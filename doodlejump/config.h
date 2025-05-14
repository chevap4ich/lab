#pragma once

#define SCREEN_SIZE_X 470
#define SCREEN_SIZE_Y 700
#define SIMULATION_SPEED 250
#define ACELLERATION 120
#define HORIZONTAL_VELOCITY 80
#define PLATFORM_WIDTH 70
#define PLATFORM_HEIGHT 20
#define BOUNCE_VELOCITY 230
enum GameState{
    Menu,
    Acting,
    Options
};

enum CurrentDirection{
    Left, 
    Right
};

enum PlatfType{
    Default, 
    Breaking,
    Moving
};