// Copyright (c) 2025 Axel Magnuson

#pragma once

#include "raylib.h"
#include "screens.h"

//----------------------------------------------------------------------------------
// LogoScreen Class Declaration and Implementation
//----------------------------------------------------------------------------------
struct LogoScreen : Screen {
    LogoScreen() {}

    void Init() override
    {
        finishScreen_ = 0;
        framesCounter_ = 0;
        lettersCount_ = 0;

        logoPositionX_ = GetScreenWidth()/2 - 128;
        logoPositionY_ = GetScreenHeight()/2 - 128;

        topSideRecWidth_ = 16;
        leftSideRecHeight_ = 16;
        bottomSideRecWidth_ = 16;
        rightSideRecHeight_ = 16;

        state_ = 0;
        alpha_ = 1.0f;
    }

    void Update() override
    {
        if (state_ == 0)                 // State 0: Top-left square corner blink logic
        {
            framesCounter_++;

            if (framesCounter_ == 80)
            {
                state_ = 1;
                framesCounter_ = 0;      // Reset counter... will be used later...
            }
        }
        else if (state_ == 1)            // State 1: Bars animation logic: top and left
        {
            topSideRecWidth_ += 8;
            leftSideRecHeight_ += 8;

            if (topSideRecWidth_ == 256) state_ = 2;
        }
        else if (state_ == 2)            // State 2: Bars animation logic: bottom and right
        {
            bottomSideRecWidth_ += 8;
            rightSideRecHeight_ += 8;

            if (bottomSideRecWidth_ == 256) state_ = 3;
        }
        else if (state_ == 3)            // State 3: "raylib" text-write animation logic
        {
            framesCounter_++;

            if (lettersCount_ < 10)
            {
                if (framesCounter_/12)   // Every 12 frames, one more letter!
                {
                    lettersCount_++;
                    framesCounter_ = 0;
                }
            }
            else    // When all letters have appeared, just fade out everything
            {
                if (framesCounter_ > 200)
                {
                    alpha_ -= 0.02f;

                    if (alpha_ <= 0.0f)
                    {
                        alpha_ = 0.0f;
                        finishScreen_ = 1;   // Jump to next screen
                    }
                }
            }
        }
    }

    void Draw() override
    {
        if (state_ == 0)         // Draw blinking top-left square corner
        {
            if ((framesCounter_/10)%2) DrawRectangle(logoPositionX_, logoPositionY_, 16, 16, BLACK);
        }
        else if (state_ == 1)    // Draw bars animation: top and left
        {
            DrawRectangle(logoPositionX_, logoPositionY_, topSideRecWidth_, 16, BLACK);
            DrawRectangle(logoPositionX_, logoPositionY_, 16, leftSideRecHeight_, BLACK);
        }
        else if (state_ == 2)    // Draw bars animation: bottom and right
        {
            DrawRectangle(logoPositionX_, logoPositionY_, topSideRecWidth_, 16, BLACK);
            DrawRectangle(logoPositionX_, logoPositionY_, 16, leftSideRecHeight_, BLACK);

            DrawRectangle(logoPositionX_ + 240, logoPositionY_, 16, rightSideRecHeight_, BLACK);
            DrawRectangle(logoPositionX_, logoPositionY_ + 240, bottomSideRecWidth_, 16, BLACK);
        }
        else if (state_ == 3)    // Draw "raylib" text-write animation + "powered by"
        {
            DrawRectangle(logoPositionX_, logoPositionY_, topSideRecWidth_, 16, Fade(BLACK, alpha_));
            DrawRectangle(logoPositionX_, logoPositionY_ + 16, 16, leftSideRecHeight_ - 32, Fade(BLACK, alpha_));

            DrawRectangle(logoPositionX_ + 240, logoPositionY_ + 16, 16, rightSideRecHeight_ - 32, Fade(BLACK, alpha_));
            DrawRectangle(logoPositionX_, logoPositionY_ + 240, bottomSideRecWidth_, 16, Fade(BLACK, alpha_));

            DrawRectangle(GetScreenWidth()/2 - 112, GetScreenHeight()/2 - 112, 224, 224, Fade(RAYWHITE, alpha_));

            DrawText(TextSubtext("raylib", 0, lettersCount_), GetScreenWidth()/2 - 44, GetScreenHeight()/2 + 48, 50, Fade(BLACK, alpha_));

            if (framesCounter_ > 20) DrawText("powered by", logoPositionX_, logoPositionY_ - 27, 20, Fade(DARKGRAY, alpha_));
        }
    }

    void Unload() override
    {
        // Unload LOGO screen variables here!
    }

    int Finish() override
    {
        return finishScreen_;
    }

private:
    int framesCounter_{0};
    int finishScreen_{0};
    int logoPositionX_{0};
    int logoPositionY_{0};
    int lettersCount_{0};
    int topSideRecWidth_{0};
    int leftSideRecHeight_{0};
    int bottomSideRecWidth_{0};
    int rightSideRecHeight_{0};
    int state_{0};
    float alpha_{1.0f};
};
