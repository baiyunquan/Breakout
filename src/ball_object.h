#ifndef BALLOBJECT_H
#define BALLOBJECT_H
#include "game_object.h"


class BallObject : public GameObject
{
public:
    // 球的半径
    float   Radius;
	// 球是否被固定在挡板上
    bool Stuck , PassThrough , Sticky;

    BallObject();
    BallObject(glm::vec2 pos, float radius, glm::vec2 velocity, Texture2D sprite);

    glm::vec2 Move(float dt, unsigned int window_width, unsigned int window_height);
    void      Reset(glm::vec2 position, glm::vec2 velocity);
};
#endif