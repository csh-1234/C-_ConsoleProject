#include "InputManager.h"
#include <iostream>

std::vector<InputManager::Key> InputManager::Keys = {};

int	UseKeys[(int)eKeyCode::Nothing] =
{
	'Q','W','E','R','T','Y','U','I','O','P',
	'A','S','D','F','G','H','J','K','L',
	'Z','X','C','V','B','N','M',
	VK_LEFT, VK_RIGHT, VK_DOWN, VK_UP,
};

void InputManager::Initialize()
{
	allocateKeys();
}
void InputManager::Update()
{
	updateKeys();
}
void InputManager::allocateKeys()
{
	for (int i = 0; i < (int)eKeyCode::Nothing; i++)
	{
		Key key = {};
		key.isPressed = false;
		key.state = eKeyState::None;
		key.keyCode = (eKeyCode)i;

		Keys.push_back(key);
	}
}
void InputManager::updateKeys()
{
	for (auto& key : Keys)
	{
		
		if (GetAsyncKeyState(UseKeys[(int)key.keyCode]) & 0x8000)
		{
			if (key.isPressed == true)
			{

				std::cout << (int)key.keyCode << std::endl;
				key.state = eKeyState::Pressed;
			}
			else
			{
				key.state = eKeyState::Down;
			}
			key.isPressed = true;
		}
		else
		{
			if (key.isPressed == false)
			{
				key.state = eKeyState::Up;
			}
			else
			{
				key.state = eKeyState::None;
			}
			key.isPressed = false;
		}
	}
}


