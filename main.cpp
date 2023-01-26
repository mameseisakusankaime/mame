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
SceneClear sceneClear;

Scene* scene_tbl[] = {
    &sceneTitle,
    &sceneGame,
    &sceneOver,
    &sceneClear,
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

    audio_init();

    while (GameLib::gameLoop())
    {
        GameLib::input::update();
        music::update();

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

    audio_deinit();

    GameLib::uninit();

    return 0;
}

void setScene(int scene)
{
    pNext = scene_tbl[scene];
}
void setScene(Scene* scene)
{
    pNext = scene;
}
