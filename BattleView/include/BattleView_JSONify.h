#pragma once

#include "BattleView_Entity.h"

class BattleViewJSONify
{
    int m_battleview_version;
    int m_battleview_mode;
    const char *m_server_name;
    const char *m_server_map;
    DynamicVectorClass<BattleViewEntity *> m_structures;
    DynamicVectorClass<BattleViewEntity *> m_players;
    DynamicVectorClass<BattleViewEntity *> m_vehicles;

public:
    BattleViewJSONify(
        int battleview_version,
        int battleview_mode,
        const char *server_name,
        const char *server_map,
        DynamicVectorClass<BattleViewEntity *> structures,
        DynamicVectorClass<BattleViewEntity *> players,
        DynamicVectorClass<BattleViewEntity *> vehicles);

    ~BattleViewJSONify();

    const char *to_json();

    StringClass entity_list_to_json_array(DynamicVectorClass<BattleViewEntity *> list);
};