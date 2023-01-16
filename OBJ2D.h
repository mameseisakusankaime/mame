#pragma once
#include "common.h"

class OBJ2D;
typedef void(*MOVER)(OBJ2D* obj);
typedef bool(*ERASER)(OBJ2D* obj);
 
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
    VECTOR2 pivot;              // 基準点
    int angle;                  // 角度
    VECTOR4 color;                // 色
    

    VECTOR2 offset;
    float radius;

    int timer;                  // タイマー

    MOVER mover;   // 関数ポインタ（移動処理）

    ERASER eraser;

    int hp;         // 体力
    float foundRadius;     // 検知する円

    int dataNum;

    bool invincible;   // 無敵時間(true発動中)
    int invincibleTimer;    // 無敵時間
    int flashingTimer;

    // アニメーション関係
    int animeState;
    int anime;
    int animeTimer;
    bool one;
    bool end;
    bool attack;
    bool half;
    

    float ReferencePosition;    // 動きの基準位置


public:
    OBJ2D() { init(); }
    void init();
    void deinit();
    void clear();
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