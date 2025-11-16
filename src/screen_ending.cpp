// Copyright (c) 2025 Axel Magnuson

#pragma once

#include "raylib.h"
#include "screens.h"

//----------------------------------------------------------------------------------
// EndingScreen Class Declaration and Implementation
//----------------------------------------------------------------------------------
struct EndingScreen : Screen {
    EndingScreen(Assets& assets)
        : assets_(assets)
    {
    }

    void Init() override
    {
        // TODO: Initialize ENDING screen variables here!
        framesCounter_ = 0;
        finishScreen_ = 0;
    }

    void Update() override
    {
        // TODO: Update ENDING screen variables here!

        // Press enter or tap to return to TITLE screen
        if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
        {
            finishScreen_ = 1;
            PlaySound(assets_.fxCoin);
        }
    }

    void Draw() override
    {
        // TODO: Draw ENDING screen here!
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLUE);

        Vector2 pos = { 20, 10 };
        DrawTextEx(assets_.font, "ENDING SCREEN", pos, assets_.font.baseSize*3.0f, 4, DARKBLUE);
        DrawText("PRESS ENTER or TAP to RETURN to TITLE SCREEN", 120, 220, 20, DARKBLUE);
    }

    void Unload() override
    {
        // TODO: Unload ENDING screen variables here!
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
