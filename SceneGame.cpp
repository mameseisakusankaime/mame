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

    // �w�i�I������
    back.deinit();
    // �v���C���[�I������
    player.deinit();
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
        player.init();

<<<<<<< HEAD
        state_++;    // �����������̏I��
        /*fallthrough*/
    case 1:
        //////// �ʏ펞�̏��� ////////

        // �I�u�W�F�N�g�̍X�V


        timer_++;

=======
        ++state;
        //break;
    case 1:
        if (TRG(0) & PAD_START)setScene(SCENE::TITLE);
<<<<<<< HEAD

        // �w�i�X�V
        back.update();
        // �v���C���[�X�V����
        player.update();

=======
>>>>>>> cbe528e29ab2de972c20ff34cdbc92dd8b1cd8a4
>>>>>>> f5afa223287260088b258565cfa4fee4d7adaf38
        break;
    }
}

void SceneGame::draw()
{
    GameLib::clear(1, 1, 1);

    // �w�i�`��
    back.draw();
    // �v���C���[�`�揈��
    player.draw();
}
