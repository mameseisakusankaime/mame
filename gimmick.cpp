#include "common.h"
#include "player.h"
#include "gimmick.h"
#include "SceneGame.h"
#include "enemy.h"

void Gimmick::init()
{
    this->searchSet(gimmick_Blok, { 900,GROUND });
    this->searchSet(gimmick_Button, { 2000,GROUND });
    this->searchSet(gimmick_door, { 4500,GROUND });
    this->searchSet(gimmick_door, { 500,GROUND });
}

bool gimmick_erase(OBJ2D* obj)
{
    return false;
}


//�U�����������u���b�N
void gimmick_Blok(OBJ2D* obj)
{
    auto&& player = Player::getInstance()->begin();
    switch (obj->state)
    {
    case 0:
        obj->data = GameLib::sprite_load(L"./Data/Images/terrain.png");//HACK:�e�N�X�`���ύX
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
        //�w�i�X�N���[���ɍ��킹��
    {
        float dist = obj->holdPosX;
        obj->holdPosX = player->pos.x;
        if (dist != obj->holdPosX)
        {
            obj->pos.x += (dist - obj->holdPosX) * 3.0f;
            obj->ReferencePosition += (dist - obj->holdPosX) * 3.0f;
        }
    }
    //�����蔻��
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

//gimmick    �����ƓG���o�Ă���{�^��
void gimmick_Button(OBJ2D* obj)
{
    auto&& player = Player::getInstance()->begin();
    switch (obj->state)
    {
    case 0:
        obj->data = GameLib::sprite_load(L"./Data/Images/enemy.png");//HACK:�e�N�X�`���ύX
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
            Enemy::getInstance()->searchSet(enemy_walk, obj->pos + VECTOR2(300,  -200));
            Enemy::getInstance()->searchSet(enemy_walk, obj->pos + VECTOR2(600,  -200));
            Enemy::getInstance()->searchSet(enemy_walk, obj->pos + VECTOR2(-300, -200));
            Enemy::getInstance()->searchSet(enemy_walk, obj->pos + VECTOR2(-600, -200));

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
        obj->data = GameLib::sprite_load(L"./Data/Images/door.png");
        obj->scale = { 1,1 };
        obj->texPos = { 0,0 };
        obj->texSize = { 270,256 };
        obj->pivot = { 135,128 };
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
            dist_len(player, obj);
            obj->state++;
            break;
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
    case 2:
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
            dist_len(player, obj);

        obj->texPos.x = (std::min)(obj->texPos.x+obj->texSize.x, 256.0f * 5.0f);
        obj->pivot.x = (std::min)(obj->pivot.x, 256.0f * 5.0f - 128.0f);
        if (obj->texPos.x >= 256 * 4.9f)
        {
            setScene(SCENE::CLEAR);
        }

        break;
    }
    obj->timer++;

}

