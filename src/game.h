/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <vector>
#include <tuple>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <irrKlang.h>

#include "game_level.h"
#include "ball_object.h"
#include "power_up.h"

using namespace irrklang;

// Represents the current state of the game
enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

enum Direction {
    UP,
    RIGHT,
    DOWN,
    LEFT
};

// Initial size of the player paddle
const glm::vec2 PLAYER_SIZE{ 100, 20 };
// Initial velocity of the player paddle
const float PLAYER_VELOCITY{ 500.0f };

// 初始化球的速度
const glm::vec2 INITIAL_BALL_VELOCITY(100.0f, -350.0f);
// 球的半径
const float BALL_RADIUS = 12.5f;
// 最大碰撞角度
const float MAX_BOUNCE_ANGLE = 70.0f;

typedef std::tuple<GLboolean, Direction, glm::vec2> Collision;

class Game
{
public:
    // 游戏状态
    GameState  State;
    bool  Keys[1024];
    bool  KeysProcessed[1024];
    unsigned int     Width, Height;

    std::vector<GameLevel> Levels;
    std::vector<PowerUp>  PowerUps;
    unsigned int            Level;
    unsigned int            Lives;
    unsigned int            Points;

    // 构造函数/析构函数
    Game(unsigned int width, unsigned int height);
    ~Game();
    // 初始化游戏状态（加载所有的着色器/纹理/关卡）
    void Init();
    // 游戏循环
    void ProcessInput(float dt);
    void Update(float dt);
    void Render();

    void ResetLevel();
    void ResetPlayer();

    void SpawnPowerUps(GameObject& block);
    void UpdatePowerUps(float dt);

    void DoCollisions();
};

#endif


/*#ifndef glCheckError()
GLenum glCheckError_(const char* file, int line)
{
    GLenum errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR)
    {
        std::string error;
        switch (errorCode)
        {
        case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
        case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
        case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
        case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
        case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
        case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
        case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
        }
        std::cout << error << " | " << file << " (" << line << ")" << std::endl;
    }
    return errorCode;
}
#define glCheckError() glCheckError_(__FILE__, __LINE__) 

#endif // glCheckError()*/