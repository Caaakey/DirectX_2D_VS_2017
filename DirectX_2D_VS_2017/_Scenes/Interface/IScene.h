#pragma once

__interface IScene
{
	HRESULT Start();
	void Update();
	void Render();

	void OnGUI();
};
