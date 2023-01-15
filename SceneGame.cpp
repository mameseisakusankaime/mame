#include "all.h"

Back back;

void SceneGame::init()
{
    state = 0;
}

void SceneGame::deinit()
{
    safe_delete(data);

    // ”wŒiI—¹ˆ—
    back.deinit();
    // ƒvƒŒƒCƒ„[I—¹ˆ—
    Player::getInstance()->deinit();
    // “GI—¹ˆ—
    Enemy::getInstance()->deinit();
    // ‚°[‚¶
    Gage::getInstance()->deinit();
}

void SceneGame::update()
{
    switch (state)
    {
    case 0:
        GameLib::setBlendMode(Blender::BS_ALPHA);

        // ”wŒi‰ŠúÝ’è
        back.init();
        // ƒvƒŒƒCƒ„[‰ŠúÝ’è
        Player::getInstance()->init();
        // “G‰ŠúÝ’è
        Enemy::getInstance()->init();
        //ƒQ[ƒW
        Gage::getInstance()->init();

        ++state;
        //break;
    case 1:
        if (TRG(0) & PAD_START)setScene(SCENE::TITLE);

        // ”wŒiXV
        back.update();
        // ƒvƒŒƒCƒ„[XVˆ—
        Player::getInstance()->update();
        // “GXVˆ—
        Enemy::getInstance()->update();
        //ƒQ[ƒW
        Gage::getInstance()->update();

        judge();

        if (TRG(0) & PAD_L1)
        {
            Enemy::getInstance()->obj_w[0].hp = Enemy::getInstance()->obj_w[0].hp <= 1 ? 2 : 1;
        }

        break;
    }
}

void SceneGame::draw()
{
    GameLib::clear(1, 1, 1);

    // ”wŒi•`‰æ
    back.draw();
    // “G•`‰æˆ—
    Enemy::getInstance()->draw();
    // ƒQ[ƒW
    Gage::getInstance()->draw();

    // ƒvƒŒƒCƒ„[•`‰æˆ—
    Player::getInstance()->draw();

    OBJ2D* plat = &Player::getInstance()->obj_w[0];

    primitive::circle(plat->pos, 40.0f, VECTOR2(1, 1), 0.0f, VECTOR4(0, 1, 0, 0.2f));
       
    OBJ2D* elat = &Enemy::getInstance()->obj_w[0];
    
    primitive::circle(elat->pos, elat->foundRadius, VECTOR2(1, 1), 0.0f, VECTOR4(0, 0, 1, 0.4f));

}

//--------------------------------------
//  ‰~‚Æ‰~‚Ì‚ ‚½‚è”»’è
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
//  OBJ2D“¯Žm‚Ì‚ ‚½‚è”»’è
//--------------------------------------
bool hitCheck(OBJ2D* obj1, OBJ2D* obj2,int num)
{
    switch (num)
    {
    case 0:
        return hitCheckCircle(
            obj1->pos + obj1->offset, obj1->radius,
            obj2->pos + obj2->offset, obj2->radius
        );
        break;
    case 1:
        return hitCheckCircle(
            obj1->pos + obj1->offset, obj1->radius,
            obj2->pos + obj2->offset, obj2->foundRadius
        );
        break;
    }
}

//--------------------------------------
//  ‚ ‚½‚è”»’è
//--------------------------------------
void judge()
{
    OBJ2D player = Player::getInstance()->obj_w[0];
    
    
    OBJ2D enemy[10];
    int num = 0;
    for (auto& obj : enemy)
    {
        obj = Enemy::getInstance()->obj_w[num];
        ++num;
    }

    for (int i = 0; i < 10; ++i)
    {
        if (enemy[i].mover == nullptr)continue;

        if (hitCheck(&player, &enemy[i],0))
        {
            debug::setString("hit!!");
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

//// •Ç‚Æ‚Ì“–‚½‚è”»’è
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
//// •Ç‚Æ‚Ì‚ß‚èž‚Ý”»’è
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