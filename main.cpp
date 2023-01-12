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

// WinMain�֐��i�G���g���|�C���g�j
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// �����ݒ�
	GameLib::init(L"�Q�[���쐬", 1280, 720);

	// �Q�[�������ݒ�
	setScene(SCENE_TITLE);

	// ���C�����[�v
	while (GameLib::gameLoop())
	{
		// ���͏���
		input::update();

		// �X�V����
		if (pNext)
		{
			pScene = pNext;
			pNext = nullptr;
			pScene->init();
		}
		pScene->update();

		// �`�揈��
		pScene->draw();

		//�f�o�b�O�p������̕\��
		debug::display(1, 1, 1, 1);

		//��ʂ�`�悷��
		GameLib::present(1, 0);
	}

	// �I������
	GameLib::uninit();

	return 0;
}

// �V�[���؂�ւ�
void setScene(int scene)
{
	pNext = scene_tbl[scene];
}