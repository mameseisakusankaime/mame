#include "common.h"
#include "player.h"
#include "gimmick.h"
#include "SceneGame.h"
#include "enemy.h"

void Gimmick::init()
{
    this->searchSet(gimmick_Blok, { 300,400 });
    this->searchSet(gimmick_Button, { 300,600 });
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
        obj->data = GameLib::sprite_load(L"./Data/Images/enemy.png");//HACK:テクスチャ変更
        obj->pos = { 900,GROUND };
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
        obj->pos = { 1000,GROUND };
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

