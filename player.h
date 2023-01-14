#pragma once
#include "OBJ2D.h"

class Player
{
public:
    OBJ2D obj;

    static GameLib::Sprite* maru;
    static GameLib::Sprite* sikaku;
    static GameLib::Sprite* hosi;
    static GameLib::Sprite* sankaku;

public:
    void init();
    void deinit();
    void update();
    void draw();

    void setData(int data); // �摜�ʒu�ݒ�i�摜�f�[�^�ʒu�j 
    void setSpr(int data);  // �摜�ݒ�
};

// ���̖��O
enum DATA
{
    MARU,
    SIKAKU,
    HOSI,
    SANKAKU
};