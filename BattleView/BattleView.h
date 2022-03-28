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
#pragma once

#include "gmplugin.h"

#define BATTLEVIEW_PLUGIN_VERSION 0.0f

class BattleViewPlugin : public Plugin
{
    StringClass m_battleview_ini_key = "BattleView";
    StringClass m_battleview_ini_mode_key = "mode";
    int m_battleview_mode;

public:
    BattleViewPlugin();

    ~BattleViewPlugin() override;

    void OnLoadGlobalINISettings(INIClass* ssgm_ini) override;

    void OnFreeData() override;

    void OnLoadMapINISettings(INIClass* ssgm_ini) override;

    void OnFreeMapData() override;

    bool OnChat(int player_id, TextMessageEnum type, const wchar_t* message, int receiver_id) override;

    void OnLoadLevel() override;

    void OnGameOver() override;

    void OnPlayerJoin(int player_id, const char* player_name) override;

    void OnPlayerLeave(int player_id) override;

    void OnThink() override;
};