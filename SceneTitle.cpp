#include "all.h"

void SceneTitle::init()
{
    state = 0;
}

void SceneTitle::deinit()
{
    safe_delete(data);
}

void SceneTitle::update()
{
    switch (state)
    {
    case 0:
        GameLib::setBlendMode(Blender::BS_ALPHA);

<<<<<<< HEAD
        data = sprite_load(L"./Data/Images/title.png");
=======
<<<<<<< HEAD
        timer_ = 0;                                  // �^�C�}�[��������
        GameLib::setBlendMode(Blender::BS_ALPHA);   // �ʏ�̃A���t�@����
        state_++;                                    // �����������̏I��


        /*fallthrough*/                             // �Ӑ}�I��break;���L�q���Ă��Ȃ�
=======
        data = sprite_load(L"./Data/Images/00.png");
>>>>>>> f5afa223287260088b258565cfa4fee4d7adaf38

        ++state;
        break;
>>>>>>> cbe528e29ab2de972c20ff34cdbc92dd8b1cd8a4
    case 1:
        if (TRG(0) & PAD_START)setScene(SCENE::GAME);
        break;
    }
}

void SceneTitle::draw()
{
    GameLib::clear(0, 0, 0);

    sprite_render(data, 0, 0);
}
