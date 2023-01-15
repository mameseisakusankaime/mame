#include "enemy.h"
#include "common.h"
#include "SceneGame.h"
#include "player.h"

using namespace GameLib;

void Enemy::init()
{
    OBJ2DManager::init();

    int num = 0;
    for (auto& item : obj_w)
    {
        item.dataNum = num;
        num++;
    }

    Enemy::getInstance()->searchSet(enemy_walk, obj_w[0].pos);
}


 
// ちょっと考える
void enemy_walk(OBJ2D* obj)
{
    OBJ2D player = Player::getInstance()->obj_w[0]; //プレイヤー
    int move = 2;   // 移動速度
    

    switch (obj->state)
    {
    case 0:
        // 初期設定
        obj->data = sprite_load(L"./Data/Images/enemy.png");
        obj->pos = { 900,200 };
        obj->scale = { 1,1 };
        obj->texPos = { 0,0 };
        obj->texSize = { 256,256 };
        obj->pivot = { 128,128 };
        obj->type = DATA::SANKAKU;
        obj->radius = 40;
        obj->hp = 2;
        obj->foundRadius = 180;

        static const float posX = obj->pos.x;

        ++obj->state;
        //break;
    case 1:
        if (obj->pos.y >= 450)++obj->state;
        break;
    case 2:
        // 左に進む
        obj->pos.x -= move;
        if (obj->pos.x <= posX - 100)
        {
            obj->state = 3;
            if (obj->scale.x > 0)obj->scale.x *= -1;
        }

        // mitukaru
        if (hitCheck(&player, obj, 1))
            obj->state = 4;

        break;
    case 3:
        // 右に進む
        obj->pos.x += move;
        if (obj->pos.x >= posX + 100)
        {
            obj->state = 2;
            if (obj->scale.x < 0)obj->scale.x *= -1;
        }

        if (hitCheck(&player, obj, 1))
            obj->state = 4;

        break;
    case 4:
        if (player.pos.x > obj->pos.x)
            obj->pos.x += move;
        if (player.pos.x < obj->pos.x)
            obj->pos.x -= move;

        break;
    }

    // 重力
    obj->pos.y += 5;
    if (obj->pos.y >= 450)obj->pos.y = 450;
}
