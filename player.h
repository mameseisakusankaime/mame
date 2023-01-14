#pragma once
#include "OBJ2D.h"

class Player
{
public:
    OBJ2D obj;

    static GameLib::Sprite* maru;
    static GameLib::Sprite* sikaku;
    static GameLib::Sprite* hosi;
    static GameLib::Sprite* sankaku;

public:
    void init();
    void deinit();
    void update();
    void draw();

    void setData(int data); // 画像位置設定（画像データ位置） 
    void setSpr(int data);  // 画像設定
};

// 仮の名前
enum DATA
{
    MARU,
    SIKAKU,
    HOSI,
    SANKAKU
};