#pragma once
#include "Scene.h"

class SceneGame :public Scene
{
public:
    void init()override;
    void update()override;
    void draw()override;
};

