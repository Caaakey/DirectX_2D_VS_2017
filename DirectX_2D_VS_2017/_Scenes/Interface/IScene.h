#pragma once
#include "stdafx.h"

__interface IScene
{
	HRESULT Start();
	void Update();
	void Render();

	void OnGUI();
};
