#include "all.h"

void SceneGame::init()
{
    state = 0;
    timer = 0;
}

void SceneGame::deinit()
{
    safe_delete(data);

    // �w�i�I������
    Back::getInstance()->deinit();
    // �v���C���[�I������
    Player::getInstance()->deinit();
    // �G�I������
    Enemy::getInstance()->deinit();
    // ���[��
    Gage::getInstance()->deinit();
    //
    Find::getInstance()->deinit();
}

void SceneGame::update()
{
    switch (state)
    {
    case 0:
        GameLib::setBlendMode(Blender::BS_ALPHA);

        // �摜�ǂݍ���
        sprLoad = sprite_load(L"./Data/Images/loading_back.png");
        sprWord = sprite_load(L"./Data/Images/loading_character.png");

        // �w�i�����ݒ�
        Back::getInstance()->init();

        Back::getInstance()->searchSet(back_update0, VECTOR2(0,0));
        Back::getInstance()->searchSet(back_update0, VECTOR2(5120,0));
        Back::getInstance()->searchSet(back_update1, VECTOR2(0,0));
        Back::getInstance()->searchSet(back_update1, VECTOR2(5120,0));
        Back::getInstance()->searchSet(back_update2, VECTOR2(0,0));
        Back::getInstance()->searchSet(back_update2, VECTOR2(5120,0));
        Back::getInstance()->searchSet(back_update3, VECTOR2(0,0));
        Back::getInstance()->searchSet(back_update3, VECTOR2(5120,0));
        Back::getInstance()->searchSet(back_update3, VECTOR2(7680,0));

        // �v���C���[�����ݒ�
        Player::getInstance()->init();
        // �G�����ݒ�
        Enemy::getInstance()->init();
        //�Q�[�W
        Gage::getInstance()->init();
        // 
        //Find::getInstance()->init();

        ++state;
        //break;
    case 1:
        //if (TRG(0) & PAD_START)setScene(SCENE::TITLE);

#ifdef _DEBUG
        debug::setString("0%d", Enemy::getInstance()->obj_w[0].state);
        debug::setString("1%d", Enemy::getInstance()->obj_w[1].state);
        debug::setString("2%d", Enemy::getInstance()->obj_w[2].state);
#endif

        // �w�i�X�V
        Back::getInstance()->update();
        // �G�X�V����
        Enemy::getInstance()->update();
        // �v���C���[�X�V����
        Player::getInstance()->update();
        //�Q�[�W
        Gage::getInstance()->update();
        //
        Find::getInstance()->update();

        judge();

        if (TRG(0) & PAD_R1)
        {
            if(!Player::getInstance()->obj_w[0].attack)player_attack();
        }

        //if (Player::getInstance()->obj_w[0].attack)
        //    anime(&Player::getInstance()->obj_w[0], 13, 2, false, 0);

        if (TRG(0) & PAD_L1)
        {
            
            if (Enemy::getInstance()->obj_w[0].mover == 0)
            {
                Enemy::getInstance()->searchSet(enemy_walk, enemy_position[0]);
            }
            else
            {
                Enemy::getInstance()->obj_w[0].hp = Enemy::getInstance()->obj_w[0].hp <= 1 ? 2 : 0;
            }
        }

       
        if (timer == 0)
            Enemy::getInstance()->searchSet(enemy_attack, enemy_position[0]);
        if (timer == 2)
            Enemy::getInstance()->searchSet(enemy_attack, enemy_position[1]);
        if (timer == 4)
            Enemy::getInstance()->searchSet(enemy_attack, enemy_position[2]);
        if (timer == 10)
            Enemy::getInstance()->searchSet(enemy_attack, enemy_position[3]);
        if (timer == 20)
            Enemy::getInstance()->searchSet(enemy_attack, enemy_position[4]);

        ++timer;

        break;
    }
}

void SceneGame::draw()
{
    GameLib::clear(1, 1, 1);



    // �w�i�`��
    Back::getInstance()->draw();
    // �G�`�揈��
    Enemy::getInstance()->draw();
    // �Q�[�W
    Gage::getInstance()->draw();
    // 
    Find::getInstance()->draw();

    // �v���C���[�`�揈��
    Player::getInstance()->draw();

    OBJ2D* plat = &Player::getInstance()->obj_w[0];

#ifdef _DEBUG
    //primitive::circle(plat->pos, plat->radius, VECTOR2(1, 1), 0.0f, VECTOR4(0, 1, 0, 0.2f));
    //primitive::circle(plat->pos, plat->foundRadius, VECTOR2(1, 1), 0.0f, VECTOR4(0, 0, 1, 0.2f));
#endif
       
    OBJ2D* elat = &Enemy::getInstance()->obj_w[0];
    
#ifdef _DEBUG
    primitive::circle(elat->pos, elat->radius, VECTOR2(1, 1), 0.0f, VECTOR4(0, 0, 1, 0.4f));
    //primitive::circle(elat->pos, elat->foundRadius, VECTOR2(1, 1), 0.0f, VECTOR4(0, 0, 1, 0.4f));
    //primitive::circle(elat->pos, elat->attackRadius, VECTOR2(1, 1), 0.0f, VECTOR4(1, 0, 0, 0.4f));
#endif

    if (timer < 60)
    {
        sprite_render(sprLoad, 0, 0);
        sprite_render(sprWord, 0, 0);
    }

}

