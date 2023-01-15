#include "gage.h"
#include "common.h"
#include "enemy.h"
using namespace GameLib;

void Gage::init()
{
    OBJ2DManager::init();

    obj_w[0].mover = gage; 
}

void gage(OBJ2D* obj)
{
    OBJ2D enemy = Enemy::getInstance()->obj_w[obj->dataNum];
    switch (obj->state)
    {
    case 0:
        obj->data = sprite_load(L"./Data/Images/gage.png");
        obj->pos = { enemy.pos.x,enemy.pos.y-50 };
        obj->scale = { 0.5f,0.5f };
        obj->texPos = { 0,0 };
        obj->texSize = { 256,256 };
        obj->pivot = { 128,128 };

        ++obj->state;        
        //break;
    case 1:
        obj->pos = { enemy.pos.x,enemy.pos.y - 50 };

        if (enemy.hp<=1)
            obj->texPos = { 256,0 };
        else
            obj->texPos = { 0,0 };
        

        break;
    }
}
