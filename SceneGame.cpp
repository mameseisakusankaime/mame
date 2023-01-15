#include "all.h"

Back back;



void SceneGame::init()
{
    state = 0;
}

void SceneGame::deinit()
{
    safe_delete(data);

    // �w�i�I������
    back.deinit();
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

        // �w�i�����ݒ�
        back.init();
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

        // �w�i�X�V
        back.update();
        // �v���C���[�X�V����
        Player::getInstance()->update();
        // �G�X�V����
        Enemy::getInstance()->update();
        //�Q�[�W
        Gage::getInstance()->update();
        //
        Find::getInstance()->update();

        judge();

        if (TRG(0) & PAD_R1)
        {
            player_attack();
        }


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

        break;
    }
}

void SceneGame::draw()
{
    GameLib::clear(1, 1, 1);

    // �w�i�`��
    back.draw();
    // �G�`�揈��
    Enemy::getInstance()->draw();
    // �Q�[�W
    Gage::getInstance()->draw();
    // 
    Find::getInstance()->draw();

    // �v���C���[�`�揈��
    Player::getInstance()->draw();

    OBJ2D* plat = &Player::getInstance()->obj_w[0];

    primitive::circle(plat->pos, plat->radius, VECTOR2(1, 1), 0.0f, VECTOR4(0, 1, 0, 0.2f));
    primitive::circle(plat->pos, plat->foundRadius, VECTOR2(1, 1), 0.0f, VECTOR4(0, 0, 1, 0.2f));
       
    OBJ2D* elat = &Enemy::getInstance()->obj_w[0];
    
    primitive::circle(elat->pos, elat->foundRadius, VECTOR2(1, 1), 0.0f, VECTOR4(0, 0, 1, 0.4f));

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
    switch (obj->state)
    {
    case 0:
        obj->anime = obj->animeTimer = 0;
        obj->end = false;
        obj->one = false;
        //if (type == 0)
        //    GameLib::sound::play(type, 0);

        ++obj->state;
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
        //else
        //{
        //    if (obj->open)
        //    {
        //        obj->anime = obj->animeTimer / flame;
        //        if (obj->anime >= total - 1)obj->one = true;
        //        if (obj->anime >= total)
        //        {
        //            obj->anime = total - 1;
        //            obj->end = true;
        //            return;
        //        }
        //        obj->texPos.x = obj->anime * obj->texSize.x;
        //        ++obj->animeTimer;
        //    }
        //}
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

    //for (int i = 0; i < 10; ++i)
    //{
    //    for (int j = 0; j < 10; ++j)
    //    {
    //        if (i == j)continue;
    //        if (hitCheck(enemy[i], enemy[j], 0))
    //        {
    //            // ���̋���
    //            float dist = enemy[i]->pos.x - enemy[j]->pos.x;
    //            // �ǂ����ɂ��邩
    //            bool right;
    //            if (dist < 0)
    //            {
    //                dist *= -1;
    //                right = true;
    //            }
    //            else
    //            {
    //                right = false;
    //            }
    //            // ������������
    //            float len = enemy[i]->radius + enemy[j]->radius;
    //            if (dist < len)
    //                enemy[j]->pos.x = right ? enemy[i]->pos.x + len : enemy[i]->pos.x - len;
    //        }
    //    }
    //}

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
            enemy[i]->hp -= 1;
        }
    }
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