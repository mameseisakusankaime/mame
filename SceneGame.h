#pragma once
#include "Scene.h"

class SceneGame :public Scene
{
public:
    GameLib::Sprite* data;
public:
    void init()override;
    void deinit()override;
    void update()override;
    void draw()override;
};