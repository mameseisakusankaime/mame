#include "player.h"
#include "gimmick.h"

//�U�����������u���b�N
void gimmick_Blok(OBJ2D* obj)
{
    auto&& player = Player::getInstance()->begin();

    if (player->pos.x + player->radius >= obj->pos.x - obj->size.x)
        player->pos.x = obj->pos.x - obj->size.x - player->radius;


}

//TODO : gimmick    �����ƓG���o�Ă���{�^��
void gimmick_Button(OBJ2D* obj)
{

}

