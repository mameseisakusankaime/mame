#pragma once

//******************************************************************************
//
//
//      �Q�[���V�[��
//
//
//******************************************************************************

//==============================================================================
//
//      Game�N���X
//
//==============================================================================

class Game : public Scene
{
private:
    bool            isPaused_;
    static Game     instance_;
    bool            gameOver_;
    int             overTimer_;

public:
    static Game* instance() { return &instance_; }


    void init() override;
    void deinit() override;
    void update() override;
    void draw() override;

    bool getGameOver()const { return this->gameOver_; }
private:
    Game()
        : isPaused_(false)
        , gameOver_(false)
        , overTimer_(0)
    {}
    Game(const Game&) = delete; // = delete �R�s�[�R���X�g���N�^�����݂��Ȃ����Ƃ𖾎�

};

//******************************************************************************

