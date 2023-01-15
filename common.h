#pragma once

#include "../GameLib/game_lib.h"
#include "../GameLib/input_manager.h"
#include "../GameLib/obj2d_data.h"
#include "../GameLib/depth_stencil.h"

using namespace GameLib::input;

enum SCENE
{
    TITLE, 
    GAME,
    OVER,
    CLEAR,
};

// ‰¼‚Ì–¼‘O
enum DATA
{
    MARU,
    SIKAKU,
    HOSI,
    SANKAKU
};

enum DIR
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
};

