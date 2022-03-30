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

struct BattleViewPlayer
{
    int player_id;
    int entity_id;
    const char* username;
};

struct BattleViewEntity
{
    int id;
    int team;
    const char* name;
    // Vector3 position;
    const char* type;
    int health;
    const char* icon; // Handle on BattleView Frontend?
    const char* character_name;
    const char* vehicle_name;
};

class BattleViewPlugin : public Plugin
{
    // Settings
    int m_config_mode;
    bool m_config_bots_as_players;

    // Think Limiter
    int m_think_interval;
    int m_think_counter;

    // TODO: Why angry?
    // VectorClass<BattleViewPlayer> m_battleview_players;
    // VectorClass<BattleViewEntity> m_battleview_entities;

public:
    BattleViewPlugin();

    virtual ~BattleViewPlugin();

    void HandleINIConfiguration(INIClass* ssgm, bool is_map);

    virtual void OnLoadGlobalINISettings(INIClass* ssgm_ini);

    virtual void OnFreeData();

    virtual void OnLoadMapINISettings(INIClass* ssgm_ini);

    virtual void OnFreeMapData();

    virtual bool OnChat(int player_id, TextMessageEnum type, const wchar_t* message, int receiver_id);

    virtual void OnLoadLevel();

    virtual void OnGameOver();

    virtual void OnPlayerJoin(int player_id, const char* player_name);

    virtual void OnPlayerLeave(int player_id);

    virtual void OnThink();
};