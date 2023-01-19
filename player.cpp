#include "player.h"
#include "common.h"
#include "enemy.h"
#include "SceneGame.h"
#include "back.h"
using namespace GameLib;

// �摜�f�[�^�e�[�u��
//GameLib::Sprite** data_tbl[] =
//{
//    &Player::maru,
//    &Player::sikaku,
//    &Player::hosi,
//    &Player::sankaku,
//};

// �摜�ʒu�e�[�u��
float data_pos[][2] =
{
    {0,0},
    {256,0},
    {512,0},
    {768,0},
};

// �摜�f�[�^
//GameLib::Sprite* Player::maru = nullptr;
//GameLib::Sprite* Player::sikaku = nullptr;
//GameLib::Sprite* Player::hosi = nullptr;
//GameLib::Sprite* Player::sankaku = nullptr;

void Player::init()
{
    OBJ2DManager::init();

    obj_w[0].mover = player;
}


void player(OBJ2D* obj)
{
    switch (obj->state)
    {
    case 0:
        //obj->data = sprite_load(L"./Data/Images/player1.png");
        obj->data = sprite_load(L"./Data/Images/player.png");
        //obj->data = sprite_load(L"./Data/Images/data.png");
        obj->pos = { 200,200 };
        obj->scale = { 0.5f,0.5f };
        obj->texPos = { 0,0 };  
        obj->texSize = { 512,512 };
        obj->pivot = { 128,384 };
        obj->type = DATA::MARU;
        obj->radius = 45;
        obj->foundRadius = 160;
        obj->hp = 5;
        //obj->eraser = enemy_erase;

        //Player::maru = sprite_load(L"./Data/Images/0.png");
        //Player::sikaku = sprite_load(L"./Data/Images/1.png");
        //Player::hosi = sprite_load(L"./Data/Images/2.png");
        //Player::sankaku = sprite_load(L"./Data/Images/3.png");

        // back 
        

        ++obj->state;
        //break;
    case 1:
        // �ړ�
        
        //if (STATE(0) & PAD_UP)obj.pos.y -= 5;
        //if (STATE(0) & PAD_DOWN)obj.pos.y += 5;
        //if (!obj->attack)
        //{
            switch (STATE(0) & (PAD_LEFT | PAD_RIGHT))
            {
            case PAD_LEFT:
                // �v���C���[�̈ړ�
                if(!obj->attack)anime(obj, 2, 15, true, 0);
                obj->pos.x -= 1;
                if (obj->scale.x > 0)obj->scale.x *= -1;
                break;
            case PAD_RIGHT:
                // �v���C���[�̈ړ�
                if (!obj->attack)anime(obj, 2, 15, true, 0);
                obj->pos.x += 1;
                if (obj->scale.x < 0)obj->scale.x *= -1;
                break;
            }
        //}

        debug::setString("x%f", obj->texPos.x);
        debug::setString("y%f", obj->texPos.y);

        // �摜�f�[�^
        //if (STATE(0) & PAD_UP)      setSpr(0);
        //if (STATE(0) & PAD_DOWN)    setSpr(1);
        //if (STATE(0) & PAD_LEFT)    setSpr(2);
        //if (STATE(0) & PAD_RIGHT)   setSpr(3);

        // �摜�ʒu
        //if (STATE(0) & PAD_UP)      setData(0);
        //if (STATE(0) & PAD_DOWN)    setData(1);
        //if (STATE(0) & PAD_LEFT)    setData(2);
        //if (STATE(0) & PAD_RIGHT)   setData(3);

        gravity(obj);

        //if (TRG(0) & PAD_L1)
        //{
        //    //setData(Enemy::getInstance()->obj_w.type);
        //}


        
        // �U���t�F�[�Y�Ɉړ�
        if (obj->attack)
            obj->state = 2;

#ifdef _DEBUG
        debug::setString("player.hp%d", obj->hp);
        //debug::setString("obj->flashingTimer")
#endif

        break;
    case 2:
        // �U��������
        obj->animeState = 0;

        ++obj->state;
        break;
    case 3:
        // �U������

        anime(obj, 13, 3, false, 0);

        if (obj->end)
        { 
            obj->texPos.x = 0;
            obj->state = 1;
            obj->end = false;
            obj->animeState = 0;
        }


        break;
    }

    if (obj->pos.x < obj->pivot.x / 2)obj->pos.x = obj->pivot.x / 2;
    if (obj->pos.x > 1280 - obj->pivot.x / 2)obj->pos.x = 1280 - obj->pivot.x / 2;

    // ���G����(������)
    if (obj->invincible)
    {
        ++obj->invincibleTimer;
        ++obj->flashingTimer;
        if (obj->flashingTimer / 5 == 1)
        {
            obj->color.w = obj->color.w == 1 ? 0 : 1;
            obj->flashingTimer = 0;
        }
    }
    // ���G���ԏI��
    if (obj->invincibleTimer >= 60)
    {
        obj->invincible = false;
        obj->invincibleTimer = 0;
        obj->color.w = 1;
    }
#ifdef _DEBUG
    debug::setString("state%d", obj->state);
#endif 
}


void Player::setData(int data)
{
    obj_w[0].texPos.x = data_pos[data][0];
    obj_w[0].texPos.y = data_pos[data][1];
}

void Player::setSpr(int data)
{
    //obj_w[0].data = *data_tbl[data];
}
