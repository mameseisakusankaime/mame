#pragma once
#include "common.h"

#define GROUND      (450.0f)
#define GRAVITY     (5.0f)

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
    VECTOR4 color;              // �F
    

    VECTOR2 offset;
    float radius;

    int timer;              // �^�C�}�[

    MOVER mover;            // �֐��|�C���^�i�ړ������j

    ERASER eraser;

    int hp;                 // �̗�
    int attackState;
    float foundRadius;      // ���m����~
    float attackRadius;     // �U���͈�

    int dataNum;

    bool invincible;        // ���G����(true������)
    int invincibleTimer;    // ���G����
    int flashingTimer;      //�_�Ŏ���

    // �A�j���[�V�����֌W
    int animeState;             // �A�j���X�e�[�g
    int anime;                  // �������ڂ�
    int animeTimer;             // �A�j���^�C�}�[
    bool one;                   // �Ōォ��ꖇ��
    bool end;                   // �A�j���[�V�����I���
    bool attack;                // �U��(�H�ׂ�)
    bool attackPunch;           // �U��(�p���`)
    bool half;                  // �A�j���[�V�����̔�����
                                // �U���^���邽�߂̔���
    bool hensin;

    float ReferencePosition;    // �����̊�ʒu

    VECTOR2 size;               //�����蔻��̑傫���̔���
    bool flag[1];               //�g�p�ς݂�

    float holdPosX;             // ��O�̃|�W�V����
    bool key;                   // ���������Ă��邩

    int playerType;

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

void gravity(OBJ2D*);
bool animeUpdate(OBJ2D* obj, int total, int frame, bool loop);