/// <summary>
/// �A�j���[�V�����֐�
/// </summary>
/// <param name="obj">�L�����N�^�[</param>
/// <param name="total">�摜����</param>
/// <param name="flame">�t���[��</param>
/// <param name="loop">���[�v���邩</param>
/// <param name="type">���ʉ��̃^�C�v(�ʏ�O�ł���)</param>
void anime(OBJ2D* obj, int total, int flame, bool loop, int type)
{
    // type 0 player
    // type 1 enemy_attack
    // type 10 player_attack

    switch (obj->animeState)
    {
    case 0:
        obj->texPos.x = 0;
        obj->anime = obj->animeTimer = 0;
        obj->end = false;
        obj->one = false;
        obj->half = false;
        

        ++obj->animeState;
    case 1:
        if (loop)
        {
            obj->anime = obj->animeTimer / flame;
            if (obj->anime >= total)
            {
                obj->anime = 0;
                obj->animeTimer = 0;
            }
            obj->texPos.x = obj->anime * obj->texSize.x;
            ++obj->animeTimer;
        }
        else
        {
            if (obj->attack)
            {
                // �U���J�n
                if (!obj->one)
                {
                    if (type == 0|| type == 1)
                        obj->texPos.y = 512;
                    
                    if (type == 10)
                        obj->texPos.y = 2560.0f;
                }

                // �U���A�j��
                obj->anime = obj->animeTimer / flame;
                if (obj->anime >= total - 1)obj->one = true;
                if (obj->anime >= total)
                {
                    obj->anime = total - 1;
                    //obj->end = true;
                    return;
                }
                obj->texPos.x = obj->anime * obj->texSize.x;

                // �U���I��
                if (obj->one)
                {

                    obj->anime = obj->animeTimer = 0;
                    obj->end = false;
                    obj->one = false;
                    obj->half = true;

                    if (type != 1)
                        ++obj->animeState;
                    else
                        obj->end = true;

                    // 
                    //enemy->hp -= 1;
                    //enemy->invincible = true;
                }

                ++obj->animeTimer;
            }
            else
            {
                obj->anime = obj->animeTimer / flame;
                if (obj->anime >= total - 1)obj->one = true;
                if (obj->anime >= total)
                {
                    obj->anime = total - 1;
                    //obj->end = true;
                    return;
                }
                obj->texPos.x = obj->anime * obj->texSize.x;

                ++obj->animeTimer;
            }
        }
        break;
    case 2:
        // �������߂�̊J�n
        if (type == 0)
            obj->texPos.y = 512 * 2;
        if (type == 10)
            obj->texPos.y = 3072.0f;

        // �������߂�A�j��
        obj->anime = obj->animeTimer / flame;
        if (obj->anime >= total - 1)obj->one = true;
        if (obj->anime >= total)
        {
            obj->anime = total - 1;
            obj->end = true;
            return;
        }
        obj->texPos.x = obj->anime * obj->texSize.x;

        // �Ђ����ߏI��
        if (obj->one)
        {
            // �摜�ʒu��ݒ�
            if(type==0)
                obj->texPos = {};
            if (type == 10)
                obj->texPos = { 0,2048.0f };
            
            obj->anime = obj->animeTimer = 0;
            obj->end = true;
            obj->one = false;
            obj->attack = false;
            obj->half = false;
            //obj->animeState = 0;
        }

        ++obj->animeTimer;
        break;
    }

}

//--------------------------------------
//  �~�Ɖ~�̂����蔻��
//--------------------------------------
bool hitCheckCircle(VECTOR2 pos1, float r1, VECTOR2 pos2, float r2)
{
    float dx = pos2.x - pos1.x;
    float dy = pos2.y - pos1.y;
    float r = r1 + r2;

    if (dx * dx + dy * dy <= r * r)
        return true;

    return false;
}

//--------------------------------------
//  OBJ2D���m�̂����蔻��
//--------------------------------------
bool hitCheck(OBJ2D* obj1, OBJ2D* obj2,int num)
{
    switch (num)
    {
    case 0: 
        // �v���C���[�ƓG
        return hitCheckCircle(
            obj1->pos + obj1->offset, obj1->radius,
            obj2->pos + obj2->offset, obj2->radius
        );
        break;
    case 1:
        // �v���C���[�ƓG�͈�
        return hitCheckCircle(
            obj1->pos + obj1->offset, obj1->radius,
            obj2->pos + obj2->offset, obj2->foundRadius
        );
        break;
    case 2:
        // �v���C���[�͈͂ƓG
        return hitCheckCircle(
            obj1->pos + obj1->offset, obj1->foundRadius,
            obj2->pos + obj2->offset, obj2->radius
        );
        break;
    case 3:
        // �v���C���[�ƓG�̍U���͈�
        return hitCheckCircle(
            obj1->pos + obj1->offset, obj1->radius,
            obj2->pos + obj2->offset, obj2->attackRadius
        );
        break;
    }
}

