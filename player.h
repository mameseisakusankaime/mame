#pragma once
#include "OBJ2D.h"

class Player :public OBJ2DManager
{
public:
    static const int OBJ_MAX = 1;
    OBJ2D	obj_w[OBJ_MAX];

    //static GameLib::Sprite* maru;
    //static GameLib::Sprite* sikaku;
    //static GameLib::Sprite* hosi;
    //static GameLib::Sprite* sankaku;

public:
    OBJ2D* begin() { return obj_w; }
    OBJ2D* end() { return obj_w + OBJ_MAX;}

    void init()override;

    

    void setData(int data); // �摜�ʒu�ݒ�i�摜�f�[�^�ʒu�j 
    void setSpr(int data);  // �摜�ݒ�

    static Player* getInstance()
    {
        static Player instance;
        return &instance;
    }
private:
    Player() {};//�}�l�[�W���[�̕��������֎~
};

void player(OBJ2D* obj);