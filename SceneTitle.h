#pragma once
#include "Scene.h"
#include "common.h"

class SceneTitle :public Scene
{
public:
    GameLib::Sprite* data;

    GameLib::Sprite* sprData;

    GameLib::Sprite* sprSura;

    VECTOR2 pos[6];
    VECTOR2 texPos;

    int timer;
    int moziState;

public:
    void init()override; 
    void deinit()override;
    void update()override;
    void draw()override;
};