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
}

void SceneGame::update()
{
    switch (state)
    {
    case 0:
        GameLib::setBlendMode(Blender::BS_ALPHA);

        // ”wŒi‰Šúİ’è
        back.init();
        // ƒvƒŒƒCƒ„[‰Šúİ’è
        Player::getInstance()->init();
        // “G‰Šúİ’è
        Enemy::getInstance()->init();

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

        break;
    }
}

void SceneGame::draw()
{
    GameLib::clear(1, 1, 1);

    // ”wŒi•`‰æ
    back.draw();
    // ƒvƒŒƒCƒ„[•`‰æˆ—
    Player::getInstance()->draw();
    // “G•`‰æˆ—
    Enemy::getInstance()->draw();

}
