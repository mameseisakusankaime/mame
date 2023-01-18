#pragma once
#include "OBJ2D.h"

static const VECTOR2 enemy_position[] =
{
    // walk��x��100�J���鎖
    {600,500},
    {900,500},
    {1200,500},
    {2000,500},
    {2500,500},
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


    //void setData(int data); // �摜�ʒu�ݒ�i�摜�f�[�^�ʒu�j 
    //void setSpr(int data);  // �摜�ݒ�

    static Enemy* getInstance()
    {
        static Enemy instance;
        return &instance;
    }
};

// ����
bool enemy_erase(OBJ2D* obj);

void enemy_walk(OBJ2D* obj);

void dist_len(OBJ2D* obj, OBJ2D* player);