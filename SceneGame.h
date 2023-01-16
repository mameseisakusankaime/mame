#pragma once
#include "Scene.h"

class SceneGame :public Scene
{
public:
    GameLib::Sprite* data;
    int timer;
public:
    void init()override;
    void deinit()override;
    void update()override;
    void draw()override; 
};

void anime(OBJ2D* obj, int total, int flame, bool loop, int type);
bool hitCheckCircle(VECTOR2 pos1, float r1, VECTOR2 pos2, float r2);
bool hitCheck(OBJ2D* obj1, OBJ2D* obj2, int num);
void judge();
void player_attack();