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
#include "gmgame.h"

BattleViewPlugin::BattleViewPlugin() {
    Console_Output(__FUNCTION__ "\n");
    helloWorldString = "Hello World!";
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
    Console_Output(__FUNCTION__ "\n");
    UnregisterEvent(EVENT_GLOBAL_INI, this);
    UnregisterEvent(EVENT_MAP_INI, this);
    UnregisterEvent(EVENT_CHAT_HOOK, this);
    UnregisterEvent(EVENT_LOAD_LEVEL_HOOK, this);
    UnregisterEvent(EVENT_GAME_OVER_HOOK, this);
    UnregisterEvent(EVENT_PLAYER_JOIN_HOOK, this);
    UnregisterEvent(EVENT_PLAYER_LEAVE_HOOK, this);
    UnregisterEvent(EVENT_THINK_HOOK, this);
}

void BattleViewPlugin::OnLoadGlobalINISettings(INIClass *SSGMIni) {
    SSGMIni->Get_String(helloWorldString, "General", "Hello World!");
    Console_Output(__FUNCTION__ "\n");
}

void BattleViewPlugin::OnFreeData() {
    Console_Output(__FUNCTION__ "\n");
}

// Configure Mode level
void BattleViewPlugin::OnLoadMapINISettings(INIClass *SSGMIni) {
    Console_Output(__FUNCTION__ "\n");
}

void BattleViewPlugin::OnFreeMapData() {
    Console_Output(__FUNCTION__ "\n");
}

// Maybe handle configuration chat commands?
bool BattleViewPlugin::OnChat(int PlayerID, TextMessageEnum Type, const wchar_t *Message, int receiverID) {
    Console_Output(__FUNCTION__ "\n");
    return true;
}

void BattleViewPlugin::OnLoadLevel() {
    Console_Output(__FUNCTION__ "\n");
}

void BattleViewPlugin::OnGameOver() {
    Console_Output(__FUNCTION__ "\n");
}

void BattleViewPlugin::OnPlayerJoin(int PlayerID, const char *PlayerName) {
    Console_Output(__FUNCTION__ "\n");
}

void BattleViewPlugin::OnPlayerLeave(int PlayerID) {
    Console_Output(__FUNCTION__ "\n");
}

// This will probably be our favorite callback
void BattleViewPlugin::OnThink() {
    Console_Output(__FUNCTION__ "\n");
}

BattleViewPlugin battleViewPlugin;

extern "C" __declspec(dllexport) Plugin *Plugin_Init() {
    return &battleViewPlugin;
}
