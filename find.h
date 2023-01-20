#pragma once
#include "OBJ2D.h"

/// <summary>
/// !É}Å[ÉN
/// </summary>
class Find :public OBJ2DManager
{
public:
    static const int OBJ_MAX = 30;
    OBJ2D obj_w[OBJ_MAX];

public:
    OBJ2D* begin() { return obj_w; }
    OBJ2D* end() { return obj_w + OBJ_MAX; }

    void init()override;

    static Find* getInstance()
    {
        static Find instance;
        return &instance; 
    }
};

void find(OBJ2D* obj);