//--------------------------------------
//  �����蔻��
//--------------------------------------
void judge()
{
    OBJ2D* player = &Player::getInstance()->obj_w[0];
    
    
    OBJ2D* enemy[10];
    int num = 0;
    for (auto& obj : enemy)
    {
        obj = &Enemy::getInstance()->obj_w[num];
        ++num;
    }

    for (int i = 0; i < 10; ++i)
    {
        if (enemy[i]->mover == nullptr)continue;

        if (hitCheck(player, enemy[i],0))
        {
            debug::setString("hit!!");

            if (player->invincible)continue;

            player->hp -= 1;
            player->invincible = true;

            if (player->hp <= 0)setScene(SCENE::OVER);
        }
    }

    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            if (i == j)continue;
            if (hitCheck(enemy[i], enemy[j], 0))
            {
                // ���̋���
                float dist = enemy[i]->pos.x - enemy[j]->pos.x;
                // �ǂ����ɂ��邩
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
                // ������������
                float len = enemy[i]->radius + enemy[j]->radius;
                if (dist < len)
                    enemy[j]->pos.x = right ? enemy[i]->pos.x + len : enemy[i]->pos.x - len;
            }
        }
    }


    /*for (int i = 0; i < ENEMY_MAX; ++i)
    {
        if (!enemy[i].moveAlg)              continue;
        if (enemy[i].area != player.area)   continue;

        if (hitCheck(&player, &enemy[i]))
        {
            game_reset();
        }
    }*/ 
}

void player_attack()
{
    OBJ2D* player = &Player::getInstance()->obj_w[0];
    OBJ2D* enemy[10];
    int num = 0;
    for (auto& obj : enemy)
    {
        obj = &Enemy::getInstance()->obj_w[num];
        ++num;
    }

    for (int i = 0; i < 10; ++i)
    {
        if (enemy[i]->mover == nullptr)continue;

        if (hitCheck(player, enemy[i], 2))
        {
            // �v���C���[�ƓG�̋���
            float dist = player->pos.x - enemy[i]->pos.x;
            bool right;
            if (dist < 0)right = true;
            else right = false;

            if (right && player->scale.x > 0 || !right && player->scale.x < 0)
                enemy[i]->half = true;

            //player->type = enemy[i]->type;

            //enemy[i]->hp -= 1;
            //enemy[i]->invincible = true;
        }
    }
    player->attack = true;
    //if(TRG(0)&PAD_START)player->animeState = 0;
}

//// �ǂƂ̓����蔻��
//bool hitCheck(OBJ2D* rc1, OBJ2D* rc2)
//{
//    const float rc1Left = rc1->pos.x;
//    const float rc1Right = rc1->pos.x + rc1->texSize.x;
//    const float rc1Top = rc1->pos.y;
//    const float rc1Bottom = rc1->pos.y + rc1->texSize.y;
//
//    const float rc2Left = rc2->pos.x;
//    const float rc2Right = rc2->pos.x + rc2->texSize.x;
//    const float rc2Top = rc2->pos.y;
//    const float rc2Bottom = rc2->pos.y + rc2->texSize.y;
//
//    if (rc1Left >= rc2Right)return false;
//    if (rc1Right <= rc2Left)return false;
//    if (rc1Top >= rc2Bottom)return false;
//    if (rc1Bottom <= rc2Top)return false;
//
//    return true;
//}
//
//
//// �ǂƂ̂߂荞�ݔ���
//float check(OBJ2D* rc1, OBJ2D* rc2, int dir) {
//    switch (dir)
//    {
//    case DIR::UP:
//    {
//        const float rc1Top = rc1->pos.y;
//        const float rc2Bottom = rc2->pos.y + rc2->texSize.y;
//
//        return rc2Bottom - rc1Top;
//    }
//    break;
//
//    case DIR::DOWN:
//    {
//        const float rc1Bottom = rc1->pos.y + rc1->texSize.y;
//        const float rc2Top = rc2->pos.y;
//
//        return rc2Top - rc1Bottom;
//    }
//    break;
//
//    case DIR::LEFT:
//    {
//        const float rc1Left = rc1->pos.x;
//        const float rc2Right = rc2->pos.x + rc2->texSize.x;
//
//        return rc2Right - rc1Left;
//    }
//    break;
//
//    case DIR::RIGHT:
//    {
//        const float rc1Right = rc1->pos.x + rc1->texSize.x;
//        const float rc2Left = rc2->pos.x;
//
//        return rc2Left - rc1Right;
//    }
//    break;
//    }
//}