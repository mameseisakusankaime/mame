#pragma once
#include "OBJ2D.h"



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

void eupdate(OBJ2D* obj);