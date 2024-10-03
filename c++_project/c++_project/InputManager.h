#pragma once
#include <vector>
#include <Windows.h>
#include <iostream>

enum class eKeyState
{				// 리턴값   입력변화
	Down,		// 0x8000   0 -> 1
	Pressed,	// 0x8001   1 -> 1
	Up,			// 0x0001   1 -> 0
	None,		// 0x0000   0 -> 0
};
enum class eKeyCode
{
	Num0, Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9,
	Q, W, E, R, T, Y, U, I, O, P,
	A, S, D, F, G, H, J, K, L,
	Z, X, C, V, B, N, M,
	Left, Right, Down, Up, Space, Nothing,
};

class InputManager
{
public:
	static InputManager& getInstance() { static InputManager input; return input; }

	struct Key
		{
			eKeyCode keyCode;
			eKeyState state;
			bool isPressed;
		};

	static std::vector<Key>Keys; // 키보드 키들을 맵핑해놓을 벡터
	static void allocateKeys();  // eKeyCode에 작성한 키들을 <vector>keys에 당
	static void updateKeys();	 // while을 돌면서 키의 변경 감지

	static void Initialize();
	static void Update();

	static bool GetKeyDown(eKeyCode code) { return Keys[(int)code].state == eKeyState::Down; }
	static bool GetKeyUp(eKeyCode code) { return Keys[(int)code].state == eKeyState::Up; }
	static bool GetKey(eKeyCode code) { return Keys[(int)code].state == eKeyState::Pressed; }

private:
	InputManager() {};
	~InputManager() {};
	InputManager(const InputManager&) = delete;
	InputManager& operator=(const InputManager&) = delete;
};


