// Copyright (c) 2025 Axel Magnuson

#include "raylib.h"
#include "screens.h"

// Unity build - include all implementation files
#include "assets.cpp"
#include "screen_logo.cpp"
#include "screen_title.cpp"
#include "screen_options.cpp"
#include "screen_gameplay.cpp"
#include "screen_ending.cpp"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

//----------------------------------------------------------------------------------
// Game Structure Definition
//----------------------------------------------------------------------------------
struct Game {
    Game()
        : assets_(),
          logo_screen_(),
          title_screen_(assets_),
          options_screen_(),
          gameplay_screen_(assets_),
          ending_screen_(assets_)
    {
    }

    void Init() {
        InitWindow(screen_width_, screen_height_, "raylib game template");

        InitAudioDevice(); // Initialize audio device

        // Music setup
        // SetMusicVolume(assets_.music, 1.0f);
        // PlayMusicStream(assets_.music);

        // Setup and init first screen
        current_screen_ = LOGO;
        GetCurrentScreen()->Init();
    }

    void Update() {
        // UpdateMusicStream(assets_.music);       // NOTE: Music keeps playing between screens

        if (!on_transition_) {
            Screen* screen = GetCurrentScreen();
            screen->Update();

            int finishResult = screen->Finish();
            if (finishResult != 0) {
                switch (current_screen_) {
                case LOGO:
                    if (finishResult) TransitionToScreen(TITLE);
                    break;
                case TITLE:
                    if (finishResult == 1) TransitionToScreen(OPTIONS);
                    else if (finishResult == 2) TransitionToScreen(GAMEPLAY);
                    break;
                case OPTIONS:
                    if (finishResult) TransitionToScreen(TITLE);
                    break;
                case GAMEPLAY:
                    if (finishResult == 1) TransitionToScreen(ENDING);
                    break;
                case ENDING:
                    if (finishResult == 1) TransitionToScreen(TITLE);
                    break;
                default:
                    break;
                }
            }
        } else {
            UpdateTransition(); // Update transition (fade-in, fade-out)
        }
    }

    void Draw() {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        GetCurrentScreen()->Draw();

        // Draw full screen rectangle in front of everything
        if (on_transition_)
            DrawTransition();

        // DrawFPS(10, 10);

        EndDrawing();
    }

    void DeInit() {
        // Unload current screen data before closing
        GetCurrentScreen()->Unload();

        // Assets are automatically unloaded by Assets destructor

        CloseAudioDevice(); // Close audio context

        CloseWindow(); // Close window and OpenGL context
    }

    // Request transition to next screen
    void TransitionToScreen(GameScreen screen) {
        on_transition_ = true;
        trans_fade_out_ = false;
        trans_from_screen_ = current_screen_;
        trans_to_screen_ = screen;
        trans_alpha_ = 0.0f;
    }

    // Update transition effect (fade-in, fade-out)
    void UpdateTransition(void) {
        if (!trans_fade_out_) {
            trans_alpha_ += 0.05f;

            // NOTE: Due to float internal representation, condition jumps on 1.0f
            // instead of 1.05f For that reason we compare against 1.01f, to avoid
            // last frame loading stop
            if (trans_alpha_ > 1.01f) {
                trans_alpha_ = 1.0f;

                // Unload current screen
                GetScreen(trans_from_screen_)->Unload();

                // Load next screen
                current_screen_ = trans_to_screen_;
                GetCurrentScreen()->Init();

                // Activate fade out effect to next loaded screen
                trans_fade_out_ = true;
            }
        } else // Transition fade out logic
        {
            trans_alpha_ -= 0.02f;

            if (trans_alpha_ < -0.01f) {
                trans_alpha_ = 0.0f;
                trans_fade_out_ = false;
                on_transition_ = false;
                trans_from_screen_ = UNKNOWN;
                trans_to_screen_ = UNKNOWN;
            }
        }
    }

    void DrawTransition(void) {
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(),
                      Fade(BLACK, trans_alpha_));
    }

private:
    Screen* GetScreen(GameScreen screen) {
        switch (screen) {
        case LOGO: return &logo_screen_;
        case TITLE: return &title_screen_;
        case OPTIONS: return &options_screen_;
        case GAMEPLAY: return &gameplay_screen_;
        case ENDING: return &ending_screen_;
        default: return nullptr;
        }
    }

    Screen* GetCurrentScreen() {
        return GetScreen(current_screen_);
    }

    GameScreen current_screen_{LOGO};
    Assets assets_;

    // Screen instances
    LogoScreen logo_screen_;
    TitleScreen title_screen_;
    OptionsScreen options_screen_;
    GameplayScreen gameplay_screen_;
    EndingScreen ending_screen_;

    int screen_width_{800};
    int screen_height_{450};

    float trans_alpha_{0.f};
    bool on_transition_{false};
    bool trans_fade_out_{false};
    GameScreen trans_from_screen_{UNKNOWN};
    GameScreen trans_to_screen_{UNKNOWN};
};

//----------------------------------------------------------------------------------
// Global Variables Definition (local to this module)
//----------------------------------------------------------------------------------
static Game* game = nullptr;

//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------
static void UpdateDrawFrame(void);          // Update and draw one frame

//----------------------------------------------------------------------------------
// Program main entry point
//----------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //---------------------------------------------------------
    game = new Game();
    game->Init();

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
#else
    SetTargetFPS(60);       // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        UpdateDrawFrame();
    }
#endif

    // De-Initialization
    //--------------------------------------------------------------------------------------
    game->DeInit();
    delete game;
    //--------------------------------------------------------------------------------------

    return 0;
}

//----------------------------------------------------------------------------------
// Module Functions Definition
//----------------------------------------------------------------------------------
// Update and draw game frame
static void UpdateDrawFrame(void)
{
    // Update
    //----------------------------------------------------------------------------------
    game->Update();
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    game->Draw();
    //----------------------------------------------------------------------------------
}
