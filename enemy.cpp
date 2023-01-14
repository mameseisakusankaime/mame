#include "enemy.h"
#include "common.h"
using namespace GameLib;

void Enemy::init()
{
    OBJ2DManager::init();

    Enemy::getInstance()->searchSet(eupdate, obj_w[0].pos);
}


// ‚¿‚å‚Á‚Æl‚¦‚é
void eupdate(OBJ2D* obj)
{
    switch (obj->state)
    {
    case 0:
        obj->data = sprite_load(L"./Data/Images/enemy.png");
        obj->pos = { 900,200 };
        obj->scale = { 1,1 };
        obj->texPos = { 0,0 };
        obj->texSize = { 256,256 };
        obj->type = DATA::SANKAKU;

        ++obj->state;
        //break;
    case 1:

        obj->pos.y += 5;
        if (obj->pos.y >= 300)obj->pos.y = 300;

        break;
    }
}
