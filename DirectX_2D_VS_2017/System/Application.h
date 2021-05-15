#pragma once

class Application
{
public:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	static Application* Get() {
		static Application instance;
		return &instance;
	}

	Application();
	Application(Application const&) = delete;
	~Application();
	void operator=(Application const&) = delete;

	const LPCWSTR ApplicationName = L"DirectX2D FrameWork";
	UINT Width;
	UINT Height;

private:
	HWND m_hWnd;
	HINSTANCE m_hInstance;

public:
	float AspectRatio() const { return (float)Width / Height; }
	HWND GetHwnd() const { return m_hWnd; }
	HINSTANCE GetInstance() const { return m_hInstance; }

public:
	HRESULT OnCreate(HINSTANCE hInstance, int CmdShow);
};

#define _Application Application::Get()