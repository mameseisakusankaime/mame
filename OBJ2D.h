#pragma once
#include "common.h"

class OBJ2D;
typedef void(*MOVER)(OBJ2D* obj);

class OBJ2D
{
public:
    int state;                  // state
    
    int type;                   // タイプ

    GameLib::Sprite* data;      // 画像
    VECTOR2 pos;                // 位置
    VECTOR2 scale;              // 大きさ
    VECTOR2 texPos;             // 元画像位置
    VECTOR2 texSize;            // 元画像サイズ
    int angle;                  // 角度

    int timer;                  // タイマー

    MOVER mover;   // 関数ポインタ（移動処理）

public:
    OBJ2D() { init(); }
    void init();
    void deinit();
    void update();
    void draw();
};

class OBJ2DManager
{
public:
    virtual OBJ2D* begin() = 0;
    virtual OBJ2D* end() = 0;

    virtual void init();
    virtual void deinit();
    virtual void update();
    virtual void draw();

    OBJ2D* searchSet(MOVER mover, const VECTOR2& pos);
};