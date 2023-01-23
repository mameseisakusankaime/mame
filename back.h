#pragma once
#include "OBJ2D.h"

class Back :public OBJ2DManager
{
public:
    static const int OBJ_MAX = 10;
    OBJ2D obj[OBJ_MAX];

public:
    OBJ2D* begin() { return obj; }
    OBJ2D* end() { return obj + OBJ_MAX; }

    void init()override;
    
    static Back* getInstance()
    {
        static Back instance;
        return &instance;
    }
};

void back_update0(OBJ2D* obj);
void back_update1(OBJ2D* obj);
void back_update2(OBJ2D* obj);
void back_update3(OBJ2D* obj);

void sea_update0(OBJ2D* obj);
void sea_update1(OBJ2D* obj);
void sea_update2(OBJ2D* obj);
void sea_update3(OBJ2D* obj);