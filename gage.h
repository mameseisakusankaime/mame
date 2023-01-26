#pragma once
#include "OBJ2D.h"

/// <summary>
/// ゲージ管理クラス
/// </summary>
class Gage :public OBJ2DManager
{
public:
    static const int OBJ_MAX = 20;
    OBJ2D obj_w[OBJ_MAX];

public:
    OBJ2D* begin() { return obj_w; }
    OBJ2D* end() { return obj_w + OBJ_MAX; }

    void init()override;

    static Gage* getInstance() 
    {
        static Gage instance;
        return &instance;
    }
};

void gage(OBJ2D* obj);