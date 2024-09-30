#pragma once
#include <Windows.h>

class TimeManager
{
public:
	static void Initalize();
	static void Update();

	static float deltaTime() { return DeltaTimeValue; }

private:
	static LARGE_INTEGER CpuFrequency;
	static LARGE_INTEGER PrevFrequency;
	static LARGE_INTEGER CurrentFrequency;
	static float DeltaTimeValue;

};

