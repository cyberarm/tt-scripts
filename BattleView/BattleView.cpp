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
#include "General.h"
#include "BattleView.h"
#include "engine_tt.h"
#include "engine_io.h"
#include "Defines.h"
#include "GameObjManager.h"
#include "gmgame.h"

BattleViewPlugin::BattleViewPlugin() {
    Console_Output("[BattleView] Loading cyberarm's BattleView Plugin v%d\n", BATTLEVIEW_PLUGIN_VERSION);
    RegisterEvent(EVENT_GLOBAL_INI, this);
    RegisterEvent(EVENT_MAP_INI, this);
    RegisterEvent(EVENT_CHAT_HOOK, this);
    RegisterEvent(EVENT_LOAD_LEVEL_HOOK, this);
    RegisterEvent(EVENT_GAME_OVER_HOOK, this);
    RegisterEvent(EVENT_PLAYER_JOIN_HOOK, this);
    RegisterEvent(EVENT_PLAYER_LEAVE_HOOK, this);
    RegisterEvent(EVENT_THINK_HOOK, this);
}

BattleViewPlugin::~BattleViewPlugin() {
    Console_Output("[BattleView] Unloading cyberarm's BattleView Plugin v%d\n", BATTLEVIEW_PLUGIN_VERSION);
    UnregisterEvent(EVENT_GLOBAL_INI, this);
    UnregisterEvent(EVENT_MAP_INI, this);
    UnregisterEvent(EVENT_CHAT_HOOK, this);
    UnregisterEvent(EVENT_LOAD_LEVEL_HOOK, this);
    UnregisterEvent(EVENT_GAME_OVER_HOOK, this);
    UnregisterEvent(EVENT_PLAYER_JOIN_HOOK, this);
    UnregisterEvent(EVENT_PLAYER_LEAVE_HOOK, this);
    UnregisterEvent(EVENT_THINK_HOOK, this);
}

void BattleViewPlugin::OnLoadGlobalINISettings(INIClass *ssgm_ini) {
    Console_Output("[BattleView] Attempting to load global INI settings...\n");
    m_battleview_mode = ssgm_ini->Get_Int(m_battleview_ini_key, m_battleview_ini_mode_key, 0);
    Console_Output(__FUNCTION__ "\n");
}

// Don't need?
void BattleViewPlugin::OnFreeData() {
    Console_Output(__FUNCTION__ "\n");
}

// Configure Mode level
void BattleViewPlugin::OnLoadMapINISettings(INIClass *ssgm_ini) {
    Console_Output("[BattleView] Attempting to load map INI settings...\n");
}

void BattleViewPlugin::OnFreeMapData() {
    Console_Output(__FUNCTION__ "\n");
}

// Maybe handle configuration chat commands?
bool BattleViewPlugin::OnChat(int player_id, TextMessageEnum type, const wchar_t *message, int receiver_id) {
    Console_Output(__FUNCTION__ "\n");
    return true;
}

// TODO: Cache current server and map name
void BattleViewPlugin::OnLoadLevel() {
    Console_Output(__FUNCTION__ "\n");
}

void BattleViewPlugin::OnGameOver() {
    Console_Output(__FUNCTION__ "\n");
}

void BattleViewPlugin::OnPlayerJoin(int player_id, const char *player_name) {
    Console_Output(__FUNCTION__ "\n");
}

void BattleViewPlugin::OnPlayerLeave(int player_id) {
    Console_Output(__FUNCTION__ "\n");
}

// This will probably be our favorite callback
void BattleViewPlugin::OnThink() {
    Console_Output(__FUNCTION__ "\n");

    for (SLNode<BuildingGameObj> *z = GameObjManager::BuildingGameObjList.Head(); z; z = z->Next()) {
        GameObject *building = z->Data();

        Vector3 pos;
        building->Get_Position(&pos);
        Get_Team
    }

    for (SLNode<cPlayer> *z = Get_Player_List()->Head(); z; z = z->Next()) {
        cPlayer * player = z->Data();

        Vector3 pos;

        player->Get_Is_Active();
        player->Get_Is_In_Game();
        player->Is_Team_Player();
        player->Get_World_Position(pos);

        if (player->Get_Is_In_Game() && player->Get_Player_Type() == Team) {
        }
    }
}

BattleViewPlugin battleViewPlugin;

extern "C" __declspec(dllexport) Plugin *Plugin_Init() {
    return &battleViewPlugin;
}
