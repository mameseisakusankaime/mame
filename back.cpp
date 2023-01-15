#include "back.h"
#include "common.h"
using namespace GameLib;

void Back::init()
{
    obj.state = 0;
}

void Back::deinit()
{
    safe_delete(obj.data);
}

void Back::update()
{  
    switch (obj.state)
    {
    case 0:
        obj.data = sprite_load(L"./Data/Images/back.png");
        obj.pos = {};

        ++obj.state;
        //break;
    case 1:
        //obj.pos.x -= 5;
        if (obj.pos.x <= -1280)obj.pos.x += 1280;//loop

        break;
    }
}

void Back::draw()
{
    sprite_render(obj.data, obj.pos.x, obj.pos.y);
}
