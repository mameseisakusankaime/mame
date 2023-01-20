#include "OBJ2D.h"
#include "common.h"
using namespace GameLib;

void OBJ2DManager::init()
{
	for (auto& item : *this)item.init();
}

void OBJ2DManager::deinit()
{
	for (auto& item : *this)item.deinit();
}

void OBJ2DManager::update()
{
	for (auto& item : *this)item.update();
}

void OBJ2DManager::draw()
{
	for (auto& item : *this)item.draw();
}

OBJ2D* OBJ2DManager::searchSet(MOVER mover, const VECTOR2& pos)
{
	for (auto& item : *this) {
		if (!item.mover) {
			item.clear();
			item.mover = mover;
			item.pos = pos;
			return &item;
		}
	}
	return nullptr;
}

void OBJ2D::init()
{
	state = 0;
	type = 0;
	
	data = nullptr;
	pos = {};
	scale = {};
	texPos = {};
	texSize = {};
	pivot = {};
	angle = 0;
	color = { 1.0f ,1.0f ,1.0f ,1.0f };

	offset = {};
	radius = 0;

	timer = 0;
	mover = nullptr;
	eraser = nullptr;

	hp = 0;
	attackState = 0;
	foundRadius = 0;
	attackRadius = 0;

	dataNum = 0;

	// 無敵時間
	invincible = false;
	invincibleTimer = 0;
	flashingTimer = 0;

	// アニメーション関係
	animeState = 0;
	anime = 0;
	animeTimer = 0;
	one = false;
	end = false;
	attack = false;
	half = false;

	ReferencePosition = 0;

	size = {};
	holdPosX = 0;
}

void OBJ2D::deinit()
{
	safe_delete(data);
}

void OBJ2D::clear()
{
	init();
}

void OBJ2D::update()
{
	if (mover)mover(this);

	// 消去チェック
	if (eraser && eraser(this)) { clear(); }

}

void OBJ2D::draw()
{
	sprite_render(data, pos.x, pos.y, scale.x, scale.y, texPos.x, texPos.y, texSize.x, texSize.y, pivot.x, pivot.y, angle, color.x, color.y, color.z, color.w);
}

void gravity(OBJ2D* obj) 
{
	obj->pos.y = (std::min)(obj->pos.y+GRAVITY, GROUND);
}