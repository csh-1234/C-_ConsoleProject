#pragma once
#include "Map.h"

class GameManager
{
public:
	static GameManager& getInstance() { static GameManager gm; return gm; }
	static void Initialize();
	static void Update();
private:
	GameManager() {};
	~GameManager() {};
	GameManager(const GameManager&) = delete;
	GameManager& operator=(const GameManager&) = delete;
};

