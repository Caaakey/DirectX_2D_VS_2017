#include "stdafx.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	
	Application* pApplication = Application::Get();
	DX2DDevice* pRenderer = DX2DDevice::Get();

	if (FAILED(pApplication->OnCreate(hInstance, nCmdShow))) return FALSE;
	if (FAILED(pRenderer->OnCreateDeviceResource(pApplication->GetHwnd()))) return FALSE;

	MainScene* pMainScene = new MainScene();
	if (FAILED(pMainScene->Start())) { SAFE_DELETE(pMainScene); return FALSE; }

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
			pMainScene->Update();

			pRenderer->BeginDraw();
			{
				pMainScene->Render();
				_Timer->DrawFrame();
			}
			pRenderer->EndDraw();
		}
	}

	SAFE_DELETE(pMainScene);
	return (int)msg.wParam;
}
