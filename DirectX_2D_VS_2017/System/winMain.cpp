#include "stdafx.h"
#include "_Scenes/MainScene.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	
	Application* application = &Application::Get();
	GraphicRenderer* renderer = &GraphicRenderer::Get();

	if (FAILED(application->OnCreate(hInstance, nCmdShow))) return false;
	if (FAILED(renderer->OnCreateDeviceResource(application->GetHwnd()))) return false;

	MainScene* mainScene = new MainScene();
	if (FAILED(mainScene->Start())) { SAFE_DELETE(mainScene); return false; }

	MSG msg;
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			_Timer->UpdateTime();
			renderer->BeginDraw();
			{
				mainScene->Render();
			}
			renderer->EndDraw();
		}
	}

	SAFE_DELETE(mainScene);

	return (int)msg.wParam;
}
