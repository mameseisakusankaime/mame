#include "common.h"
#include "player.h"
#include "gimmick.h"
#include "SceneGame.h"
#include "enemy.h"

void Gimmick::init()
{
    this->searchSet(gimmick_Blok, { 900,GROUND });
    this->searchSet(gimmick_Button, { 1000,GROUND });
}

bool gimmick_erase(OBJ2D* obj)
{
    return false;
}


//攻撃したら壊れるブロック
void gimmick_Blok(OBJ2D* obj)
{
    auto&& player = Player::getInstance()->begin();
    switch (obj->state)
    {
    case 0:
        obj->data = GameLib::sprite_load(L"./Data/Images/terrain.png");//HACK:テクスチャ変更
        obj->scale = { 2,2 };
        obj->texPos = { 0,0 };
        obj->texSize = { 64,64 };
        obj->pivot = { 32,32 };
        obj->radius = 40;
        obj->hp = 1;
        obj->eraser = gimmick_erase;

        obj->state++;
        //break;
    case 1:
        //背景スクロールに合わせる
    {
        float dist = obj->holdPosX;
        obj->holdPosX = player->pos.x;
        if (dist != obj->holdPosX)
        {
            obj->pos.x += (dist - obj->holdPosX) * 3.0f;
            obj->ReferencePosition += (dist - obj->holdPosX) * 3.0f;
        }
    }
    //当たり判定
        if (hitCheck(player,obj,HITCHECK::PLAndENE))
        {
            //player->pos = obj->pos - vec2Normalize(player->pos - obj->pos) * (player->radius + obj->radius);
            dist_len(player, obj);
        }
        for (auto&& enemy : *Enemy::getInstance())
        {
            if (!enemy.mover)continue;
            if (hitCheck(&enemy, obj, HITCHECK::PLAndENE))
            {
                dist_len(&enemy, obj);
            }
        }
    }
}

//gimmick    押すと敵が出てくるボタン
void gimmick_Button(OBJ2D* obj)
{
    auto&& player = Player::getInstance()->begin();
    switch (obj->state)
    {
    case 0:
        obj->data = GameLib::sprite_load(L"./Data/Images/enemy.png");//HACK:テクスチャ変更
        obj->scale = { 1,1 };
        obj->texPos = { 0,0 };
        obj->texSize = { 256,256 };
        obj->pivot = { 128,128 };
        obj->radius = 40;
        obj->hp = 1;
        obj->eraser = gimmick_erase;
        
        obj->state++;
        //break;
    case 1:
    {
        float dist = obj->holdPosX;
        obj->holdPosX = player->pos.x;
        if (dist != obj->holdPosX)
        {
            obj->pos.x += (dist - obj->holdPosX) * 3.0f;
            obj->ReferencePosition += (dist - obj->holdPosX) * 3.0f;
        }
    }
        if (hitCheck(obj, player, HITCHECK::PLAndENE))
        {
            Enemy::getInstance()->searchSet(enemy_walk, obj->pos + VECTOR2(100,  -100));
            Enemy::getInstance()->searchSet(enemy_walk, obj->pos + VECTOR2(200,  -100));
            Enemy::getInstance()->searchSet(enemy_walk, obj->pos + VECTOR2(-100, -100));
            Enemy::getInstance()->searchSet(enemy_walk, obj->pos + VECTOR2(-200, -100));

            obj->clear();
            break;
        }

    }
}

void gimmick_door(OBJ2D* obj)
{
    auto&& player = Player::getInstance()->begin();
    switch (obj->state)
    {
    case 0:
        obj->data = GameLib::sprite_load(L"./Data/Images/door.png");//HACK:テクスチャ変更
        obj->scale = { 1,1 };
        obj->texPos = { 0,0 };
        obj->texSize = { 270,270 };
        obj->pivot = { 135,135 };
        obj->radius = 40;
        obj->hp = 1;
        obj->eraser = gimmick_erase;

        obj->state++;
        //break;
    case 1:
    {
        float dist = obj->holdPosX;
        obj->holdPosX = player->pos.x;
        if (dist != obj->holdPosX)
        {
            obj->pos.x += (dist - obj->holdPosX) * 3.0f;
            obj->ReferencePosition += (dist - obj->holdPosX) * 3.0f;
        }
    }

        if (hitCheck(player, obj, HITCHECK::PLAndENE))
        {
            //player->pos = obj->pos - vec2Normalize(player->pos - obj->pos) * (player->radius + obj->radius);
            if (player->key)
            {
                obj->clear();
            }
            else
            {
                dist_len(player, obj);
            }
        }
        for (auto&& enemy : *Enemy::getInstance())
        {
            if (!enemy.mover)continue;
            if (hitCheck(&enemy, obj, HITCHECK::PLAndENE))
            {
                dist_len(&enemy, obj);
            }
        }


        break;
    }

}

