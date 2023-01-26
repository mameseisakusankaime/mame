#include "player.h"
#include "common.h"
#include "enemy.h"
#include "SceneGame.h"
#include "back.h"
using namespace GameLib;


// 画像位置テーブル
float data_pos[][2] =
{
    {0,0},
    {256,0},
    {512,0},
    {768,0},
};

void Player::init()
{
    OBJ2DManager::init();

    obj_w[0].mover = player;
}

void Player::reduceHp()
{
    obj_w[0].hp -= 1;
    obj_w[0].invincible = true;
}

void player_attack(OBJ2D* obj)
{
    Player* player = Player::getInstance();
    switch (obj->state)
    {
    case 0:
        //obj->data = sprite_load(L"./Data/Images/player.png");
        obj->pos = player->pos;
        obj->hp = player->hp;

        obj->scale = { 0.5f,0.5f };
        obj->texPos = { 0,1536 };
        obj->texSize = { 512,512 };
        obj->pivot = { 128,384 };

        obj->radius = 45;
        obj->foundRadius = 180;

        obj->animeState = 0;

        obj->eraser = enemy_erase;

        obj->one = false;

        obj->playerType = PLAYER_PUNCH;

        ++obj->state;
        //break;
    case 1:
        obj->texPos.y = 1536.0f;
        anime(obj, 6, 10, false, 0);

        if (obj->one)
        {
            obj->state = 2;
            obj->texPos = { 0,2048.0f };
            obj->attack = false;
        }

        break;
    case 2:
        obj->texPos = { 0,2048.0f };
        switch (STATE(0) & (PAD_LEFT | PAD_RIGHT))
        {
        case PAD_LEFT:
            // プレイヤーの移動
            if (!obj->attack)anime(obj, 2, 15, true, 0);
            obj->pos.x -= 1;
            if (obj->scale.x > 0)obj->scale.x *= -1;
            break;
        case PAD_RIGHT:
            // プレイヤーの移動
            if (!obj->attack)anime(obj, 2, 15, true, 0);
            obj->pos.x += 1;
            if (obj->scale.x < 0)obj->scale.x *= -1;
            break;
        }

        // 吸い込み移動
        if (obj->attack)
            obj->state = 3;
        // 攻撃（パンチに移動）
        if (obj->attackPunch)
            obj->state = 5;

        break;
    case 3:
        // 吸い込み期化
        obj->animeState = 0;

        ++obj->state;
        break;
    case 4:
        // 吸い込み処理
        anime(obj, 13, 3, false, 10);

        if (obj->end)
        {
            obj->texPos.x = 0;
            obj->state = 2;
            obj->end = false;
            obj->animeState = 0;
        }

        break;
    case 5:
        // パンチの初期化
        obj->animeState = 0;

        ++obj->state;
        break;
    case 6:
        // パンチの処理
        anime(obj, 11, 3, false, 11);

        if (obj->end)
        {
            obj->texPos.x = 0;
            obj->state = 2;
            obj->end = false;
            obj->animeState = 0;
            obj->attackPunch = false;
        }
        break;
    }
    // 画面外チェック
    obj->pos.x = (std::max)(obj->pos.x, obj->pivot.x / 2);
    float oldx = obj->pos.x;
    obj->pos.x = (std::min)(obj->pos.x, 1280 - obj->pivot.x / 2);
    if ( oldx!=obj->pos.x ) 
    {
        //右端に付いたらクリア
        setScene(SCENE::CLEAR);
    }

    invincibleupdate(obj);


    if (player->obj_w[0].hp <= 0)setScene(SCENE::OVER);

#ifdef _DEBUG
    debug::setString("pos%f,%f", obj->pos.x, obj->pos.y);
    debug::setString("texpos%f:%f", obj->texPos.x, obj->texPos.y);
    debug::setString("hp%d", obj->hp);
    debug::setString("w%f", obj->color.w);
    debug::setString("playerType%d", Player::getInstance()->begin()->playerType);
#endif
}

