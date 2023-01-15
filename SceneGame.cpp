#include "all.h"

Back back;



void SceneGame::init()
{
    state = 0;
}

void SceneGame::deinit()
{
    safe_delete(data);

    // 背景終了処理
    back.deinit();
    // プレイヤー終了処理
    Player::getInstance()->deinit();
    // 敵終了処理
    Enemy::getInstance()->deinit();
    // げーじ
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

        // 背景初期設定
        back.init();
        // プレイヤー初期設定
        Player::getInstance()->init();
        // 敵初期設定
        Enemy::getInstance()->init();
        //ゲージ
        Gage::getInstance()->init();
        // 
        //Find::getInstance()->init();

        ++state;
        //break;
    case 1:
        //if (TRG(0) & PAD_START)setScene(SCENE::TITLE);

        // 背景更新
        back.update();
        // プレイヤー更新処理
        Player::getInstance()->update();
        // 敵更新処理
        Enemy::getInstance()->update();
        //ゲージ
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

    // 背景描画
    back.draw();
    // 敵描画処理
    Enemy::getInstance()->draw();
    // ゲージ
    Gage::getInstance()->draw();
    // 
    Find::getInstance()->draw();

    // プレイヤー描画処理
    Player::getInstance()->draw();

    OBJ2D* plat = &Player::getInstance()->obj_w[0];

    primitive::circle(plat->pos, plat->radius, VECTOR2(1, 1), 0.0f, VECTOR4(0, 1, 0, 0.2f));
    primitive::circle(plat->pos, plat->foundRadius, VECTOR2(1, 1), 0.0f, VECTOR4(0, 0, 1, 0.2f));
       
    OBJ2D* elat = &Enemy::getInstance()->obj_w[0];
    
    primitive::circle(elat->pos, elat->foundRadius, VECTOR2(1, 1), 0.0f, VECTOR4(0, 0, 1, 0.4f));

}

/// <summary>
/// アニメーション関数
/// </summary>
/// <param name="obj">キャラクター</param>
/// <param name="total">画像枚数</param>
/// <param name="flame">フレーム</param>
/// <param name="loop">ループするか</param>
/// <param name="type">効果音のタイプ(通常０でいい)</param>
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
//  円と円のあたり判定
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
//  OBJ2D同士のあたり判定
//--------------------------------------
bool hitCheck(OBJ2D* obj1, OBJ2D* obj2,int num)
{
    switch (num)
    {
    case 0: 
        // プレイヤーと敵
        return hitCheckCircle(
            obj1->pos + obj1->offset, obj1->radius,
            obj2->pos + obj2->offset, obj2->radius
        );
        break;
    case 1:
        // プレイヤーと敵範囲
        return hitCheckCircle(
            obj1->pos + obj1->offset, obj1->radius,
            obj2->pos + obj2->offset, obj2->foundRadius
        );
        break;
    case 2:
        // プレイヤー範囲と敵
        return hitCheckCircle(
            obj1->pos + obj1->offset, obj1->foundRadius,
            obj2->pos + obj2->offset, obj2->radius
        );
        break;
    }
}

//--------------------------------------
//  あたり判定
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
    //            // 今の距離
    //            float dist = enemy[i]->pos.x - enemy[j]->pos.x;
    //            // どっちにいるか
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
    //            // 離したい距離
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

//// 壁との当たり判定
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
//// 壁とのめり込み判定
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