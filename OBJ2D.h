#pragma once
#include "common.h"

class OBJ2D
{
public:
    int state;                  // state
    
    GameLib::Sprite* data;      // 画像
    VECTOR2 pos;                // 位置
    VECTOR2 scale;              // 大きさ
    VECTOR2 texPos;             // 元画像位置
    VECTOR2 texSize;            // 元画像サイズ
    int angle;                  // 角度

    int timer;                  // タイマー
};