void player(OBJ2D* obj)
{
    auto&& player = Player::getInstance();

    switch (obj->state)
    {
    case 0:
        //obj->data = sprite_load(L"./Data/Images/player1.png");
        obj->data = sprite_load(L"./Data/Images/player.png");
        //obj->data = sprite_load(L"./Data/Images/data.png");
        obj->pos = { 10,200 };
        obj->scale = { 0.5f,0.5f };
        obj->texPos = { 0,0 };  
        obj->texSize = { 512,512 };
        obj->pivot = { 128,384 };
        //obj->type = DATA::MARU;
        obj->radius = 45;
        obj->foundRadius = 180;
        obj->hp = 5;
        //obj->eraser = enemy_erase;

        obj->eraser = enemy_erase;
        
        obj->playerType = PLAYER_WALK;

        ++obj->state;
        //break;
    case 1:
        // 移動
        
        //if (STATE(0) & PAD_UP)obj.pos.y -= 5;
        //if (STATE(0) & PAD_DOWN)obj.pos.y += 5;
        //if (!obj->attack)
        //{
            switch (STATE(0) & (PAD_LEFT | PAD_RIGHT))
            {
            case PAD_LEFT:
                // プレイヤーの移動
                if(!obj->attack)anime(obj, 2, 15, true, 0);
                obj->pos.x -= 1;
                if (obj->scale.x > 0)obj->scale.x *= -1;
                break;
            case PAD_RIGHT:
                // プレイヤーの移動
                if (!obj->attack)anime(obj, 2, 15, true, 0);
                obj->pos.x += 1;
                if (obj->scale.x < 0)obj->scale.x *= -1;
                break;
            }
        //}

#ifdef _DEBUG
        debug::setString("x%f", obj->texPos.x);
        debug::setString("y%f", obj->texPos.y);
        debug::setString("obj->type%f", obj->type);
#endif

        // 画像データ
        //if (STATE(0) & PAD_UP)      setSpr(0);
        //if (STATE(0) & PAD_DOWN)    setSpr(1);
        //if (STATE(0) & PAD_LEFT)    setSpr(2);
        //if (STATE(0) & PAD_RIGHT)   setSpr(3);

        // 画像位置
        //if (STATE(0) & PAD_UP)      setData(0);
        //if (STATE(0) & PAD_DOWN)    setData(1);
        //if (STATE(0) & PAD_LEFT)    setData(2);
        //if (STATE(0) & PAD_RIGHT)   setData(3);

        gravity(obj);

        //if (TRG(0) & PAD_L1)
        //{
        //    //setData(Enemy::getInstance()->obj_w.type);
        //}

        if (obj->type == DATA::ATTACK)
        {
            player->pos = obj->pos;
            player->hp = obj->hp;
            obj->mover = player_attack;
            obj->state = 0;
            return;
        }
        
        // 攻撃フェーズに移動（飲み込み）
        if (obj->attack)
            obj->state = 2;


#ifdef _DEBUG
        debug::setString("player.hp%d", obj->hp);
        //debug::setString("obj->flashingTimer")
#endif

        break;
    case 2:
        // 攻撃初期化
        obj->animeState = 0;

        ++obj->state;
        break;
    case 3:
        // 攻撃処理

        anime(obj, 13, 3, false, 0);

        if (obj->end)
        { 
            obj->texPos.x = 0;
            obj->state = 1;
            obj->end = false;
            obj->animeState = 0;
        }
        break;
    }

    //画面外チェック
    obj->pos.x = (std::max)(obj->pos.x, obj->pivot.x / 2);
    obj->pos.x = (std::min)(obj->pos.x, 1280 - obj->pivot.x / 2);

    //無敵の更新
    invincibleupdate(obj);

#ifdef _DEBUG
    debug::setString("state%d", obj->state);
    debug::setString("playerType%d", Player::getInstance()->begin()->playerType);
#endif 

    if (player->obj_w[0].hp <= 0)setScene(SCENE::OVER);
}


void Player::setData(int data)
{
    obj_w[0].texPos.x = data_pos[data][0];
    obj_w[0].texPos.y = data_pos[data][1];
}

void Player::setSpr(int data)
{
    //obj_w[0].data = *data_tbl[data];
}

void invincibleupdate(OBJ2D* obj)
{
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
}
