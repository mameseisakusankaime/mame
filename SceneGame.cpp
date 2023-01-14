#include "all.h"

Back back;

void SceneGame::init()
{
    state = 0;
}

void SceneGame::deinit()
{
    safe_delete(data);

    // �w�i�I������
    back.deinit();
    // �v���C���[�I������
    Player::getInstance()->deinit();
    // �G�I������
    Enemy::getInstance()->deinit();
}

void SceneGame::update()
{
    switch (state)
    {
    case 0:
        GameLib::setBlendMode(Blender::BS_ALPHA);

        // �w�i�����ݒ�
        back.init();
        // �v���C���[�����ݒ�
        Player::getInstance()->init();
        // �G�����ݒ�
        Enemy::getInstance()->init();

        ++state;
        //break;
    case 1:
        if (TRG(0) & PAD_START)setScene(SCENE::TITLE);

        // �w�i�X�V
        back.update();
        // �v���C���[�X�V����
        Player::getInstance()->update();
        // �G�X�V����
        Enemy::getInstance()->update();

        break;
    }
}

void SceneGame::draw()
{
    GameLib::clear(1, 1, 1);

    // �w�i�`��
    back.draw();
    // �v���C���[�`�揈��
    Player::getInstance()->draw();
    // �G�`�揈��
    Enemy::getInstance()->draw();

}
