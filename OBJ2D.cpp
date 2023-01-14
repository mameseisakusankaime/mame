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
		if (item.mover == 0) {
			//item.clear();
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
	angle = 0;
	timer = 0;
	mover = nullptr;
}

void OBJ2D::deinit()
{
	safe_delete(data);
}

void OBJ2D::update()
{
	if (mover)mover(this);
}

void OBJ2D::draw()
{
	sprite_render(data, pos.x, pos.y, scale.x, scale.y, texPos.x, texPos.y, texSize.x, texSize.y);
}
