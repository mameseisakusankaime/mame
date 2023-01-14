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

        data = sprite_load(L"./Data/Images/title.png");

        ++state;
        //break;
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
