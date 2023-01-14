#include "all.h"

Back back;
Player player;

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
    player.deinit();
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
        player.init();

        ++state;
        //break;
    case 1:
        if (TRG(0) & PAD_START)setScene(SCENE::TITLE);

        // 背景更新
        back.update();
        // プレイヤー更新処理
        player.update();

        break;
    }
}

void SceneGame::draw()
{
    GameLib::clear(1, 1, 1);

    // 背景描画
    back.draw();
    // プレイヤー描画処理
    player.draw();
}
