// Copyright (c) 2025 Axel Magnuson

#pragma once

#include "raylib.h"
#include "screens.h"

//----------------------------------------------------------------------------------
// GameplayScreen Class Declaration and Implementation
//----------------------------------------------------------------------------------
struct GameplayScreen : Screen {
    GameplayScreen(Assets& assets)
        : assets_(assets)
    {
    }

    void Init() override
    {
        // TODO: Initialize GAMEPLAY screen variables here!
        framesCounter_ = 0;
        finishScreen_ = 0;
    }

    void Update() override
    {
        // TODO: Update GAMEPLAY screen variables here!

        // Press enter or tap to change to ENDING screen
        if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
        {
            finishScreen_ = 1;
            PlaySound(assets_.fxCoin);
        }
    }

    void Draw() override
    {
        // TODO: Draw GAMEPLAY screen here!
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), PURPLE);
        Vector2 pos = { 20, 10 };
        DrawTextEx(assets_.font, "GAMEPLAY SCREEN", pos, assets_.font.baseSize*3.0f, 4, MAROON);
        DrawText("PRESS ENTER or TAP to JUMP to ENDING SCREEN", 130, 220, 20, MAROON);
    }

    void Unload() override
    {
        // TODO: Unload GAMEPLAY screen variables here!
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
