#include "stdafx.h"
#include "InputManager.h"

InputManager::InputManager()
{
	ZeroMemory(m_KeyDown, sizeof m_KeyDown);
	ZeroMemory(m_PrevKey, sizeof m_PrevKey);
}

bool InputManager::GetKeyDown(int KeyCode)
{
	if (GetAsyncKeyState(KeyCode) & 0x8000) {
		if (!m_KeyDown[KeyCode]) {
			m_KeyDown[KeyCode] = 0x01;
			return true;
		}
	}
	else m_KeyDown[KeyCode] = 0;

	return false;
}

bool InputManager::GetKey(int KeyCode)
{
	if (GetAsyncKeyState(KeyCode) & 0x8000) {
		m_PrevKey[KeyCode] = 0x01;
		return true;
	}

	return false;
}

bool InputManager::GetKeyUp(int KeyCode)
{
	if (!GetKey(KeyCode)) {
		if (m_PrevKey[KeyCode] == 0x01) {
			m_PrevKey[KeyCode] = 0;
			return true;
		}
	}

	return false;
}

bool InputManager::ToggleDown(int KeyCode)
{
	if (GetKeyState(KeyCode) & 0x0001) return true;
	return false;
}
