#pragma once
#include "Scene.h"
#include "common.h"

class SceneTitle :public Scene
{
public:
    GameLib::Sprite* data;
public:
    void init()override; 
    void deinit()override;
    void update()override;
    void draw()override;
};