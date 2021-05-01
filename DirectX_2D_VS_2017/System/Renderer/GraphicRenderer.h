#pragma once
#include <d2d1.h>
#include <dwrite.h>
#include <wincodec.h>

#pragma comment(lib, "D2D1.lib")
#pragma comment(lib, "DWrite.lib")

class GraphicRenderer
{
public:
	static GraphicRenderer& Get() {
		static GraphicRenderer instance;
		return instance;
	}

	GraphicRenderer();
	GraphicRenderer(GraphicRenderer const&) = delete;
	~GraphicRenderer();
	void operator=(GraphicRenderer const&) = delete;

private:
	ID2D1Factory*			m_D2DFactory;
	IDWriteFactory*			m_DWriteFactory;
	IWICImagingFactory*		m_WICFactory;
	ID2D1HwndRenderTarget*	m_RenderTarget;

public:
	ID2D1HwndRenderTarget* RenderTarget() const { return m_RenderTarget; }

public:
	HRESULT OnCreateDeviceResource(HWND hWnd);
	void OnResize(UINT width, UINT height);

	void BeginDraw();
	void EndDraw();

	HRESULT CreateBitmap(
		_Out_ ID2D1Bitmap** pBitmap,
		_In_ std::wstring filePath, _In_ float width = 1.0f, _In_ float height = 1.0f,
		_In_ float alphaThresholdPercent = 0.0f,
		_In_ WICBitmapDitherType diter = WICBitmapDitherTypeNone,
		_In_ WICBitmapPaletteType palette = WICBitmapPaletteTypeCustom);
};

#define _Renderer GraphicRenderer::Get()
