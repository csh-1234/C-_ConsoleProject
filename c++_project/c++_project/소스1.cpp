// getline 으로 읽어들이기
#include <fstream>
#include <iostream>
#include <string>
#include "Map.h"
#include "MapManager.h"
#include "Manager.h"
int main() 
{
	Manager& manager = Manager::getInstance();
	//manager.game.Initialize();
	//manager.input.Initialize();
	//manager.map.Initialize();
	manager.map.GetCurrentMap();
	manager.map.LoadMap(eMaps::test);
	manager.map.GetCurrentMap();
	
}