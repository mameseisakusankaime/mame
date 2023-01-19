#include "back.h"
#include "common.h"
using namespace GameLib;

const wchar_t* sprite_table[] = {
    L"./Data/Images/back.png",
    L"./Data/Images1/back.png",
    L"./Data/Images2/back.png",
    L"./Data/Images3/back.png",
};

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
            obj[i].data = sprite_load(sprite_table[i / 2]);
            obj[i].pos = {};

            int t = i % 2;
            if (t)//Šï”‚ÌŽž
            {
                obj[i].pos = { 1280 * t,0 };
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
