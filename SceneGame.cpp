#include "all.h"
EnemySetdata enemySetdata[] = {
    {enemy_attack,VECTOR2(600,500), 0},
    {enemy_attack,VECTOR2(900,500), 2},
    {enemy_attack,VECTOR2(1200,500), 4},
    {enemy_attack,VECTOR2(2000,500),10},
    {enemy_attack,VECTOR2(2500,500),20},
    //終了フラグ
    {nullptr,VECTOR2(-1,-1),-1},
};


void SceneGame::init()
{
    state = 0;
}

void SceneGame::deinit()
{
    safe_delete(data);

    // 背景終了処理
    Back::getInstance()->deinit();
    // プレイヤー終了処理
    Player::getInstance()->deinit();
    // 敵終了処理
    Enemy::getInstance()->deinit();
    // げーじ
    Gage::getInstance()->deinit();
    // !マーク
    Find::getInstance()->deinit();
    // ギミック
    Gimmick::getInstance()->deinit();
}

void SceneGame::update()
{
    static EnemySetdata* pEnemydata = enemySetdata;
    switch (state)
    {
    case 0:
        GameLib::setBlendMode(Blender::BS_ALPHA);

        // 画像読み込み
        sprLoad = sprite_load(L"./Data/Images/loading_back.png");
        sprWord = sprite_load(L"./Data/Images/loading_character.png");

        // 背景初期設定
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
        
        //Back::getInstance()->searchSet(sea_update0, VECTOR2(0,0));
        //Back::getInstance()->searchSet(sea_update0, VECTOR2(5120,0));
        //Back::getInstance()->searchSet(sea_update1, VECTOR2(0,0));
        //Back::getInstance()->searchSet(sea_update1, VECTOR2(5120,0));
        //Back::getInstance()->searchSet(sea_update2, VECTOR2(0,0));
        //Back::getInstance()->searchSet(sea_update2, VECTOR2(5120,0));
        //Back::getInstance()->searchSet(sea_update3, VECTOR2(0,0));
        //Back::getInstance()->searchSet(sea_update3, VECTOR2(5120,0));
        //Back::getInstance()->searchSet(sea_update3, VECTOR2(7680,0));

        // プレイヤー初期設定
        Player::getInstance()->init();
        // 敵初期設定
        Enemy::getInstance()->init();
        //ゲージ
        Gage::getInstance()->init();
        // 
        //Find::getInstance()->init();
        //ギミック
        Gimmick::getInstance()->init();

        ++state;
        //break;
    case 1:
        //if (TRG(0) & PAD_START)setScene(SCENE::TITLE);

#ifdef _DEBUG
        debug::setString("0%d", Enemy::getInstance()->obj_w[0].state);
        debug::setString("1%d", Enemy::getInstance()->obj_w[1].state);
        debug::setString("2%d", Enemy::getInstance()->obj_w[2].state);
#endif

        // 背景更新
        Back::getInstance()->update();
        // 敵更新処理
        Enemy::getInstance()->update();
        // プレイヤー更新処理
        Player::getInstance()->update();
        //ゲージ
        Gage::getInstance()->update();
        //
        Find::getInstance()->update();
        //ギミック
        Gimmick::getInstance()->update();

        judge();

        {
            auto&& player = Player::getInstance()->begin();
        //攻撃
        if (TRG(0) & PAD_R3)//Rボタン
        {
            if (!player->attack &&
                !player->attackPunch)
            {
                player_attack();
            }
        }
        if (TRG(0) & PAD_R1)//Lボタン
        {
            if (!player->attack &&
                !player->attackPunch &&
                 player->playerType == PLAYER_PUNCH)
                player_attack1();
        }
        }



        //if (Player::getInstance()->obj_w[0].attack)
        //    anime(&Player::getInstance()->obj_w[0], 13, 2, false, 0);

        if (TRG(0) & PAD_L1)
        {
            
            if (!Enemy::getInstance()->obj_w[0].mover)
            {
                Enemy::getInstance()->searchSet(enemy_walk, enemySetdata[0].pos);
            }
            else
            {
                Enemy::getInstance()->obj_w[0].hp = Enemy::getInstance()->obj_w[0].hp <= 1 ? 2 : 0;
            }
        }

        if (timer >= pEnemydata->timer&&pEnemydata->mover!=nullptr)
        {
            Enemy::getInstance()->searchSet(pEnemydata->mover, pEnemydata->pos);
            pEnemydata++;
        }

        ++timer;
        break;
    }
}

