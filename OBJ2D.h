#pragma once
#include "common.h"

class OBJ2D
{
public:
    int state;                  // state
    
    GameLib::Sprite* data;      // �摜
    VECTOR2 pos;                // �ʒu
    VECTOR2 scale;              // �傫��
    VECTOR2 texPos;             // ���摜�ʒu
    VECTOR2 texSize;            // ���摜�T�C�Y
    int angle;                  // �p�x

    int timer;                  // �^�C�}�[
};