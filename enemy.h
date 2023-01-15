#pragma once
#include "OBJ2D.h"

static const VECTOR2 enemy_position[] =
{
    {500,100},
    {700,100},
    {900,100},
};

class Enemy:public OBJ2DManager
{
public:
    static const int OBJ_MAX = 10;
    OBJ2D obj_w[OBJ_MAX];

    

public:
    OBJ2D* begin() { return obj_w; }
    OBJ2D* end() { return obj_w + OBJ_MAX; }

    void init();


    //void setData(int data); // 画像位置設定（画像データ位置） 
    //void setSpr(int data);  // 画像設定

    static Enemy* getInstance()
    {
        static Enemy instance;
        return &instance;
    }
};

// 消去
bool enemy_erase(OBJ2D* obj);

void enemy_walk(OBJ2D* obj);