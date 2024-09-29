#pragma once
#include "MapManager.h"
#include "Map.h"
#include <map>
#include <vector>

enum class eMaps
{
	Village,
	Dungeon_1,
	BossRoom,
	test,
	None,	// 항상 맨끝에 둘 것.(개수 파악용)
};

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


