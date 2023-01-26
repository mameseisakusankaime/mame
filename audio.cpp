#include "all.h"

//--------------------------------------
//  オーディオの初期設定
//--------------------------------------
void audio_init()
{
    // 音楽の読み込み  BGM
    //music::load();
    music::load(0, L"./Data/Musics/title.wav");
    music::load(1, L"./Data/Musics/game.wav");

    // SEの読み込み
    //sound::load();
    sound::load(ATTACK_XWB, L"./Data/Sounds/attack.xwb");
    
    //音量調整
    //sound::setVolume();
}

//--------------------------------------
//  オーディオの終了処理
//--------------------------------------
void audio_deinit()
{
    // 音楽を全て解放
    music::clear();
}
