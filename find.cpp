#include "find.h"
#include "common.h"
#include "enemy.h"
using namespace GameLib;

void Find::init()
{
    OBJ2DManager::init();

    obj_w[0].mover = find;
}

void find(OBJ2D* obj)
{
    OBJ2D enemy = Enemy::getInstance()->obj_w[obj->dataNum];

    switch (obj->state)
    {
    case 0:
        obj->data = sprite_load(L"./Data/Images/find.png");
        obj->pos = { enemy.pos.x,enemy.pos.y - 100 };
        obj->scale = { 0.5f,0.5f };
        obj->texPos = { 0,0 };
        obj->texSize = { 256,256 };
        obj->pivot = { 128,128 };
        obj->eraser = enemy_erase;
        obj->hp = 1;

        ++obj->state;
        //break;
    case 1:

        obj->pos = { enemy.pos.x,enemy.pos.y - 100 };

        if (obj->timer >= 60)
        {
            obj->hp = 0;
        }

        ++obj->timer;
        break;
    }
}
