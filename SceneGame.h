#pragma once
#include "Scene.h"

//hitChaeckä÷êîÇÃédól
enum HITCHECK
{
    PLAndENE = 0,
    PLAndENEScope,
    PLScopeAndENE,

};

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

void anime(OBJ2D* obj, int total, int flame, bool loop, int type);
bool hitCheckCircle(VECTOR2 pos1, float r1, VECTOR2 pos2, float r2);
bool hitCheckBox(float b1top, float B1left, float b1right, float b1bottom,
    float b2top, float b2left, float b2right, float b2bottom);
bool hitCheckBox(VECTOR2 pos1, VECTOR2 size1, VECTOR2 pos2, VECTOR2 size2);
bool hitCheck(OBJ2D* obj1, OBJ2D* obj2, int num);
void judge();
void player_attack();