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
 
// ただ歩くだけの敵
void enemy_walk(OBJ2D* obj)
{
    OBJ2D* player = Player::getInstance()->begin(); //プレイヤー

    float move = 0.5f;   // 移動速度
    float dist;

    switch (obj->state)
    {
    case 0:
        // 初期設定
        //obj->data = sprite_load(L"./Data/Images/enemy.png");
        obj->data = sprite_load(L"./Data/Images/enemy_attack.png");
        //obj->pos = { 900,200 };
        obj->scale = { 0.5f,0.5f };
        obj->texPos = { 0,0 };
        obj->texSize = { 512,512 };
        obj->pivot = { 384,384 };
        obj->type = DATA::WALK;
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

        obj->holdPosX = player->pos.x;
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
        obj->holdPosX = player->pos.x;
        if (dist != obj->holdPosX)
        {
            obj->pos.x += (dist - obj->holdPosX) * 3.0f;
            obj->ReferencePosition += (dist - obj->holdPosX) * 3.0f;
        }

        // アニメーション
        anime(obj, 2, 15, true, 0);

        dist_len(obj, player);

        // 見つける
        if (hitCheck(player, obj, HITCHECK::PLAndENEScope))
            if (player->pos.x < obj->pos.x)obj->state = 4;


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
        obj->holdPosX = player->pos.x;
        if (dist != obj->holdPosX)
        {
            obj->pos.x += (dist - obj->holdPosX) * 3.0f;
            obj->ReferencePosition += (dist - obj->holdPosX) * 3.0f;
        }

        // アニメーション
        anime(obj, 2, 15, true, 0);

        dist_len(obj, player);

        // 見つける
        if (hitCheck(player, obj, HITCHECK::PLAndENEScope))
            if (player->pos.x > obj->pos.x)obj->state = 4;


        break;
    case 4:

        Find::getInstance()->searchSet(find, VECTOR2(obj->pos.x, obj->pos.y - 100));

        ++obj->state;
        break;
    case 5:
        // プレイヤーの方向に向かって進む
        if (player->pos.x > obj->pos.x)
        {
            obj->pos.x += move;
            // 画像を進行方向へ向ける
            if (obj->scale.x > 0)obj->scale.x *= -1;
        }
        if (player->pos.x < obj->pos.x)
        {
            obj->pos.x -= move;
            // 画像を進行方向へ向ける
            if (obj->scale.x < 0)obj->scale.x *= -1;
        }

        // 背景スクロールに合わせる
        dist = obj->holdPosX;
        obj->holdPosX = player->pos.x;
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
        
        dist_len(obj, player);

        break;
    }

    // 
    if (player->half && obj->half)
    {
        obj->half = false;
        obj->hp -= 1;
        obj->invincible = true;
        
        if (obj->hp <= 0)
            player->type = obj->type;
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

// 見つかると攻撃してくる敵
void enemy_attack(OBJ2D* obj)
{
    OBJ2D* player = &Player::getInstance()->obj_w[0]; // プレイヤー

    float move = 0.5f;   // 移動速度
    float dist;

    switch (obj->state)
    {
    case 0:
        obj->data = sprite_load(L"./Data/Images/enemy_attack.png");
        obj->scale = { 0.5f,0.5f };
        obj->texPos = { 0,0 };
        obj->texSize = { 512,512 };
        obj->pivot = { 384,384 };
        obj->type = DATA::ATTACK;
        obj->radius = 40;
        obj->hp = 2;
        obj->foundRadius = 200;
        obj->attackRadius = 100;
        obj->eraser = enemy_erase;


        obj->ReferencePosition = obj->pos.x;

        // 初期設定
        Find::getInstance()->init();

        ++obj->state;
        //break;
    case 1: // 敵を初期位置にセット
        if (obj->pos.y >= 450)++obj->state;

        obj->holdPosX = player->pos.x;
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
        obj->holdPosX = player->pos.x;
        if (dist != obj->holdPosX)
        {
            obj->pos.x += (dist - obj->holdPosX) * 3.0f;
            obj->ReferencePosition += (dist - obj->holdPosX) * 3.0f;
        }

        // アニメーション
        anime(obj, 2, 15, true, 0);

        // 当たり判定で離す距離
        dist_len(obj, player);

        // 見つける
        if (hitCheck(player, obj, 1))
            if (player->pos.x < obj->pos.x)obj->state = 4;

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
        obj->holdPosX = player->pos.x;
        if (dist != obj->holdPosX)
        {
            obj->pos.x += (dist - obj->holdPosX) * 3.0f;
            obj->ReferencePosition += (dist - obj->holdPosX) * 3.0f;
        }

        // アニメーション
        anime(obj, 2, 15, true, 0);

        // 当たり判定で離す距離
        dist_len(obj, player);

        // 見つける
        if (hitCheck(player, obj, 1))
            if (player->pos.x > obj->pos.x)obj->state = 4;
        break;
    case 4:
        // ビックリマークを出す
        Find::getInstance()->searchSet(find, VECTOR2(obj->pos.x, obj->pos.y - 100));
        obj->state = 5;
        break;
    case 5:
        // プレイヤーの方向に向かって進む
        if (player->pos.x > obj->pos.x)
        {
            obj->pos.x += move;
            // 画像を進行方向へ向ける
            if (obj->scale.x > 0)obj->scale.x *= -1;
        }
        if (player->pos.x < obj->pos.x)
        {
            obj->pos.x -= move;
            // 画像を進行方向へ向ける
            if (obj->scale.x < 0)obj->scale.x *= -1;
        }

        // 背景スクロールに合わせる
        dist = obj->holdPosX;
        obj->holdPosX = player->pos.x;
        if (dist != obj->holdPosX)
        {
            obj->pos.x += (dist - obj->holdPosX) * 3.0f;
            obj->ReferencePosition += (dist - obj->holdPosX) * 3.0f;
        }

        // アニメーション
        anime(obj, 2, 15, true, 0);

        // 当たり判定で離す距離
        dist_len(obj, player);

        if (hitCheck(player, obj, 3))
        {
            obj->state = 6;
            obj->attack = true;
            obj->animeState = 0;
            break;
        }

        break;
    case 6:
        // 攻撃モーション

        anime(obj, 12, 3, false, 1);

        if (obj->end)
        {
            //player.pos.x -= 20;
            if(Player::getInstance()->obj_w[0].invincible==false)
                Player::getInstance()->reduceHp();

            obj->texPos.x = 0;
            obj->state = 5;
            obj->end = false;
            obj->animeState = 0;
        }

        // 背景スクロールに合わせる
        dist = obj->holdPosX;
        obj->holdPosX = player->pos.x;
        if (dist != obj->holdPosX)
        {
            obj->pos.x += (dist - obj->holdPosX) * 3.0f;
            obj->ReferencePosition += (dist - obj->holdPosX) * 3.0f;
        }



        // 当たり判定で離す距離
        dist_len(obj, player);

        break;
    }
    //
    if (player->half && obj->half)
    {
        obj->half = false;
        obj->hp -= 1;
        obj->invincible = true;

        if (obj->hp <= 0)
            player->type = obj->type;
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
    obj->pos.y += 5;
    if (obj->pos.y >= 450)obj->pos.y = 450;
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