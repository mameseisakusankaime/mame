#include "enemy.h"
#include "common.h"
#include "SceneGame.h"
#include "player.h"
#include "find.h"

using namespace GameLib;

bool enemy_erase(OBJ2D* obj)
{
    return (obj->hp <= 0 ? true : false);
}

void Enemy::init()
{
    OBJ2DManager::init();

    int num = 0;
    for (auto& item : obj_w)
    {
        item.dataNum = num;
        num++;
    }    

    Enemy::getInstance()->searchSet(enemy_walk, enemy_position[0]);
    Enemy::getInstance()->searchSet(enemy_walk, enemy_position[1]);
    Enemy::getInstance()->searchSet(enemy_walk, enemy_position[2]);
}


 
// ちょっと考える
void enemy_walk(OBJ2D* obj)
{
    OBJ2D& player = Player::getInstance()->obj_w[0]; //プレイヤー
    int move = 2;   // 移動速度
    

    switch (obj->state)
    {
    case 0:
        // 初期設定
        obj->data = sprite_load(L"./Data/Images/enemy.png");
        //obj->pos = { 900,200 };
        obj->scale = { 1,1 };
        obj->texPos = { 0,0 };
        obj->texSize = { 256,256 };
        obj->pivot = { 128,128 };
        obj->type = DATA::SANKAKU;
        obj->radius = 40;
        obj->hp = 2;
        obj->foundRadius = 200;
        obj->eraser = enemy_erase;

        static const float posX = obj->pos.x;       //初期位置
        obj->ReferencePosition = obj->pos.x;


        ++obj->state;
        //break;
    case 1:
        if (obj->pos.y >= 450)++obj->state;
        break;
    case 2:
        // 左に進む
        obj->pos.x -= move;
        if (obj->pos.x <= obj->ReferencePosition - 100)
        {
            obj->state = 3;
            if (obj->scale.x > 0)obj->scale.x *= -1;
        }

        // 見つける
        if (hitCheck(&player, obj, HITCHECK::PLAndENEScope))
            if (player.pos.x < obj->pos.x)obj->state = 4;

        break;
    case 3:
        // 右に進む
        obj->pos.x += move;
        if (obj->pos.x >= obj->ReferencePosition + 100)
        {
            obj->state = 2;
            if (obj->scale.x < 0)obj->scale.x *= -1;
        }

        // 見つける
        if (hitCheck(&player, obj, HITCHECK::PLAndENEScope))
            if (player.pos.x > obj->pos.x)obj->state = 4;

        break;
    case 4:
        Find::getInstance()->init();
        ++obj->state;
        break;
    case 5:
        // プレイヤーの方向に向かって進む
        if (player.pos.x > obj->pos.x)
        {
            obj->pos.x += move;
            // 画像を進行方向へ向ける
            if (obj->scale.x > 0)obj->scale.x *= -1;
        }
        if (player.pos.x < obj->pos.x)
        {
            obj->pos.x -= move;
            // 画像を進行方向へ向ける
            if (obj->scale.x < 0)obj->scale.x *= -1;
        }


        // 食べてるみたいで面白い
        //// プレイヤーと敵の距離
        //float dist = player.pos.x - obj->pos.x;    
        //if (dist < 0)dist *= -1;
        //// プレイヤーと敵の離しておきたい距離
        //float len = player.radius + obj->radius;
        //if (dist < len)obj->pos.x = player.pos.x + obj->radius;
        
        // プレイヤーと敵の距離
        float dist = player.pos.x - obj->pos.x;
        // 敵がどっちにいるか(右だとtrue)
        bool right;
        if (dist < 0)
        {
            dist *= -1;
            right = true;
        }
        else
        {
            right = false;
        }
        // プレイヤーと敵の離しておきたい距離
        float len = player.radius + obj->radius;
        if (dist < len)
            obj->pos.x = right ? player.pos.x + len : player.pos.x - len;

        break;
    }

    // 重力
    obj->pos.y += 5;
    if (obj->pos.y >= 450)obj->pos.y = 450;     //地面
}
