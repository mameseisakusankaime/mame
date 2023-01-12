#pragma once

//******************************************************************************
//
//
//      くりあシーン
//
//
//******************************************************************************

//==============================================================================
//
//      Clearクラス
//
//==============================================================================

class Title : public Scene
{
private:
	static Title instance_;

public:
	static Title* instance() { return &instance_; }

	void update() override;
	void draw() override;

private:
	Title() {}
	Title(const Title&) = delete;
};

//******************************************************************************

