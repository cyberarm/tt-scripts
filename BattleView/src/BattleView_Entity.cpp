#include "general.h"
#include "include/BattleView_Entity.h"

// Moved away from a struct because of confusion over the meaning .Length() vs .Count()...
BattleViewEntity::BattleViewEntity(
    int id,
    int team,
    const char *name,
    Vector3 position,
    const char *type,
    double health,
    const char *icon,
    const char *character_name,
    const char *vehicle_name)
{
    m_id = id;
    m_team = team;
    m_name = name;
    m_position = position;
    m_type = type;
    m_health = health;
    m_icon = icon;
    m_character_name = character_name;
    m_vehicle_name = vehicle_name;
}

BattleViewEntity::~BattleViewEntity()
{
}

int BattleViewEntity::id()
{
    return m_id;
}

int BattleViewEntity::team()
{
    return m_team;
}

const char *BattleViewEntity::name()
{
    return m_name;
}

Vector3 BattleViewEntity::position()
{
    return m_position;
}

const char *BattleViewEntity::type()
{
    return m_type;
}

double BattleViewEntity::health()
{
    return m_health;
}

const char *BattleViewEntity::icon()
{
    return m_icon;
}

const char *BattleViewEntity::character_name()
{
    return m_character_name;
}

const char *BattleViewEntity::vehicle_name()
{
    return m_vehicle_name;
}
