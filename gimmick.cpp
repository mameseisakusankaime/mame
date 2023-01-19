#include "common.h"
#include "player.h"
#include "gimmick.h"
#include "SceneGame.h"

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
        obj->data = GameLib::sprite_load(L"./Data/Images/enemy.png");//TODO:テクスチャ変更
        obj->pos = { 900,200 };
        obj->scale = { 1,1 };
        obj->texPos = { 0,0 };
        obj->texSize = { 256,256 };
        obj->pivot = { 128,128 };
        obj->radius = 40;
        obj->hp = 1;
        obj->eraser = gimmick_erase;

        //break;
    case 1:
        if (hitCheckBox(player->pos, { player->radius,player->radius }, obj->pos, { obj->radius,obj->radius }))
        {

        }
    }



}

//TODO : gimmick    押すと敵が出てくるボタン
void gimmick_Button(OBJ2D* obj)
{

}

