#pragma once
#include "OBJ2D.h"

class Gimmick : public OBJ2DManager
{
public:
	static const int OBJ_MAX = 10;
	OBJ2D obj_w[OBJ_MAX];
public:
	virtual OBJ2D* begin()override { return &obj_w[0]; }
	virtual OBJ2D* end()override { return &obj_w[OBJ_MAX]; }
	virtual ~Gimmick() {};
	void init()override;

	/// <summary>
	/// singleton
	/// </summary>
	/// <returns>アドレス</returns>
	static Gimmick* getInstance()
	{
		static Gimmick instance;
		return &instance;
	}

private:
	Gimmick() {}
	Gimmick(const Gimmick&) = delete;//コピー禁止
	Gimmick operator=(const Gimmick&) = delete;//代入禁止

};

bool gimmick_erase(OBJ2D* obj);

void gimmick_Blok(OBJ2D* obj);
void gimmick_Button(OBJ2D* obj);
void gimmick_door(OBJ2D* obj);