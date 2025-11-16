// Copyright (c) 2025 Axel Magnuson

#pragma once

#include "raylib.h"
#include "screens.h"

//----------------------------------------------------------------------------------
// Assets Structure Declaration and Implementation
//----------------------------------------------------------------------------------
struct Assets {
    Assets()
    {
        // Load global assets
        font = LoadFont("resources/mecha.png");
        // music = LoadMusicStream("resources/ambient.ogg"); // TODO: Load music
        fxCoin = LoadSound("resources/coin.wav");
    }

    ~Assets()
    {
        // Unload all assets
        UnloadFont(font);
        UnloadMusicStream(music);
        UnloadSound(fxCoin);
    }

    Font font;
    Music music;
    Sound fxCoin;
};