void SceneGame::draw()
{
    GameLib::clear(1, 1, 1);

    // 背景描画
    Back::getInstance()->draw();
    //ギミック
    Gimmick::getInstance()->draw();
    // 敵描画処理
    Enemy::getInstance()->draw();
    // ゲージ
    Gage::getInstance()->draw();
    // 
    Find::getInstance()->draw();

    // プレイヤー描画処理
    Player::getInstance()->draw();

    OBJ2D* plat = Player::getInstance()->begin();

#ifdef _DEBUG
    //primitive::circle(plat->pos, plat->radius, VECTOR2(1, 1), 0.0f, VECTOR4(0, 1, 0, 0.2f));
    //primitive::circle(plat->pos, plat->foundRadius, VECTOR2(1, 1), 0.0f, VECTOR4(0, 0, 1, 0.2f));
#endif
       
    OBJ2D* elat = Enemy::getInstance()->begin();
    
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
/// アニメーション関数
/// </summary>
/// <param name="obj">キャラクター</param>
/// <param name="total">画像枚数</param>
/// <param name="flame">フレーム</param>
/// <param name="loop">ループするか</param>
/// <param name="type">効果音のタイプ(通常０でいい)</param>
void anime(OBJ2D* obj, int total, int flame, bool loop, int type)
{
    // type 0 player
    // type 1 enemy_attack
    // type 10 player_attack
    // type 11 player_attack_punch

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
            if (obj->attack || obj->attackPunch)
            {
                // 攻撃開始
                if (!obj->one)
                {
                    if (type == 0|| type == 1)
                        obj->texPos.y = 512;
                    
                    if (type == 10)
                        obj->texPos.y = 2560.0f;

                    if (type == 11)
                        obj->texPos.y = 3584.0f;
                }

                // 攻撃アニメ
                obj->anime = obj->animeTimer / flame;
                if (obj->anime >= total - 1)obj->one = true;
                if (obj->anime >= total)
                {
                    obj->anime = total - 1;
                    //obj->end = true;
                    return;
                }
                obj->texPos.x = obj->anime * obj->texSize.x;

                // 攻撃終了
                if (obj->one)
                {

                    obj->anime = obj->animeTimer = 0;
                    obj->end = false;
                    obj->one = false;
                    obj->half = true;

                    if (type == 1 || type == 11)
                        obj->end = true;
                    else
                        ++obj->animeState;

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
        // 引っ込めるの開始
        if (type == 0)
            obj->texPos.y = 512 * 2;
        if (type == 10)
            obj->texPos.y = 3072.0f;
        if (type == 11)
            obj->texPos.y = 4096.0f;

        // 引っ込めるアニメ
        obj->anime = obj->animeTimer / flame;
        if (obj->anime >= total - 1)obj->one = true;
        if (obj->anime >= total)
        {
            obj->anime = total - 1;
            obj->end = true;
            return;
        }
        obj->texPos.x = obj->anime * obj->texSize.x;

        // ひっこめ終了
        if (obj->one)
        {
            // 画像位置を設定
            if(type==0)
                obj->texPos = {};
            if (type == 10)
                obj->texPos = { 0,2048.0f };
            
            obj->anime = obj->animeTimer = 0;
            obj->end = true;
            obj->one = false;
            obj->attack = false;
            obj->attackPunch = false;
            obj->half = false;
            //obj->animeState = 0;
        }

        ++obj->animeTimer;
        break;
    }

}

//--------------------------------------
//  円と円のあたり判定
//--------------------------------------
bool hitCheckCircle(VECTOR2 pos1, float r1, VECTOR2 pos2, float r2)
{
    const float dx = pos2.x - pos1.x;
    const float dy = pos2.y - pos1.y;
    const float r = r1 + r2;

    if (dx * dx + dy * dy <= r * r)
        return true;

    return false;
}

//--------------------------------------
//  四角と四角のあたり判定
//--------------------------------------
bool hitCheckBox(   float b1top,float B1left,float b1right,float b1bottom,
                    float b2top,float b2left,float b2right,float b2bottom)
{
    if (    B1left < b2right
        ||  b1right > b2left
        ||  b1top < b2bottom
        ||  b1bottom > b2top)return false;

    return true;
}

bool hitCheckBox(VECTOR2 pos1, VECTOR2 size1, VECTOR2 pos2, VECTOR2 size2)
{
    return hitCheckBox( pos1.y - size1.y, pos1.x - size1.x, pos1.x + size1.x, pos1.y + size1.y,
                        pos2.y - size2.y, pos1.x - size2.x, pos2.x + size2.x, pos2.y + size2.y);
}

//--------------------------------------
//  OBJ2D同士のあたり判定
//--------------------------------------
bool hitCheck(OBJ2D* obj1, OBJ2D* obj2,int num)
{
    switch (num)
    {
    case HITCHECK::PLAndENE: 
        // プレイヤーと敵
        return hitCheckCircle(
            obj1->pos + obj1->offset, obj1->radius,
            obj2->pos + obj2->offset, obj2->radius
        );
        break;
    case HITCHECK::PLAndENEScope:
        // プレイヤーと敵範囲
        return hitCheckCircle(
            obj1->pos + obj1->offset, obj1->radius,
            obj2->pos + obj2->offset, obj2->foundRadius
        );
        break;
    case HITCHECK::PLScopeAndENE:
        // プレイヤー範囲と敵
        return hitCheckCircle(
            obj1->pos + obj1->offset, obj1->foundRadius,
            obj2->pos + obj2->offset, obj2->radius
        );
        break;
    case 3:
        // プレイヤーと敵の攻撃範囲
        return hitCheckCircle(
            obj1->pos + obj1->offset, obj1->radius,
            obj2->pos + obj2->offset, obj2->attackRadius
        );
        break;
    }
}

//--------------------------------------
//  あたり判定
//--------------------------------------
void judge()
{
    OBJ2D* player = Player::getInstance()->begin();
    
    //playerとenemyの判定
    for (auto&& enemy : *Enemy::getInstance())
    {
        if (!enemy.mover)continue;

        if (hitCheck(player, &enemy, HITCHECK::PLAndENE))
        {
            debug::setString("hit!!");

            if (player->invincible)continue;

            player->hp -= 1;
            player->invincible = true;

            if (player->hp <= 0)setScene(SCENE::OVER);
        }
    }

    //enemy同士の当たり判定
    for (auto&& enemy1 : *Enemy::getInstance())
    {
        for (auto&& enemy2 : *Enemy::getInstance())
        {
            if (&enemy1 == &enemy2)continue;

            if (hitCheck(&enemy1, &enemy2, HITCHECK::PLAndENE))
            {
                // 今の距離
                float dist = enemy1.pos.x - enemy2.pos.x;
                // どっちにいるか
                bool right = false;
                if (dist < 0)
                {
                    dist *= -1;
                    right = true;
                }
                // 離したい距離
                float len = enemy1.radius + enemy2.radius;
                if (dist < len)
                    enemy2.pos.x = right ? enemy1.pos.x + len : enemy1.pos.x - len;
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

void player_attack1()
{
    OBJ2D* player = Player::getInstance()->begin();

    for (auto&& enemy : *Enemy::getInstance())
    {
        if (!enemy.mover)continue;

        if (hitCheck(player, &enemy, HITCHECK::PLScopeAndENE))
        {
            // プレイヤーと敵の距離
            float dist = player->pos.x - enemy.pos.x;
            bool right;
            if (dist < 0)right = true;
            else right = false;

            if (right && player->scale.x > 0 || !right && player->scale.x < 0)
                enemy.half = true;


            // ギミック
            for (auto&& gimmick : *Gimmick::getInstance())
            {
                if (!gimmick.mover)continue;
                if (gimmick.mover != gimmick_Blok)continue;

                if (hitCheck(player, &gimmick, HITCHECK::PLScopeAndENE))
                {
                    gimmick.clear();
                }
            }

        }
    }
    player->attackPunch = true;
    sound::play(0, 1);
}

// 食べる
void player_attack()
{
    OBJ2D* player = Player::getInstance()->begin();

    for (auto&& enemy : *Enemy::getInstance())
    {
        if (!enemy.mover)continue;

        if (hitCheck(player, &enemy, HITCHECK::PLScopeAndENE))
        {
            // プレイヤーと敵の距離
            float dist = player->pos.x - enemy.pos.x;
            bool right;
            if (dist < 0)right = true;
            else right = false;

            if (right && player->scale.x > 0 || !right && player->scale.x < 0)
                enemy.half = true;

            //player->type = enemy[i]->type;

            //enemy[i]->hp -= 1;
            //enemy[i]->invincible = true;
//=======
//            enemy.half = true;
//            //enemy.hp -= 1;
//            //enemy.invincible = true;
//>>>>>>> 83ddf8e3132d7043242e8096ecb5c02a4842bd29
        }
    }

    for (auto&& gimmick : *Gimmick::getInstance())
    {
        if (!gimmick.mover)continue;
        if (gimmick.mover != gimmick_Blok)continue;

        if (hitCheck(player, &gimmick, HITCHECK::PLScopeAndENE))
        {
            gimmick.clear();
        }
    }

    player->attack = true;
    sound::play(0, 0);
    //if(TRG(0)&PAD_START)player->animeState = 0;
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