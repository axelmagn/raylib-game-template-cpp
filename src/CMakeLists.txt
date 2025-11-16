# Unity build configuration - only compile raylib_game.cpp which includes all other sources
target_sources(${PROJECT_NAME} PRIVATE
    raylib_game.cpp
    screens.h
)
