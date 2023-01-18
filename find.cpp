#include "find.h"
#include "common.h"
#include "enemy.h"
#include "player.h"
using namespace GameLib;

void Find::init()
{
    OBJ2DManager::init();

    int num = 0;
    for (auto& item : obj_w)
    {
        item.dataNum = num;
        num++;
    }

    //obj_w[0].mover = find;
    //obj_w[1].mover = find;
    //obj_w[2].mover = find;
}

void find(OBJ2D* obj)
{
    //OBJ2D enemy = Enemy::getInstance()->obj_w[obj->dataNum];
    OBJ2D player = Player::getInstance()->obj_w[0];
    float dist;

    switch (obj->state)
    {
    case 0:
        obj->data = sprite_load(L"./Data/Images/find.png");
        //obj->pos = { enemy[obj->dataNum].pos.x,enemy[obj->dataNum].pos.y - 100 };
        obj->scale = { 0.5f,0.5f }; 
        obj->texPos = { 0,0 };
        obj->texSize = { 256,256 };
        obj->pivot = { 128,128 };
        obj->eraser = enemy_erase;
        obj->hp = 1;

        obj->holdPosX = player.pos.x;

        ++obj->state;
        //break;
    case 1:
        //obj->pos = { enemy[obj->dataNum].pos.x,enemy[obj->dataNum].pos.y - 100 };

        //obj->pos = { enemy.pos.x,enemy.pos.y - 100 };


        // ˆê’èŽžŠÔ‚½‚Â‚ÆÁ‚¦‚é
        if (obj->timer >= 60)
        {
            obj->hp = 0;
        }

        

        // ”wŒiƒXƒNƒ[ƒ‹‚É‡‚í‚¹‚é
        dist = obj->holdPosX;
        obj->holdPosX = player.pos.x;
        if (dist != obj->holdPosX)
        {
            obj->pos.x += (dist - obj->holdPosX) * 3.0f;
            obj->ReferencePosition += (dist - obj->holdPosX) * 3.0f;
        }

        ++obj->timer;
        break;
    }
}
