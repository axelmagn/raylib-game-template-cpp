// Copyright (c) 2025 Axel Magnuson

#pragma once

#include "raylib.h"
#include "screens.h"

//----------------------------------------------------------------------------------
// OptionsScreen Class Declaration and Implementation
//----------------------------------------------------------------------------------
struct OptionsScreen : Screen {
    OptionsScreen() {}

    void Init() override
    {
        // TODO: Initialize OPTIONS screen variables here!
        framesCounter_ = 0;
        finishScreen_ = 0;
    }

    void Update() override
    {
        // TODO: Update OPTIONS screen variables here!
    }

    void Draw() override
    {
        // TODO: Draw OPTIONS screen here!
    }

    void Unload() override
    {
        // TODO: Unload OPTIONS screen variables here!
    }

    int Finish() override
    {
        return finishScreen_;
    }

private:
    int framesCounter_{0};
    int finishScreen_{0};
};
