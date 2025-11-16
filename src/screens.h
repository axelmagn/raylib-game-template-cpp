// Copyright (c) 2025 Axel Magnuson

#ifndef SCREENS_H
#define SCREENS_H

#include "raylib.h"

//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------
typedef enum GameScreen { UNKNOWN = -1, LOGO = 0, TITLE, OPTIONS, GAMEPLAY, ENDING } GameScreen;

//----------------------------------------------------------------------------------
// Forward Declarations
//----------------------------------------------------------------------------------
struct Assets;

//----------------------------------------------------------------------------------
// Base Screen Structure
//----------------------------------------------------------------------------------
struct Screen {
    virtual ~Screen() {}

    virtual void Init() = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;
    virtual void Unload() = 0;
    virtual int Finish() = 0;
};

#endif // SCREENS_H
