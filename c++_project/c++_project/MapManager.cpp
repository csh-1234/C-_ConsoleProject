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
    // Village의 (9,9) 좌표의 포탈, 
    // 해당 포탈로 이동하면 나오는 맵: Dungeon_1
    // 포탈로 이동 후 플레이어의 스폰위치(9,10)
    p.CurrentMap = eMaps::Village;
    p.PortalPos.first = 22;
    p.PortalPos.second = 21;
    p.NextMap = eMaps::Dungeon_1;
    p.PlayerStartPos = make_pair(13, 12);
    PortalList.push_back(p);

    PortalInfo p2 = {};
    p2.CurrentMap = eMaps::Dungeon_1;
    p2.PortalPos.first = 11;
    p2.PortalPos.second = 13;
    p2.NextMap = eMaps::Village;
    p2.PlayerStartPos = make_pair(21, 23);
    PortalList.push_back(p2);

    PortalInfo p3 = {};
    p3.CurrentMap = eMaps::Dungeon_1;
    p3.PortalPos.first = 13;
    p3.PortalPos.second = 13;
    p3.NextMap = eMaps::BossRoom;
    p3.PlayerStartPos = make_pair(31, 33);
    PortalList.push_back(p3);

    PortalInfo p4 = {};
    p4.CurrentMap = eMaps::Dungeon_1;
    p4.PortalPos.first = 33;
    p4.PortalPos.second = 85;
    p4.NextMap = eMaps::BossRoom;
    p4.PlayerStartPos = make_pair(31, 33);
    PortalList.push_back(p4);

    PortalInfo p5 = {};
    p5.CurrentMap = eMaps::BossRoom;
    p5.PortalPos.first = 34;
    p5.PortalPos.second = 31;
    p5.NextMap = eMaps::Dungeon_1;
    p5.PlayerStartPos = make_pair(13, 12);
    PortalList.push_back(p5);
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
    case eMaps::Dungeon_2: return "Dungeon_2";
    case eMaps::BossRoom: return "BossRoom";
    case eMaps::test: return "test";
    case eMaps::None: return "None";
    default: return "Unknown";
    }
}

void MapManager::LoadMap(eMaps mapType)
{
    if (initializedMaps.find(mapType) == initializedMaps.end())
    {
        initializedMaps[mapType] = new Map(GetMapName(mapType));
        currentMap = mapType;
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

