#pragma once

class InputManager
{
public:
	InputManager();
	static InputManager* Get()
	{
		static InputManager Instance;
		return &Instance;
	}

	bool GetKeyDown(int KeyCode);
	bool GetKey(int KeyCode);
	bool GetKeyUp(int KeyCode);
	bool ToggleDown(int KeyCode);

private:
	unsigned char m_KeyDown[256];
	unsigned char m_PrevKey[256];
};

#define _KeyCode InputManager::Get()