#include "back.h"
#include "common.h"
#include "player.h"
#include "enemy.h"
using namespace GameLib;

void Back::init()
{
    OBJ2DManager::init();    
}

void sea_update0(OBJ2D* obj)
{
    OBJ2D player = Player::getInstance()->obj_w[0];

    switch (obj->state)
    {
    case 0:
        obj->data = sprite_load(L"./Data/Images/sea.png");
        obj->scale = { 1,1 };
        obj->texPos = { 0,0 };
        obj->texSize = { 2560,720 };
        obj->pivot = { 0,0 };

        if (obj->pos.x != 0)obj->scale.x = -1;

        ++obj->state;
        //break;
    case 1:

        float dist = obj->holdPosX;
        obj->holdPosX = player.pos.x;
        if (dist != obj->holdPosX)
        {
            obj->pos.x += (dist - obj->holdPosX) * 1.2f;
        }

        break;
    }
}

void sea_update1(OBJ2D* obj)
{
    OBJ2D player = Player::getInstance()->obj_w[0];

    switch (obj->state)
    {
    case 0:
        obj->data = sprite_load(L"./Data/Images/sea1.png");
        obj->scale = { 1,1 };
        obj->texPos = { 0,0 };
        obj->texSize = { 2560,720 };
        obj->pivot = { 0,0 };

        if (obj->pos.x != 0)obj->scale.x = -1;

        ++obj->state;
        //break;
    case 1:
        float dist = obj->holdPosX;
        obj->holdPosX = player.pos.x;
        if (dist != obj->holdPosX)
        {
            obj->pos.x += (dist - obj->holdPosX) * 2;
        }



        break;
    }
}

void sea_update2(OBJ2D* obj)
{
    OBJ2D player = Player::getInstance()->obj_w[0];

    switch (obj->state)
    {
    case 0:
        obj->data = sprite_load(L"./Data/Images/sea2.png");
        obj->scale = { 1,1 };
        obj->texPos = { 0,0 };
        obj->texSize = { 2560,720 };
        obj->pivot = { 0,0 };

        if (obj->pos.x != 0)obj->scale.x = -1;

        ++obj->state;
        //break;
    case 1:
        float dist = obj->holdPosX;
        obj->holdPosX = player.pos.x;
        if (dist != obj->holdPosX)
        {
            obj->pos.x += (dist - obj->holdPosX) * 3;
        }



        break;
    }
}

void sea_update3(OBJ2D* obj)
{
    OBJ2D player = Player::getInstance()->obj_w[0];

    switch (obj->state)
    {
    case 0:
        obj->data = sprite_load(L"./Data/Images/sea3.png");
        obj->scale = { 1,1 };
        obj->texPos = { 0,0 };
        obj->texSize = { 2560,720 };
        obj->pivot = { 0,0 };

        if (obj->pos.x != 0)obj->scale.x = -1;

        ++obj->state;
        //break;
    case 1:
        float dist = obj->holdPosX;
        obj->holdPosX = player.pos.x;
        if (dist != obj->holdPosX)
        {
            obj->pos.x += (dist - obj->holdPosX) * 5;
        }



        break;
    }
}

void back_update0(OBJ2D* obj)
{
    OBJ2D player = Player::getInstance()->obj_w[0];

    switch (obj->state)
    {
    case 0:
        obj->data = sprite_load(L"./Data/Images/back.png");
        obj->scale = { 1,1 };
        obj->texPos = { 0,0 };
        obj->texSize = { 2560,720 };
        obj->pivot = { 0,0 };

        if (obj->pos.x != 0)obj->scale.x = -1;

        ++obj->state;
        //break;
    case 1:

        float dist = obj->holdPosX;
        obj->holdPosX = player.pos.x;
        if (dist != obj->holdPosX)
        {
            obj->pos.x += (dist - obj->holdPosX) * 1.2f;
        }               

        break;
    }
}

void back_update1(OBJ2D* obj)
{
    OBJ2D player = Player::getInstance()->obj_w[0];

    switch (obj->state)
    {
    case 0:
        obj->data = sprite_load(L"./Data/Images/back1.png");
        obj->scale = { 1,1 };
        obj->texPos = { 0,0 };
        obj->texSize = { 2560,720 };
        obj->pivot = { 0,0 };

        if (obj->pos.x != 0)obj->scale.x = -1;

        ++obj->state;
        //break;
    case 1:
        float dist = obj->holdPosX;
        obj->holdPosX = player.pos.x;
        if (dist != obj->holdPosX)
        {
            obj->pos.x += (dist - obj->holdPosX) * 2;
        }



        break;
    }
}

void back_update2(OBJ2D* obj)
{
    OBJ2D player = Player::getInstance()->obj_w[0];

    switch (obj->state)
    {
    case 0:
        obj->data = sprite_load(L"./Data/Images/back2.png");
        obj->scale = { 1,1 };
        obj->texPos = { 0,0 };
        obj->texSize = { 2560,720 };
        obj->pivot = { 0,0 };

        if (obj->pos.x != 0)obj->scale.x = -1;

        ++obj->state;
        //break;
    case 1:
        float dist = obj->holdPosX;
        obj->holdPosX = player.pos.x;
        if (dist != obj->holdPosX)
        {
            obj->pos.x += (dist - obj->holdPosX) * 3;
        }



        break;
    }
}

void back_update3(OBJ2D* obj)
{
    OBJ2D player = Player::getInstance()->obj_w[0];

    switch (obj->state)
    {
    case 0:
        obj->data = sprite_load(L"./Data/Images/back3.png");
        obj->scale = { 1,1 };
        obj->texPos = { 0,0 };
        obj->texSize = { 2560,720 };
        obj->pivot = { 0,0 };

        if (obj->pos.x != 0)obj->scale.x = -1;

        ++obj->state;
        //break;
    case 1:
        float dist = obj->holdPosX;
        obj->holdPosX = player.pos.x;
        if (dist != obj->holdPosX)
        {
            obj->pos.x += (dist - obj->holdPosX) * 5;
        }



        break;
    }
}

