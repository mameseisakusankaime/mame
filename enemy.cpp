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

    //Enemy::getInstance()->searchSet(enemy_walk, enemy_position[0]);
    //Enemy::getInstance()->searchSet(enemy_walk, enemy_position[1]);
    //Enemy::getInstance()->searchSet(enemy_walk, enemy_position[2]);
}
 
// ちょっと考える
void enemy_walk(OBJ2D* obj)
{
    OBJ2D player = Player::getInstance()->obj_w[0]; //プレイヤー
    OBJ2D* find_obj[10];
    for (int i = 0; i < 10; ++i)
    {
        find_obj[i] = &Find::getInstance()->obj_w[i];
    }

    float move = 0.5f;   // 移動速度
    float dist;

    switch (obj->state)
    {
    case 0:
        // 初期設定
        obj->data = sprite_load(L"./Data/Images/enemy.png");
        //obj->data = sprite_load(L"./Data/Images/enemy.png");
        //obj->pos = { 900,200 };
        obj->scale = { 0.5f,0.5f };
        obj->texPos = { 0,0 };
        obj->texSize = { 512,512 };
        obj->pivot = { 128,384 };
        obj->type = DATA::SANKAKU;
        obj->radius = 40;
        obj->hp = 1;
        obj->foundRadius = 200;
        obj->eraser = enemy_erase;

        static const float posX = obj->pos.x;       //初期位置
        obj->ReferencePosition = obj->pos.x;
        // 初期設定
        Find::getInstance()->init();
        ++obj->state;
        //break;
    case 1:
        if (obj->pos.y >= 450)++obj->state;

        obj->holdPosX = player.pos.x;
        break;
    case 2:
        // 左に進む
        obj->pos.x -= move;
        if (obj->pos.x <= obj->ReferencePosition - 100)
        {
            obj->state = 3;
            if (obj->scale.x > 0)obj->scale.x *= -1;
        }

        // 背景スクロールに合わせる
        dist = obj->holdPosX;
        obj->holdPosX = player.pos.x;
        if (dist != obj->holdPosX)
        {
            obj->pos.x += (dist - obj->holdPosX) * 3.0f;
            obj->ReferencePosition += (dist - obj->holdPosX) * 3.0f;
        }

        // アニメーション
        anime(obj, 2, 15, true, 0);

        dist_len(obj, &player);

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

        // 背景スクロールに合わせる
        dist = obj->holdPosX;
        obj->holdPosX = player.pos.x;
        if (dist != obj->holdPosX)
        {
            obj->pos.x += (dist - obj->holdPosX) * 3.0f;
            obj->ReferencePosition += (dist - obj->holdPosX) * 3.0f;
        }

        // アニメーション
        anime(obj, 2, 15, true, 0);

        dist_len(obj, &player);

        // 見つける
        if (hitCheck(&player, obj, HITCHECK::PLAndENEScope))
            if (player.pos.x > obj->pos.x)obj->state = 4;

        break;
    case 4:

        Find::getInstance()->searchSet(find, VECTOR2(obj->pos.x, obj->pos.y - 100));

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

        // 背景スクロールに合わせる
        dist = obj->holdPosX;
        obj->holdPosX = player.pos.x;
        if (dist != obj->holdPosX)
        {
            obj->pos.x += (dist - obj->holdPosX) * 3.0f;
            obj->ReferencePosition += (dist - obj->holdPosX) * 3.0f;
        }

        // アニメーション
        anime(obj, 2, 15, true, 0);

        // 食べてるみたいで面白い
        //// プレイヤーと敵の距離
        //float dist = player.pos.x - obj->pos.x;    
        //if (dist < 0)dist *= -1;
        //// プレイヤーと敵の離しておきたい距離
        //float len = player.radius + obj->radius;
        //if (dist < len)obj->pos.x = player.pos.x + obj->radius;
        
        dist_len(obj, &player);

        break;
    }



    
    
    

    //
    if (player.half && obj->half)
    {
        obj->half = false;
        obj->hp -= 1;
        obj->invincible = true;
    }

    // 無敵時間(発動中)
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
    // 無敵時間終了
    if (obj->invincibleTimer >= 60)
    {
        obj->invincible = false;
        obj->invincibleTimer = 0;
        obj->color.w = 1;
    }

    // 重力
    gravity(obj);

}


void dist_len(OBJ2D* obj,OBJ2D* player)
{        
    // プレイヤーと敵の距離
    float dist = player->pos.x - obj->pos.x;
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
    float len = player->radius + obj->radius;
    if (dist < len)
        obj->pos.x = right ? player->pos.x + len : player->pos.x - len;

}