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

BattleViewPlugin::BattleViewPlugin()
{
    if (BATTLEVIEW_DEBUG_FUNCTIONS)
        Console_Output("[BattleView] Loading cyberarm's BattleView Plugin v%d\n", BATTLEVIEW_PLUGIN_VERSION);
    RegisterEvent(EVENT_GLOBAL_INI, this);
    RegisterEvent(EVENT_MAP_INI, this);
    RegisterEvent(EVENT_CHAT_HOOK, this);
    RegisterEvent(EVENT_LOAD_LEVEL_HOOK, this);
    RegisterEvent(EVENT_GAME_OVER_HOOK, this);
    RegisterEvent(EVENT_PLAYER_JOIN_HOOK, this);
    RegisterEvent(EVENT_PLAYER_LEAVE_HOOK, this);
    RegisterEvent(EVENT_THINK_HOOK, this);

    m_think_interval = 10; // 500;             // 60;
    m_think_counter = m_think_interval; // Run at first call

    m_http_client = nullptr;

    m_level_loaded = false;

    int iResult;
    WSADATA wsaData;

    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != NO_ERROR) {
        Console_Output("WSAStartup failed with error: %d\n", iResult);
        return;
    }

    m_udp_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (m_udp_socket == INVALID_SOCKET) {
        Console_Output("socket failed with error: %ld\n", WSAGetLastError());
        WSACleanup();
        return;
    }

    m_udp_socket_addr.sin_family = AF_INET;
    m_udp_socket_addr.sin_port = htons(50789);
    m_udp_socket_addr.sin_addr.s_addr = inet_addr("192.168.195.29");
}

