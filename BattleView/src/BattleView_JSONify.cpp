#include "general.h"
#include "include/BattleView_JSONify.h"

BattleViewJSONify::BattleViewJSONify(int battleview_version, int battleview_mode, const char *server_name, const char *server_map,
                                     DynamicVectorClass<BattleViewEntity *> structures, DynamicVectorClass<BattleViewEntity *> players,
                                     DynamicVectorClass<BattleViewEntity *> vehicles)
{
    m_battleview_version = battleview_version;
    m_battleview_mode = battleview_mode;
    m_server_name = server_name;
    m_server_map = server_map;
    m_structures = structures;
    m_players = players;
    m_vehicles = vehicles;
}

BattleViewJSONify::~BattleViewJSONify()
{
}

const char *BattleViewJSONify::to_json()
{
    StringClass buffer = "";
    buffer += "{";
    buffer += "\"data\":";
    buffer += "{";
    buffer += "\"battleview_version\":";
    buffer += buffer.getFormattedString("%i,", m_battleview_version);
    buffer += "\"battleview_mode\":";
    buffer += buffer.getFormattedString("%i,", m_battleview_mode);
    buffer += "\"server_name\":";
    buffer += buffer.getFormattedString("\"%s\",", m_server_name);
    buffer += "\"server_map\":";
    buffer += buffer.getFormattedString("\"%s\",", m_server_map);

    buffer += "\"structures\":";
    buffer += BattleViewJSONify::entity_list_to_json_array(m_structures);
    buffer += ",";
    buffer += "\"players\":";
    buffer += BattleViewJSONify::entity_list_to_json_array(m_players);
    buffer += ",";
    buffer += "\"vehicles\":";
    buffer += BattleViewJSONify::entity_list_to_json_array(m_vehicles);

    buffer += "}";
    buffer += "}";

    return buffer;
}

StringClass BattleViewJSONify::entity_list_to_json_array(DynamicVectorClass<BattleViewEntity *> list)
{
    StringClass buffer;

    buffer += "[";
    for (int i = 0; i < list.Count(); i++)
    {
        BattleViewEntity *entity = list[i];

        buffer += "{";

        buffer += "\"id\":";
        buffer += buffer.getFormattedString("%i,", entity->id());
        buffer += "\"team\":";
        buffer += buffer.getFormattedString("%i,", entity->team());
        buffer += "\"name\":";
        if (entity->name())
            buffer += buffer.getFormattedString("\"%s\",", entity->name());
        if (!entity->name())
            buffer += "null,";
        buffer += "\"position\":";
        buffer += buffer.getFormattedString("[%.2f,%.2f,%.2f],", entity->position().X, entity->position().Y, entity->position().Z);
        buffer += "\"type\":";
        buffer += buffer.getFormattedString("\"%s\",", entity->type());
        buffer += "\"health\":";
        buffer += buffer.getFormattedString("%.2f,", entity->health());
        buffer += "\"icon\":";
        buffer += buffer.getFormattedString("\"%s\",", entity->icon());
        buffer += "\"character_name\":";
        if (entity->character_name())
            buffer += buffer.getFormattedString("\"%s\",", entity->character_name()); // nullible
        if (!entity->character_name())
            buffer += "null,";
        buffer += "\"vehicle_name\":";
        if (entity->vehicle_name())
            buffer += buffer.getFormattedString("\"%s\"", entity->vehicle_name()); // nullible
        if (!entity->vehicle_name())
            buffer += "null";

        buffer += buffer.getFormattedString("}%s", i == list.Count() - 1 ? "" : ",");
    }
    buffer += "]";

    return buffer;
}
