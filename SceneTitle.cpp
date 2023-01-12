#include "all.h"
using namespace GameLib::input;


void SceneTitle::init()
{
    state = 0;
}

void SceneTitle::update()
{
    switch (state)
    {
    case 0:
        ++state;
        break;
    case 1:
        if (TRG(0) & PAD_START)
            setScene(SCENE::GAME);
        break;
    }
}

void SceneTitle::draw()
{
    debug::setString("TITLE");
}
