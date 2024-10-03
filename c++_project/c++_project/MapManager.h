#pragma once
#include "MapManager.h"
#include "Map.h"
#include <map>
#include <vector>
#include "Enums.h"


class MapManager
{
public:
	struct PortalInfo
	{
		eMaps CurrentMap;
		pair<int, int> PortalPos;
		eMaps NextMap;
		pair<int, int> PlayerStartPos;
	};

	static MapManager& getInstance() { static MapManager map; return map; }
	static void Initialize();
	static void Update();

	static vector<PortalInfo> PortalList;

	Map* GetCurrentMap();
	eMaps GetcurrenteMap();
	string GetMapName(eMaps map);
	
	void LoadMap(eMaps mapType);
	void UnloadMap(eMaps mapType);

private:
	MapManager();
	~MapManager();
	MapManager(const MapManager&) = delete;
	MapManager& operator=(const MapManager&) = delete;

	std::map<eMaps, Map*> initializedMaps; 
	eMaps currentMap;
};


