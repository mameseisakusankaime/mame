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

    debug::setString("gameover");

}


