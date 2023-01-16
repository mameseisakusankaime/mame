#pragma once
#include "OBJ2D.h"

class Back
{
public:
    static const int OBJ_MAX = 8;
    OBJ2D obj[OBJ_MAX];

public:
    void init();
    void deinit();
    void update();
    void draw();
};