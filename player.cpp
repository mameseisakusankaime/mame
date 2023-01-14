#include "player.h"
#include "common.h"
using namespace GameLib;

GameLib::Sprite** data_tbl[] =
{
    &Player::maru,
    &Player::sikaku,
    &Player::hosi,
    &Player::sankaku,
};

float data_pos[][2] =
{
    {0,0},
    {256,0},
    {512,0},
    {768,0},
};

GameLib::Sprite* Player::maru = nullptr;
GameLib::Sprite* Player::sikaku = nullptr;
GameLib::Sprite* Player::hosi = nullptr;
GameLib::Sprite* Player::sankaku = nullptr;

void Player::init()
{
    obj.state = 0;
}

void Player::deinit()
{
    safe_delete(obj.data);
}

void Player::update()
{
    switch (obj.state)
    {
    case 0:
        obj.data = sprite_load(L"./Data/Images/player.png");
        obj.data = sprite_load(L"./Data/Images/data.png");
        obj.pos = { 200,200 };
        obj.scale = { 1,1 };
        obj.texPos = { 0,0 };
        obj.texSize = { 256,256 };

        maru = sprite_load(L"./Data/Images/0.png");
        sikaku = sprite_load(L"./Data/Images/1.png");
        hosi = sprite_load(L"./Data/Images/2.png");
        sankaku = sprite_load(L"./Data/Images/3.png");

        ++obj.state;
        //break;
    case 1:
        // 移動
        //if (STATE(0) & PAD_UP)obj.pos.y -= 5;
        //if (STATE(0) & PAD_DOWN)obj.pos.y += 5;
        if (STATE(0) & PAD_LEFT)obj.pos.x -= 5;
        if (STATE(0) & PAD_RIGHT)obj.pos.x += 5;

        // 画像データ
        //if (STATE(0) & PAD_UP)      setSpr(0);
        //if (STATE(0) & PAD_DOWN)    setSpr(1);
        //if (STATE(0) & PAD_LEFT)    setSpr(2);
        //if (STATE(0) & PAD_RIGHT)   setSpr(3);

        // 画像位置
        if (STATE(0) & PAD_UP)      setData(0);
        if (STATE(0) & PAD_DOWN)    setData(1);
        if (STATE(0) & PAD_LEFT)    setData(2);
        if (STATE(0) & PAD_RIGHT)   setData(3);

        obj.pos.y += 5;
        if (obj.pos.y >= 300)obj.pos.y = 300;

        break;
    }
}

void Player::draw()
{
    sprite_render(obj.data, obj.pos.x, obj.pos.y, obj.scale.x, obj.scale.y, obj.texPos.x, obj.texPos.y, obj.texSize.x, obj.texSize.y);
}

void Player::setData(int data)
{
    obj.texPos.x = data_pos[data][0];
    obj.texPos.y = data_pos[data][1];
}

void Player::setSpr(int data)
{
    obj.data = *data_tbl[data];
}
