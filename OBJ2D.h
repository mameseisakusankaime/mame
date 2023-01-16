#pragma once
#include "common.h"

class OBJ2D;
typedef void(*MOVER)(OBJ2D* obj);
typedef bool(*ERASER)(OBJ2D* obj);
 
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
    VECTOR2 pivot;              // ��_
    int angle;                  // �p�x
    VECTOR4 color;                // �F
    

    VECTOR2 offset;
    float radius;

    int timer;                  // �^�C�}�[

    MOVER mover;   // �֐��|�C���^�i�ړ������j

    ERASER eraser;

    int hp;         // �̗�
    float foundRadius;     // ���m����~

    int dataNum;

    bool invincible;   // ���G����(true������)
    int invincibleTimer;    // ���G����
    int flashingTimer;

    // �A�j���[�V�����֌W
    int animeState;
    int anime;
    int animeTimer;
    bool one;
    bool end;
    bool attack;
    bool half;
    

    float ReferencePosition;    // �����̊�ʒu


public:
    OBJ2D() { init(); }
    void init();
    void deinit();
    void clear();
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