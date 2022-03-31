#pragma once

#include "gmplugin.h"

class BattleViewEntity
{
    int m_id;
    int m_team;
    const char *m_name;
    Vector3 m_position;
    const char *m_type;
    double m_health;
    const char *m_icon; // Handle on BattleView Frontend?
    const char *m_character_name;
    const char *m_vehicle_name;

public:
    BattleViewEntity(
        int id,
        int team,
        const char *name,
        Vector3 position,
        const char *type,
        double health,
        const char *icon,
        const char *character_name,
        const char *vehicle_name);
    ~BattleViewEntity();

    int id();
    int team();
    const char *name();
    Vector3 position();
    const char *type();
    double health();
    const char *icon();
    const char *character_name();
    const char *vehicle_name();
};