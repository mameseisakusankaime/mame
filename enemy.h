#pragma once
#include "OBJ2D.h"

struct EnemySetdata
{
    MOVER mover;
    VECTOR2 pos;
    int timer;
};

/// <summary>
/// �G�Ǘ��N���X
/// </summary>
class Enemy:
    public OBJ2DManager
{
public:
    static const int OBJ_MAX = 30;
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
private:
    Enemy() {};//�}�l�[�W���[�̕��������֎~
};

// ����
bool enemy_erase(OBJ2D* obj);

void enemy_walk(OBJ2D* obj);
void enemy_attack(OBJ2D* obj);

void dist_len(OBJ2D* obj, OBJ2D* player);



