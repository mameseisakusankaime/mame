#include "all.h"

void SceneOver::init()
{
    state = 0;
    timer = 0;
}

void SceneOver::deinit()
{
    safe_delete(data);
}

void SceneOver::update()
{ 
    switch (state)
    {
    case 0:
        GameLib::setBlendMode(Blender::BS_ALPHA);
        data = sprite_load(L"./Data/Images/game_over.png");

        ++state;
        //break;
    case 1:
        if (TRG(0) & PAD_START)
            setScene(SCENE::TITLE);

        break;
    }
    this->timer++;
}

void SceneOver::draw()
{
    GameLib::clear(0, 0, 0);
    
    sprite_render(this->data, 0, 0, 1.0f, 1.0f, (std::min)((this->timer / 10),8) * 1280, 0, 1280, 720);
}


