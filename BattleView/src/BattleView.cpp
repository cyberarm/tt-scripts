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

    m_think_interval = 500; // 60;
    m_think_counter = m_think_interval; // Run at first call

    m_http_client = nullptr;
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

/*************
* HELPER METHODS
*/

void BattleViewPlugin::HandleINIConfiguration(INIClass* ssgm_ini, bool is_map)
{
    m_config_mode            = ssgm_ini->Get_Int ("BattleView", "mode",            is_map ? m_config_mode : 0); // BattleView Frontend is currently fixed at mode 7
    m_config_bots_as_players = ssgm_ini->Get_Bool("BattleView", "bots_as_players", is_map ? m_config_bots_as_players : true); // Appease SkyNET

    /* Initializing HTTPClient may only happen once, via GlobalINI */
    if (!is_map && m_http_client != nullptr)
        return;

    char endpoint[1024];
    char token[256];

    ssgm_ini->Get_String("BattleView", "endpoint", "http://localhost:80/api/v1/battleview", endpoint, 1024);
    ssgm_ini->Get_String("BattleView", "token", nullptr, token, 256);

    m_http_client = new BattleViewHTTPClient(reinterpret_cast<const char*>(endpoint), reinterpret_cast<const char*>(token));
}


/*************************
* Load Global Settings
*/
void BattleViewPlugin::OnLoadGlobalINISettings(INIClass *ssgm_ini) {
    Console_Output(__FUNCTION__ "\n");
    Console_Output("[BattleView] Attempting to load global INI settings...\n");

    HandleINIConfiguration(ssgm_ini, false);
}

// Don't need? What do?
void BattleViewPlugin::OnFreeData() {
    Console_Output(__FUNCTION__ "\n");
}

// Configure Mode level
void BattleViewPlugin::OnLoadMapINISettings(INIClass *ssgm_ini) {
    Console_Output("[BattleView] Attempting to load map INI settings...\n");

    HandleINIConfiguration(ssgm_ini, true);
}

void BattleViewPlugin::OnFreeMapData() {
    Console_Output(__FUNCTION__ "\n");
}

// Maybe handle configuration chat commands?
bool BattleViewPlugin::OnChat(int player_id, TextMessageEnum type, const wchar_t *message, int receiver_id) {
    Console_Output(__FUNCTION__ "\n");

    const char* message_type = "UNKNOWN";

    switch (type)
    {
    case TEXT_MESSAGE_PUBLIC:
        message_type = "PUBLIC";
        break;
    case TEXT_MESSAGE_TEAM:
        message_type = "TEAM";
        break;
    case TEXT_MESSAGE_PRIVATE:
        message_type = "PRIVATE";
        break;
    case TEXT_MESSAGE_TMSG:
        message_type = "TMSG";
        break;
    default:
        break;
    }

    Console_Output("[%s] (%i) %s wrote: %s [%i]\n", message_type, player_id, "?sender_name?", message, receiver_id);
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
    // Don't think unless the http client is ready
    if (!m_http_client || (m_http_client && !m_http_client->is_ready()))
        return;

    m_think_counter += 1;

    if (m_think_counter < m_think_interval)
        return;

    m_think_counter = 0;

    Console_Output(__FUNCTION__ "\n");

    Console_Output("Buildings:\n");
    for (SLNode<BuildingGameObj>* z = GameObjManager::BuildingGameObjList.Head(); z; z = z->Next()) {
        BuildingGameObj* obj = z->Data();

        Vector3 pos;

        obj->Get_World_Position(pos);
        double health = 100.0; // (Commands->Get_Health(soldier) / Commands->Get_Max_Health(soldier)) * 100.0;

        bool base_defense = obj->Get_Definition().Get_Type() == BuildingConstants::BuildingType::TYPE_BASE_DEFENSE;

        BattleViewEntity entity;
        entity.id = obj->Get_ID();
        entity.team = obj->Get_Player_Type();
        entity.name = Get_Translated_Preset_Name(obj);
        entity.position = pos;
        entity.type = base_defense ? "BASE_DEFENSE" : "BUILDING"; // BUILDING, BASE_DEFENSE
        entity.health = health;
        entity.icon = "";
        entity.character_name = nullptr;
        entity.vehicle_name = nullptr; // soldier->Get_Vehicle() != nullptr ? (const char*)soldier->Get_Vehicle()->Get_Vehicle_Name() : nullptr;

        Console_Output(
            "ID: %i, TEAM: %i, NAME: %s, POSITION: [%0.2f, %0.2f, %0.2f], TYPE: %s, HEALTH: %0.2f, ICON: %s, CHAR: %s, VEHICLE: %s\n",
            entity.id, entity.team, entity.name, entity.position.X, entity.position.Y, entity.position.Z, entity.type, entity.health, entity.icon, entity.character_name, entity.vehicle_name
        );

        // Console_Output("Name: %s, Prefix: %s at X: %f,Y: %f, Z: %f for Team ID %i\n", Get_Translated_Preset_Name(building), building->Get_Name_Prefix(), pos.X, pos.Y, pos.Z, building->Get_Player_Type());
    }

    Console_Output("Players:\n");
    for (SLNode<SoldierGameObj>* z = GameObjManager::SoldierGameObjList.Head(); z; z = z->Next()) {
        SoldierGameObj* obj = z->Data();
        Vector3 pos;

        if (obj->Is_Bot() && !m_config_bots_as_players)
            continue;

        obj->Get_World_Position(pos);
        double health = 100.0; // (Commands->Get_Health(soldier) / Commands->Get_Max_Health(soldier)) * 100.0;

        BattleViewEntity entity;
        entity.id = obj->Get_ID();
        entity.team = obj->Get_Player_Type();
        entity.name = Get_Player_Name(obj);
        entity.position = pos;
        entity.type = "SOLDIER"; // SOLDIER, VEHICLE, AIRCRAFT, [HELICOPTER?], HARVESTER
        entity.health = health;
        entity.icon = "";
        entity.character_name = Get_Translated_Preset_Name(obj);
        entity.vehicle_name = nullptr; // soldier->Get_Vehicle() != nullptr ? (const char*)soldier->Get_Vehicle()->Get_Vehicle_Name() : nullptr;

        Console_Output(
            "ID: %i, TEAM: %i, NAME: %s, POSITION: [%0.2f, %0.2f, %0.2f], TYPE: %s, HEALTH: %0.2f, ICON: %s, CHAR: %s, VEHICLE: %s\n",
            entity.id, entity.team, entity.name, entity.position.X, entity.position.Y, entity.position.Z, entity.type, entity.health, entity.icon, entity.character_name, entity.vehicle_name
        );
    }

    if (m_http_client->is_ready()) {
        m_http_client->enqueue(nullptr);
        m_http_client->post();
    }
}

BattleViewPlugin battleViewPlugin;

extern "C" __declspec(dllexport) Plugin *Plugin_Init() {
    return &battleViewPlugin;
}