BattleViewPlugin::~BattleViewPlugin()
{
    closesocket(m_udp_socket);
    WSACleanup();

    if (BATTLEVIEW_DEBUG_FUNCTIONS)
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

void BattleViewPlugin::HandleINIConfiguration(INIClass *ssgm_ini, bool is_map)
{
    m_config_mode = ssgm_ini->Get_Int("BattleView", "mode", is_map ? m_config_mode : 0);                                      // BattleView Frontend is currently fixed at mode 7
    m_config_bots_as_players = ssgm_ini->Get_Bool("BattleView", "bots_as_players", is_map ? m_config_bots_as_players : true); // Appease SkyNET

    /* Initializing HTTPClient may only happen once, via GlobalINI */
    if (!is_map && false)//!m_http_client)
        return;

    char endpoint[1024];
    char token[256];

    ssgm_ini->Get_String("BattleView", "endpoint", "http://localhost:80/api/v1/battleview", endpoint, 1024);
    ssgm_ini->Get_String("BattleView", "token", nullptr, token, 256);

    m_endpoint = reinterpret_cast<const char*>(endpoint);
    m_token = reinterpret_cast<const char*>(token);
}

/*************************
 * Load Global Settings
 */
void BattleViewPlugin::OnLoadGlobalINISettings(INIClass *ssgm_ini)
{
    if (BATTLEVIEW_DEBUG_FUNCTIONS) {
        Console_Output(__FUNCTION__ "\n");
        Console_Output("[BattleView] Attempting to load global INI settings...\n");
    }

    HandleINIConfiguration(ssgm_ini, false);
}

// Don't need? What do?
void BattleViewPlugin::OnFreeData()
{
    if (BATTLEVIEW_DEBUG_FUNCTIONS)
        Console_Output(__FUNCTION__ "\n");
}

// Configure Mode level
void BattleViewPlugin::OnLoadMapINISettings(INIClass *ssgm_ini)
{
    if (BATTLEVIEW_DEBUG_FUNCTIONS)
        Console_Output("[BattleView] Attempting to load map INI settings...\n");

    HandleINIConfiguration(ssgm_ini, true);
}

void BattleViewPlugin::OnFreeMapData()
{
    if (BATTLEVIEW_DEBUG_FUNCTIONS)
        Console_Output(__FUNCTION__ "\n");
}

// Maybe handle configuration chat commands?
bool BattleViewPlugin::OnChat(int player_id, TextMessageEnum type, const wchar_t *message, int receiver_id)
{
    if (BATTLEVIEW_DEBUG_FUNCTIONS)
        Console_Output(__FUNCTION__ "\n");

    const char *message_type = "UNKNOWN";

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

    if (BATTLEVIEW_DEBUG_FUNCTIONS)
        Console_Output("[%s] (%i) %s wrote: %s [%i]\n", message_type, player_id, "?sender_name?", message, receiver_id);
    return true;
}

// TODO: Cache current server and map name
void BattleViewPlugin::OnLoadLevel()
{
    if (BATTLEVIEW_DEBUG_FUNCTIONS)
        Console_Output(__FUNCTION__ "\n");

    m_level_loaded = true;
}

void BattleViewPlugin::OnGameOver()
{
    if (BATTLEVIEW_DEBUG_FUNCTIONS)
        Console_Output(__FUNCTION__ "\n");

    m_level_loaded = false;
}

void BattleViewPlugin::OnPlayerJoin(int player_id, const char *player_name)
{
    if (BATTLEVIEW_DEBUG_FUNCTIONS)
        Console_Output(__FUNCTION__ "\n");
}

void BattleViewPlugin::OnPlayerLeave(int player_id)
{
    if (BATTLEVIEW_DEBUG_FUNCTIONS)
        Console_Output(__FUNCTION__ "\n");
}

// This will probably be our favorite callback
void BattleViewPlugin::OnThink()
{
    // Don't think unless the http client is ready
    // if (!m_http_client || (m_http_client && !m_http_client->is_ready()))
    // {
        // Console_Output("HTTPClient not ready.\n");
        // return;
    // }

    if (!m_level_loaded) return;

    m_think_counter += 1;

    if (m_think_counter < m_think_interval)
        return;

    m_think_counter = 0;

    if (BATTLEVIEW_DEBUG_FUNCTIONS)
        Console_Output(__FUNCTION__ "\n");

    m_structures.Clear();
    m_players.Clear();
    m_vehicles.Clear();

    // TODO: Some base defenses are actually VEHICLES, like turrets
    //       Inter

    if (BATTLEVIEW_DEBUG_ENTITIES)
        Console_Output("Buildings:\n");

    for (SLNode<BuildingGameObj> *z = GameObjManager::BuildingGameObjList.Head(); z; z = z->Next())
    {
        BuildingGameObj *obj = z->Data();

        game_object_to_entity(obj);
    }

    if (BATTLEVIEW_DEBUG_ENTITIES)
        Console_Output("Players:\n");

    for (SLNode<SoldierGameObj> *z = GameObjManager::SoldierGameObjList.Head(); z; z = z->Next())
    {
        SoldierGameObj *obj = z->Data();

        if (obj->Is_Bot() && !m_config_bots_as_players)
            continue;

        game_object_to_entity(obj);
    }

    if (BATTLEVIEW_DEBUG_ENTITIES)
        Console_Output("Vehicles:\n");

    for (SLNode<VehicleGameObj> *z = GameObjManager::VehicleGameObjList.Head(); z; z = z->Next())
    {
        VehicleGameObj *obj = z->Data();

        bool is_bot = false;
        GameObject *game_object = Get_Vehicle_Driver(obj);

        if (game_object != nullptr)
            is_bot = game_object->As_SoldierGameObj()->Is_Bot();

        // Give bots the power of invisiblity unless you appease SkyNET
        if (is_bot && !m_config_bots_as_players)
            continue;

        game_object_to_entity(obj);
    }

    StringClass sane;
    WideStringClass w_f = The_Game()->Get_Game_Name();
    w_f.Convert_To(sane);

    const char *json;
    json = BattleViewJSONify::BattleViewJSONify(0, 7, sane, The_Game()->Get_Map_Name(), m_structures, m_players, m_vehicles).to_json();
    if (BATTLEVIEW_DEBUG_JSON)
        Console_Output("JSON: %s\n", json);

    //if (m_http_client->is_ready()) {
    //    m_http_client->post(json);
    //}

    // TODO: fail if m_udp_socket is bad
    int iResult = sendto(m_udp_socket, json, strlen(json), 0, (SOCKADDR*)&m_udp_socket_addr, sizeof(m_udp_socket_addr));
    if (iResult == SOCKET_ERROR) {
        Console_Output("closesocket failed with error: %d\n", WSAGetLastError());
    }
}

// For SoldierGameObj and VehicleGameObj
BattleViewEntity *BattleViewPlugin::game_object_to_entity(SmartGameObj *obj)
{
    Vector3 pos;

    obj->Get_World_Position(pos);

    // Get total health and armor (shields) in range 0.0..100.0
    double health = ((Commands->Get_Health(obj) + Commands->Get_Shield_Strength(obj)) /
                     (Commands->Get_Max_Health(obj) + Commands->Get_Max_Shield_Strength(obj)) * 100.0);

    const char *type;
    const char *name;
    const char *character_name;
    const char *vehicle_name;
    bool is_structure;
    type = "SOLDIER";
    name = nullptr;
    character_name = nullptr;
    vehicle_name = nullptr;
    is_structure = false;

    if (obj->As_VehicleGameObj() != nullptr)
    {
        type = "VEHICLE";
        vehicle_name = Get_Translated_Preset_Name(obj);

        if (Get_Vehicle_Driver(obj))
        {
            name = Get_Player_Name(Get_Vehicle_Driver(obj));
            character_name = Get_Translated_Preset_Name(Get_Vehicle_Driver(obj)->As_SoldierGameObj());
        }
    }
    else {
        name = Get_Player_Name(obj);
    }
    if (Get_Vehicle_Mode(obj) == VEHICLE_TYPE_TURRET)
    {
        type = "BASE_DEFENSE";
        is_structure = true;
    }
    if (obj->Get_Type() == VEHICLE_TYPE_FLYING)
        type = "AIRCRAFT";
    if (obj->Get_Type() == VEHICLE_TYPE_SUB)
        type = "SHIP";
    if (Is_Harvester(obj))
        type = "HARVESTER";

    if (obj->As_SoldierGameObj() != nullptr)
        character_name = Get_Translated_Definition_Name(Commands->Get_Preset_Name(obj->As_SoldierGameObj()));

    if (!is_structure && name == nullptr)
        Get_Player_Name(obj);

    BattleViewEntity *entity;
    entity = new BattleViewEntity(
        obj->Get_ID(),
        obj->Get_Player_Type(),
        is_structure ? Get_Translated_Preset_Name(obj) : name,
        pos,  // X, Y[Actually .Z here], FACING
        type, // SOLDIER, VEHICLE, AIRCRAFT, SHIP, HARVESTER
        health,
        Commands->Get_Preset_Name(obj),
        character_name,
        vehicle_name);

    if (BATTLEVIEW_DEBUG_ENTITIES) {
        Console_Output(
          "ID: %i, TEAM: %i, NAME: %s, POSITION: [%0.2f, %0.2f, %0.2f], TYPE: %s, HEALTH: %0.2f, ICON: %s, CHAR: %s, VEHICLE: %s\n",
          entity->id(), entity->team(), entity->name(), entity->position().X, entity->position().Y, entity->position().Z, entity->type(), entity->health(), entity->icon(), entity->character_name(), entity->vehicle_name());
    }

    if (is_structure)
    {
        m_structures.Add(entity); // Turrets and co. are technically vehicles
    }
    else if (vehicle_name != nullptr)
    {
        m_vehicles.Add(entity);
    }
    else
    {
        m_players.Add(entity);
    }

    return entity;
}

// For BuildingGameObj
BattleViewEntity *BattleViewPlugin::game_object_to_entity(BuildingGameObj *obj)
{
    Vector3 pos;

    // Get total health and armor (shields) in range 0.0..100.0
    double health = ((Commands->Get_Health(obj) + Commands->Get_Shield_Strength(obj)) /
                     (Commands->Get_Max_Health(obj) + Commands->Get_Max_Shield_Strength(obj)) * 100.0);

    bool base_defense = obj->Get_Definition().Get_Type() == BuildingConstants::BuildingType::TYPE_BASE_DEFENSE;

    obj->Get_World_Position(pos);

    BattleViewEntity *entity;
    entity = new BattleViewEntity(
        obj->Get_ID(),
        obj->Get_Player_Type(),
        Get_Translated_Preset_Name(obj),
        pos,
        base_defense ? "BASE_DEFENSE" : "BUILDING",
        health,
        Commands->Get_Preset_Name(obj),
        nullptr,
        nullptr);

    if (BATTLEVIEW_DEBUG_ENTITIES) {
        Console_Output(
            "ID: %i, TEAM: %i, NAME: %s, POSITION: [%0.2f, %0.2f, %0.2f], TYPE: %s, HEALTH: %0.2f, ICON: %s, CHAR: %s, VEHICLE: %s\n",
            entity->id(), entity->team(), entity->name(), entity->position().X, entity->position().Y, entity->position().Z, entity->type(), entity->health(), entity->icon(), entity->character_name(), entity->vehicle_name());
    }

    m_structures.Add(entity);

    return entity;
}

BattleViewPlugin battleViewPlugin;

extern "C" __declspec(dllexport) Plugin *Plugin_Init()
{
    return &battleViewPlugin;
}
