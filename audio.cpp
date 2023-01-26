#include "all.h"

//--------------------------------------
//  �I�[�f�B�I�̏����ݒ�
//--------------------------------------
void audio_init()
{
    // ���y�̓ǂݍ���  BGM
    //music::load();
    music::load(0, L"./Data/Musics/title.wav");
    music::load(1, L"./Data/Musics/game.wav");

    // SE�̓ǂݍ���
    //sound::load();
    sound::load(ATTACK_XWB, L"./Data/Sounds/attack.xwb");
    
    //���ʒ���
    //sound::setVolume();
}

//--------------------------------------
//  �I�[�f�B�I�̏I������
//--------------------------------------
void audio_deinit()
{
    // ���y��S�ĉ��
    music::clear();
}
