#include "MapManager.h"

std::vector<MapManager::PortalInfo> MapManager::PortalList = {};

MapManager::MapManager(): currentMap(eMaps::None){}

MapManager::~MapManager()
{
    for (auto& maps : initializedMaps) 
    {
        delete maps.second;
        maps.second = nullptr;
    }
    initializedMaps.clear();
}

void MapManager::Initialize()
{
    PortalInfo p = {};
    p.CurrentMap = eMaps::Village;
    p.PortalPos.first = 2;
    p.PortalPos.second = 2;
    p.NextMap = eMaps::Dungeon_1;
    p.PlayerStartPos = make_pair(2, 3);
    PortalList.push_back(p);

    PortalInfo p2 = {};
    p2.CurrentMap = eMaps::Dungeon_1;
    p2.PortalPos.first = 2;
    p2.PortalPos.second = 2;
    p2.NextMap = eMaps::Village;
    p2.PlayerStartPos = make_pair(2, 1);
    PortalList.push_back(p2);

}

void MapManager::Update()
{
}

Map* MapManager::GetCurrentMap()
{
    map<eMaps, Map*>::iterator it = initializedMaps.find(currentMap);
    if (it != initializedMaps.end())
    {
        return it->second;
    }
    else
    {
        return nullptr;
    }
}

eMaps MapManager::GetcurrenteMap()
{
    map<eMaps, Map*>::iterator it = initializedMaps.find(currentMap);
    if (it != initializedMaps.end())
    {
        return it->first;
    }
    else
    {
        return eMaps::None;
    }
}

string MapManager::GetMapName(eMaps map)
{
    switch (map)
    {
    case eMaps::Village: return "Village";
    case eMaps::Dungeon_1: return "Dungeon_1";
    case eMaps::BossRoom: return "BossRoom";
    case eMaps::test: return "test";
    case eMaps::None: return "None";
    default: return "Unknown";
    }
}

void MapManager::LoadMap(eMaps mapType)
{
    if (currentMap != mapType)
    {
        if (initializedMaps.find(mapType) == initializedMaps.end())
        {
            initializedMaps[mapType] = new Map(GetMapName(mapType));
            currentMap = mapType;
        }
    }
}

void MapManager::UnloadMap(eMaps mapType)
{
    map<eMaps, Map*>::iterator it = initializedMaps.find(mapType);
    if (it != initializedMaps.end()) {
        delete it->second;
        initializedMaps.erase(it);
    }
}

