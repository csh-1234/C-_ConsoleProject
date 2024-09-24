#pragma once
#include <vector>
#include <Windows.h>
#include <iostream>
namespace InputManager
{
	enum class eKeyState
	{				// ���ϰ�   �Էº�ȭ
		Down,		// 0x8000   0 -> 1
		Pressed,	// 0x8001   1 -> 1
		Up,			// 0x0001   1 -> 0
		None,		// 0x0000   0 -> 0
	};
	enum class eKeyCode
	{
		Q, W, E, R, T, Y, U, I, O, P,
		A, S, D, F, G, H, J, K, L,
		Z, X, C, V, B, N, M,
		Left, Right, Down, Up, Nothing,
	};

	class Input
	{
	public:
		struct Key
		{
			eKeyCode keyCode;
			eKeyState state;
			bool isPressed;
		};
		static void Initialize();
		static void Update();

		//static bool GetKeyDown(eKeyCode code) { return Keys[(UINT)code].state == eKeyState::Down; }
		//static bool GetKeyUp(eKeyCode code) { return Keys[(UINT)code].state == eKeyState::Up; }
		//static bool GetKey(eKeyCode code) { return Keys[(UINT)code].state == eKeyState::Pressed; }

	private:
		static std::vector<Key>Keys; // Ű���� Ű���� �����س��� ����
		static void allocateKeys();  // eKeyCode�� �ۼ��� Ű���� <vector>keys�� �Ҵ�
		static void updateKeys();	 // while�� ���鼭 Ű�� ���� ����
	};

}
