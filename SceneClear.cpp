#include "all.h"

void SceneClear::init()
{
    state = 0;
    timer = 0;
}

void SceneClear::deinit()
{
    safe_delete(data);
}

void SceneClear::update()
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

void SceneClear::draw()
{
    GameLib::clear(0, 0, 0);

    text_out(1, "GAME CLEAR", 1280/2, 720/2, 3.0f, 3.0f,1.0f,1.0f,1.0f,1.0f,GameLib::TEXT_ALIGN::MIDDLE);

}
