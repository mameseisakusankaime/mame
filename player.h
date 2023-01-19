#pragma once
#include "OBJ2D.h"

class Player :public OBJ2DManager
{
public:
    static const int OBJ_MAX = 1;
    OBJ2D	obj_w[OBJ_MAX];

    //static GameLib::Sprite* maru;
    //static GameLib::Sprite* sikaku;
    //static GameLib::Sprite* hosi;
    //static GameLib::Sprite* sankaku;

public:
    OBJ2D* begin() { return obj_w; }
    OBJ2D* end() { return obj_w + OBJ_MAX;}

    void init()override;

    

    void setData(int data); // 画像位置設定（画像データ位置） 
    void setSpr(int data);  // 画像設定

    static Player* getInstance()
    {
        static Player instance;
        return &instance;
    }
private:
    Player() {};//マネージャーの複数生成禁止
};

void player(OBJ2D* obj);