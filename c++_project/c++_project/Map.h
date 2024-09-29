#pragma once
#include <iostream>
using namespace std;
class Map
{
public:
	Map(const string inputName);
	~Map();

	int& at(int y, int x);
	int** GenerateMap(string mapName);
	string GetMapName();
	
private:
	int** mapInfo;
	string mapName;
};