#pragma once
#include "common.h"

class OBJ2D;
typedef void(*MOVER)(OBJ2D* obj);

class OBJ2D
{
public:
    int state;                  // state
    
    int type;                   // �^�C�v

    GameLib::Sprite* data;      // �摜
    VECTOR2 pos;                // �ʒu
    VECTOR2 scale;              // �傫��
    VECTOR2 texPos;             // ���摜�ʒu
    VECTOR2 texSize;            // ���摜�T�C�Y
    int angle;                  // �p�x

    int timer;                  // �^�C�}�[

    MOVER mover;   // �֐��|�C���^�i�ړ������j

public:
    OBJ2D() { init(); }
    void init();
    void deinit();
    void update();
    void draw();
};

class OBJ2DManager
{
public:
    virtual OBJ2D* begin() = 0;
    virtual OBJ2D* end() = 0;

    virtual void init();
    virtual void deinit();
    virtual void update();
    virtual void draw();

    OBJ2D* searchSet(MOVER mover, const VECTOR2& pos);
};