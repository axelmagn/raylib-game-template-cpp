// Copyright (c) 2025 Axel Magnuson

#pragma once

#include "raylib.h"
#include "screens.h"

//----------------------------------------------------------------------------------
// TitleScreen Class Declaration and Implementation
//----------------------------------------------------------------------------------
struct TitleScreen : Screen {
    TitleScreen(Assets& assets)
        : assets_(assets)
    {
    }

    void Init() override
    {
        // TODO: Initialize TITLE screen variables here!
        framesCounter_ = 0;
        finishScreen_ = 0;
    }

    void Update() override
    {
        // TODO: Update TITLE screen variables here!

        // Press enter or tap to change to GAMEPLAY screen
        if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
        {
            //finishScreen_ = 1;   // OPTIONS
            finishScreen_ = 2;   // GAMEPLAY
            PlaySound(assets_.fxCoin);
        }
    }

    void Draw() override
    {
        // TODO: Draw TITLE screen here!
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), GREEN);
        Vector2 pos = { 20, 10 };
        DrawTextEx(assets_.font, "TITLE SCREEN", pos, assets_.font.baseSize*3.0f, 4, DARKGREEN);
        DrawText("PRESS ENTER or TAP to JUMP to GAMEPLAY SCREEN", 120, 220, 20, DARKGREEN);
    }

    void Unload() override
    {
        // TODO: Unload TITLE screen variables here!
    }

    int Finish() override
    {
        return finishScreen_;
    }

private:
    Assets& assets_;

    int framesCounter_{0};
    int finishScreen_{0};
};
