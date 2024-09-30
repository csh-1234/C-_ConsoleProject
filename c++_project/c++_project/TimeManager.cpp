#include "TimeManager.h"
#include<Windows.h>

LARGE_INTEGER TimeManager::CpuFrequency = {};
LARGE_INTEGER TimeManager::PrevFrequency = {};
LARGE_INTEGER TimeManager::CurrentFrequency = {};
float TimeManager::DeltaTimeValue = 0.0f;

void TimeManager::Initalize()
{
	// 실제 클럭수
	QueryPerformanceFrequency(&CpuFrequency);
	// 프로그램 실행시 클럭수(누적)
	QueryPerformanceCounter(&CpuFrequency);
}

void TimeManager::Update()
{
	// 클럭 측정 시작
	QueryPerformanceCounter(&CurrentFrequency);

	float differenceFrequency
		= static_cast<float>(CurrentFrequency.QuadPart - PrevFrequency.QuadPart); // 최근 클럭 - 이전 클럭
	DeltaTimeValue = differenceFrequency / static_cast<float>(CpuFrequency.QuadPart); // deltatime = 한 클럭당 횟수 / 기본클럭수
	PrevFrequency.QuadPart = CurrentFrequency.QuadPart; // 한 사이클이 돌았으므로 이전 클럭을 최신화
}  
