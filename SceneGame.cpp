#include "all.h"

using namespace GameLib::input;

void SceneGame::init()
{
    state = 0;
}

void SceneGame::deinit()
{
    safe_delete(data);
}

void SceneGame::update()
{
    switch (state)
    {
    case 0:
        GameLib::setBlendMode(Blender::BS_ALPHA);

        data = sprite_load(L"./Data/Images/enemy.png");

<<<<<<< HEAD
        state_++;    // �����������̏I��
        /*fallthrough*/
    case 1:
        //////// �ʏ펞�̏��� ////////

        // �I�u�W�F�N�g�̍X�V


        timer_++;

=======
        ++state;
        break;
    case 1:
        if (TRG(0) & PAD_START)setScene(SCENE::TITLE);
>>>>>>> cbe528e29ab2de972c20ff34cdbc92dd8b1cd8a4
        break;
    }
}

void SceneGame::draw()
{
    GameLib::clear(1, 1, 1);

    sprite_render(data, 0, 0);
}
