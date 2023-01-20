#pragma once
//******************************************************************************
//
//
//      all.h
//
//
//******************************************************************************

//システムやライブラリのヘッダーファイルは上の方へ
#include "common.h"
#include "audio.h"

#include "OBJ2D.h"

#include "Scene.h"
#include "SceneTitle.h"
#include "SceneGame.h"
#include "SceneOver.h"

#include "back.h"
#include "player.h"
#include "enemy.h"
#include "gage.h"
#include "find.h"
#include "gimmick.h"

using namespace GameLib;
 
void setScene(int scene);