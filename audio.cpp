#include "all.h"

//--------------------------------------
//  �I�[�f�B�I�̏����ݒ�
//--------------------------------------
void audio_init()
{
    // ���y�̓ǂݍ���  BGM
    //music::load();

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
