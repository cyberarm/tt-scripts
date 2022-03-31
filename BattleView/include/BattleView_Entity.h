#pragma once

#include "gmplugin.h"

struct BattleViewEntity
{
    int id;
    int team;
    const char* name;
    Vector3 position;
    const char* type;
    double health;
    const char* icon; // Handle on BattleView Frontend?
    const char* character_name;
    const char* vehicle_name;
};