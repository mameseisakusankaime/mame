#pragma once 
#include "Scene.h"
#include "common.h"

class SceneClear :public Scene
{
public:
    GameLib::Sprite* data;
    int                 timer;
public:
    void init()override;
    void deinit()override;
    void update()override;
    void draw()override;
};