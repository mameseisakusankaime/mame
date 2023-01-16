//******************************************************************************
//
//
//      main
//
//
//******************************************************************************

//------< インクルード >----------------------------------------------------------
#include "all.h"

SceneTitle sceneTitle;
SceneGame sceneGame;
SceneOver sceneOver;

Scene* scene_tbl[] = {
    &sceneTitle,
    &sceneGame,
    &sceneOver,
};

Scene* pScene;
Scene* pNext;

//--------------------------------------------------------------
//  WinMain（エントリポイント）
//--------------------------------------------------------------
int APIENTRY wWinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPWSTR, _In_ int)
 {
    GameLib::init(L"最強すらすら", 1280, 720, true);

    setScene(SCENE::TITLE);
    pScene = pNext;
    pNext = nullptr;
    pScene->init();

    while (GameLib::gameLoop())
    {
        GameLib::input::update();

        if (pNext)
        {
            pScene->deinit();
            pScene = pNext;
            pNext = nullptr;
            pScene->init();
        }
         
        pScene->update();
        pScene->draw();

        debug::display(1.0f, 1.0f, 1.0f, 1, 1);

        GameLib::present(1, 0);
    }

    GameLib::uninit();

    return 0;
}

void setScene(int scene)
{
    pNext = scene_tbl[scene];
}
