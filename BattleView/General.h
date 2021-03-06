/*	Renegade Scripts.dll
	Copyright 2013 Tiberian Technologies

	This file is part of the Renegade scripts.dll
	The Renegade scripts.dll is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 2, or (at your option) any later
	version. See the file COPYING for more details.
	In addition, an exemption is given to allow Run Time Dynamic Linking of this code with any closed source module that does not contain code covered by this licence.
	Only the source code to the module(s) containing the licenced code has to be released.
*/
#ifndef EXAMPLEPLUGIN_INCLUDE__GENERAL_H
#define EXAMPLEPLUGIN_INCLUDE__GENERAL_H

#define BATTLEVIEW_DEBUG_FUNCTIONS false
#define BATTLEVIEW_DEBUG_ENTITIES false
#define BATTLEVIEW_DEBUG_JSON false
#define BATTLEVIEW_DEBUG_HTTPCLIENT false

// Enable for debugging, disable for release
#ifdef _DEBUG
#pragma warning( disable : 4127) // 4101
#endif

#include "Defines.h"
#include "Standard.h"

#include "include/BattleView.h"
#include "include/BattleView_JSONify.h"

#include "GameObjManager.h"
#include "BuildingGameObj.h"
#include "BuildingGameObjDef.h"
#include "SoldierGameObj.h"
#include "VehicleGameObj.h"
#include "SmartGameObj.h"

#include "scripts.h"
#include "engine_tt.h"
#include "engine_io.h"
#include "gmgame.h"

#endif
