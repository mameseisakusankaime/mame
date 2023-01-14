#include "player.h"
#include "common.h"
#include "enemy.h"
using namespace GameLib;

// 画像データテーブル
GameLib::Sprite** data_tbl[] =
{
    &Player::maru,
    &Player::sikaku,
    &Player::hosi,
    &Player::sankaku,
};

// 画像位置テーブル
float data_pos[][2] =
{
    {0,0},
    {256,0},
    {512,0},
    {768,0},
};

// 画像データ
GameLib::Sprite* Player::maru = nullptr;
GameLib::Sprite* Player::sikaku = nullptr;
GameLib::Sprite* Player::hosi = nullptr;
GameLib::Sprite* Player::sankaku = nullptr;

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
        obj->data = sprite_load(L"./Data/Images/player.png");
        obj->data = sprite_load(L"./Data/Images/data.png");
        obj->pos = { 200,200 };
        obj->scale = { 1,1 };
        obj->texPos = { 0,0 };
        obj->texSize = { 256,256 };
        obj->type = DATA::MARU;

        Player::maru = sprite_load(L"./Data/Images/0.png");
        Player::sikaku = sprite_load(L"./Data/Images/1.png");
        Player::hosi = sprite_load(L"./Data/Images/2.png");
        Player::sankaku = sprite_load(L"./Data/Images/3.png");

        ++obj->state;
        //break;
    case 1:
        // 移動
        //if (STATE(0) & PAD_UP)obj.pos.y -= 5;
        //if (STATE(0) & PAD_DOWN)obj.pos.y += 5;
        if (STATE(0) & PAD_LEFT)obj->pos.x -= 5;
        if (STATE(0) & PAD_RIGHT)obj->pos.x += 5;

        // 画像データ
        //if (STATE(0) & PAD_UP)      setSpr(0);
        //if (STATE(0) & PAD_DOWN)    setSpr(1);
        //if (STATE(0) & PAD_LEFT)    setSpr(2);
        //if (STATE(0) & PAD_RIGHT)   setSpr(3);

        // 画像位置
        //if (STATE(0) & PAD_UP)      setData(0);
        //if (STATE(0) & PAD_DOWN)    setData(1);
        //if (STATE(0) & PAD_LEFT)    setData(2);
        //if (STATE(0) & PAD_RIGHT)   setData(3);

        obj->pos.y += 5;
        if (obj->pos.y >= 300)obj->pos.y = 300;

        if (TRG(0) & PAD_L1)
        {
            //setData(Enemy::getInstance()->obj_w.type);
        }

        break;
    }
}

void Player::setData(int data)
{
    obj_w[0].texPos.x = data_pos[data][0];
    obj_w[0].texPos.y = data_pos[data][1];
}

void Player::setSpr(int data)
{
    obj_w[0].data = *data_tbl[data];
}
