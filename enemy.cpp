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
 
// �������������̓G
void enemy_walk(OBJ2D* obj)
{
    OBJ2D* player = Player::getInstance()->begin(); //�v���C���[

    float move = 0.5f;   // �ړ����x
    float dist;

    switch (obj->state)
    {
    case 0:
        // �����ݒ�
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

        static const float posX = obj->pos.x;       //�����ʒu
        obj->ReferencePosition = obj->pos.x;
        // �����ݒ�
        Find::getInstance()->init();
        ++obj->state;
        //break;
    case 1:
        if (obj->pos.y >= 450)++obj->state;

        obj->holdPosX = player->pos.x;
        break;
    case 2:
        // ���ɐi��
        obj->pos.x -= move;
        if (obj->pos.x <= obj->ReferencePosition - 100)
        {
            obj->state = 3;
            if (obj->scale.x > 0)obj->scale.x *= -1;
        }

        // �w�i�X�N���[���ɍ��킹��
        dist = obj->holdPosX;
        obj->holdPosX = player->pos.x;
        if (dist != obj->holdPosX)
        {
            obj->pos.x += (dist - obj->holdPosX) * 3.0f;
            obj->ReferencePosition += (dist - obj->holdPosX) * 3.0f;
        }

        // �A�j���[�V����
        anime(obj, 2, 15, true, 0);

        dist_len(obj, player);

        // ������
        if (hitCheck(player, obj, HITCHECK::PLAndENEScope))
            if (player->pos.x < obj->pos.x)obj->state = 4;


        break;
    case 3:
        // �E�ɐi��
        obj->pos.x += move;
        if (obj->pos.x >= obj->ReferencePosition + 100)
        {
            obj->state = 2;
            if (obj->scale.x < 0)obj->scale.x *= -1;
        }

        // �w�i�X�N���[���ɍ��킹��
        dist = obj->holdPosX;
        obj->holdPosX = player->pos.x;
        if (dist != obj->holdPosX)
        {
            obj->pos.x += (dist - obj->holdPosX) * 3.0f;
            obj->ReferencePosition += (dist - obj->holdPosX) * 3.0f;
        }

        // �A�j���[�V����
        anime(obj, 2, 15, true, 0);

        dist_len(obj, player);

        // ������
        if (hitCheck(player, obj, HITCHECK::PLAndENEScope))
            if (player->pos.x > obj->pos.x)obj->state = 4;


        break;
    case 4:

        Find::getInstance()->searchSet(find, VECTOR2(obj->pos.x, obj->pos.y - 100));

        ++obj->state;
        break;
    case 5:
        // �v���C���[�̕����Ɍ������Đi��
        if (player->pos.x > obj->pos.x)
        {
            obj->pos.x += move;
            // �摜��i�s�����֌�����
            if (obj->scale.x > 0)obj->scale.x *= -1;
        }
        if (player->pos.x < obj->pos.x)
        {
            obj->pos.x -= move;
            // �摜��i�s�����֌�����
            if (obj->scale.x < 0)obj->scale.x *= -1;
        }

        // �w�i�X�N���[���ɍ��킹��
        dist = obj->holdPosX;
        obj->holdPosX = player->pos.x;
        if (dist != obj->holdPosX)
        {
            obj->pos.x += (dist - obj->holdPosX) * 3.0f;
            obj->ReferencePosition += (dist - obj->holdPosX) * 3.0f;
        }

        // �A�j���[�V����
        anime(obj, 2, 15, true, 0);

        // �H�ׂĂ�݂����Ŗʔ���
        //// �v���C���[�ƓG�̋���
        //float dist = player.pos.x - obj->pos.x;    
        //if (dist < 0)dist *= -1;
        //// �v���C���[�ƓG�̗����Ă�����������
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

    // ���G����(������)
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
    // ���G���ԏI��
    if (obj->invincibleTimer >= 60)
    {
        obj->invincible = false;
        obj->invincibleTimer = 0;
        obj->color.w = 1;
    }

    // �d��
    gravity(obj);

}

// ������ƍU�����Ă���G
void enemy_attack(OBJ2D* obj)
{
    OBJ2D* player = &Player::getInstance()->obj_w[0]; // �v���C���[

    float move = 0.5f;   // �ړ����x
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

        // �����ݒ�
        Find::getInstance()->init();

        ++obj->state;
        //break;
    case 1: // �G�������ʒu�ɃZ�b�g
        if (obj->pos.y >= 450)++obj->state;

        obj->holdPosX = player->pos.x;
        break;
    case 2:
        // ���ɐi��
        obj->pos.x -= move;
        if (obj->pos.x <= obj->ReferencePosition - 100)
        {
            obj->state = 3;
            if (obj->scale.x > 0)obj->scale.x *= -1;
        }

        // �w�i�X�N���[���ɍ��킹��
        dist = obj->holdPosX;
        obj->holdPosX = player->pos.x;
        if (dist != obj->holdPosX)
        {
            obj->pos.x += (dist - obj->holdPosX) * 3.0f;
            obj->ReferencePosition += (dist - obj->holdPosX) * 3.0f;
        }

        // �A�j���[�V����
        anime(obj, 2, 15, true, 0);

        // �����蔻��ŗ�������
        dist_len(obj, player);

        // ������
        if (hitCheck(player, obj, 1))
            if (player->pos.x < obj->pos.x)obj->state = 4;

        break;
    case 3:
        // �E�ɐi��
        obj->pos.x += move;
        if (obj->pos.x >= obj->ReferencePosition + 100)
        {
            obj->state = 2;
            if (obj->scale.x < 0)obj->scale.x *= -1;
        }

        // �w�i�X�N���[���ɍ��킹��
        dist = obj->holdPosX;
        obj->holdPosX = player->pos.x;
        if (dist != obj->holdPosX)
        {
            obj->pos.x += (dist - obj->holdPosX) * 3.0f;
            obj->ReferencePosition += (dist - obj->holdPosX) * 3.0f;
        }

        // �A�j���[�V����
        anime(obj, 2, 15, true, 0);

        // �����蔻��ŗ�������
        dist_len(obj, player);

        // ������
        if (hitCheck(player, obj, 1))
            if (player->pos.x > obj->pos.x)obj->state = 4;
        break;
    case 4:
        // �r�b�N���}�[�N���o��
        Find::getInstance()->searchSet(find, VECTOR2(obj->pos.x, obj->pos.y - 100));
        obj->state = 5;
        break;
    case 5:
        // �v���C���[�̕����Ɍ������Đi��
        if (player->pos.x > obj->pos.x)
        {
            obj->pos.x += move;
            // �摜��i�s�����֌�����
            if (obj->scale.x > 0)obj->scale.x *= -1;
        }
        if (player->pos.x < obj->pos.x)
        {
            obj->pos.x -= move;
            // �摜��i�s�����֌�����
            if (obj->scale.x < 0)obj->scale.x *= -1;
        }

        // �w�i�X�N���[���ɍ��킹��
        dist = obj->holdPosX;
        obj->holdPosX = player->pos.x;
        if (dist != obj->holdPosX)
        {
            obj->pos.x += (dist - obj->holdPosX) * 3.0f;
            obj->ReferencePosition += (dist - obj->holdPosX) * 3.0f;
        }

        // �A�j���[�V����
        anime(obj, 2, 15, true, 0);

        // �����蔻��ŗ�������
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
        // �U�����[�V����

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

        // �w�i�X�N���[���ɍ��킹��
        dist = obj->holdPosX;
        obj->holdPosX = player->pos.x;
        if (dist != obj->holdPosX)
        {
            obj->pos.x += (dist - obj->holdPosX) * 3.0f;
            obj->ReferencePosition += (dist - obj->holdPosX) * 3.0f;
        }



        // �����蔻��ŗ�������
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

    // ���G����(������)
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
    // ���G���ԏI��
    if (obj->invincibleTimer >= 60)
    {
        obj->invincible = false;
        obj->invincibleTimer = 0;
        obj->color.w = 1;
    }

    // �d��
    obj->pos.y += 5;
    if (obj->pos.y >= 450)obj->pos.y = 450;
}

void dist_len(OBJ2D* obj,OBJ2D* player)
{        
    // �v���C���[�ƓG�̋���
    float dist = player->pos.x - obj->pos.x;
    // �G���ǂ����ɂ��邩(�E����true)
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
    // �v���C���[�ƓG�̗����Ă�����������
    float len = player->radius + obj->radius;
    if (dist < len)
        obj->pos.x = right ? player->pos.x + len : player->pos.x - len;

}