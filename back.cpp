#include "back.h"
#include "common.h"
using namespace GameLib;

void Back::init()
{
    for (int i = 0; i < OBJ_MAX; ++i)
    {
        obj[i].state = 0;
    }
}

void Back::deinit()
{
    for (int i = 0; i < OBJ_MAX; ++i)
    {
        safe_delete(obj[i].data);
    }
}

void Back::update()
{
    for (int i = 0; i < OBJ_MAX; ++i)
    {
        switch (obj[i].state)
        {
        case 0:
            obj[i].scale = { 1,1 };

            if (i == 0 || i == 1)
            {
                obj[i].data = sprite_load(L"./Data/Images/back.png");
                obj[i].data = sprite_load(L"./Data/Images/back.png");
            }
            if (i == 2 || i == 3)
            {
                obj[i].data = sprite_load(L"./Data/Images/back1.png");
                obj[i].data = sprite_load(L"./Data/Images/back1.png");
            }
            if (i == 4 || i == 5)
            {
                obj[i].data = sprite_load(L"./Data/Images/back2.png");
                obj[i].data = sprite_load(L"./Data/Images/back2.png");
            }
            if (i == 6 || i == 7)
            {
                obj[i].data = sprite_load(L"./Data/Images/back3.png");
                obj[i].data = sprite_load(L"./Data/Images/back3.png");
            }
            obj[i].pos = {};

            if (i == 1 || i == 3 || i == 5 || i == 7)
            {
                obj[i].pos = { 1280,0 };
                obj[i].scale.x = -1;
            }

            ++obj[i].state;
            //break;
        case 1:
            //obj.pos.x -= 5;
            //if (obj[i].pos.x <= -1280)obj[i].pos.x += 1280;



            //obj[i].pos.x -= 5;

            break;
        }
    }
}

void Back::draw()
{
    for (int i = 0; i < OBJ_MAX; ++i)
    {
        sprite_render(obj[i].data, obj[i].pos.x, obj[i].pos.y, obj[i].scale.x, obj[i].scale.y);
    }
}
