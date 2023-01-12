<<<<<<< HEAD
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
=======
>>>>>>> f27f2d22d2f22a679c54ef9cb6aa2ff1c2bc980a
