#pragma once
#include "Scene.h"

class SceneTitle :public Scene
{
public:
    void init()override;
    void update()override;
    void draw()override;
};