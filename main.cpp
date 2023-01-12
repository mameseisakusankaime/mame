#include "all.h"

SceneTitle sceneTitle;
SceneGame sceneGame;

Scene* scene_tbl[] =
{
	&sceneTitle,
	&sceneGame,
};

Scene* pScene;
Scene* pNext;

// WinMain関数（エントリポイント）
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// 初期設定
	GameLib::init(L"ゲーム作成", 1280, 720);

	// ゲーム初期設定
	setScene(SCENE_TITLE);

	// メインループ
	while (GameLib::gameLoop())
	{
		// 入力処理
		input::update();

		// 更新処理
		if (pNext)
		{
			pScene = pNext;
			pNext = nullptr;
			pScene->init();
		}
		pScene->update();

		// 描画処理
		pScene->draw();

		//デバッグ用文字列の表示
		debug::display(1, 1, 1, 1);

		//画面を描画する
		GameLib::present(1, 0);
	}

	// 終了処理
	GameLib::uninit();

	return 0;
}

// シーン切り替え
void setScene(int scene)
{
	pNext = scene_tbl[scene];
}