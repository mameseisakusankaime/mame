#include "all.h"

void SceneTitle::init()
{
    state = 0;
    moziState = 0;
}

void SceneTitle::deinit()
{
    safe_delete(data);
    safe_delete(sprData);
}

void SceneTitle::update()
{

    float move = 3.0f;

    switch (state)
    {
    case 0:
        GameLib::setBlendMode(Blender::BS_ALPHA);

        data = sprite_load(L"./Data/Images/title.png");
        sprData = sprite_load(L"./Data/Images/title_w.png");

        

        pos[0] = {400,100};
        pos[1] = {630,100};
        pos[2] = {640,260};
        pos[3] = {740,260};
        pos[4] = {840,260};
        pos[5] = {940,260};

        ++state;
        //break;
    case 1:
        if (TRG(0) & PAD_START)setScene(SCENE::GAME);

        switch (moziState)
        {
        case 0:
            pos[2].y += move;
            if (pos[2].y > 330)moziState++;
            break;
        case 1:
            pos[3].y += move;
            if (pos[3].y > 330)moziState++;
            break;
        case 2:
            pos[4].y += move;
            if (pos[4].y > 330)moziState++;
            break;        
        case 3:
            pos[5].y += move;
            if (pos[5].y > 330)moziState++;
            break;
        case 4:
            pos[2].y -= move;
            pos[3].y -= move;
            pos[4].y -= move;
            pos[5].y -= move;
            if (pos[2].y < 260)moziState = 0;
            break;
        }

        break;
    }
}

void SceneTitle::draw() 
{
    GameLib::clear(0, 0, 0);

    sprite_render(data, 0, 0);

    sprite_render(sprData, pos[0].x, pos[0].y, 1, 1, 0, 0, 240, 242);   // Å
    sprite_render(sprData, pos[1].x, pos[1].y, 1, 1, 270, 0, 240, 242); // ‹­

    sprite_render(sprData, pos[2].x, pos[2].y, 1, 1, 0, 242, 110, 110); // ‚·
    sprite_render(sprData, pos[3].x, pos[3].y, 1, 1, 105, 242, 100, 110); // ‚ç
    sprite_render(sprData, pos[4].x, pos[4].y, 1, 1, 210, 242, 110, 110); // ‚·
    sprite_render(sprData, pos[5].x, pos[5].y, 1, 1, 318, 242, 100, 110); // ‚ç

    
}
