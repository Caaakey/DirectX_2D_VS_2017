#pragma once
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>

#pragma comment(lib, "D2D1.lib")
#pragma comment(lib, "DWrite.lib")

class DX2DDevice
{
public:
	static DX2DDevice* Get() {
		static DX2DDevice instance;
		return &instance;
	}

	DX2DDevice();
	DX2DDevice(DX2DDevice const&) = delete;
	~DX2DDevice();
	void operator=(DX2DDevice const&) = delete;

private:
	ID2D1Factory*			m_D2DFactory;
	IDWriteFactory*			m_DWriteFactory;
	IWICImagingFactory*		m_WICFactory;
	ID2D1HwndRenderTarget*	m_RenderTarget;

	ID2D1SolidColorBrush*	m_SolidBrush;
	D2D1_ANTIALIAS_MODE		m_AntialiasMode;

public:
	ID2D1HwndRenderTarget* RenderTarget() const { return m_RenderTarget; }
	ID2D1SolidColorBrush* GetBrush() const { return m_SolidBrush; }

public:
	HRESULT OnCreateDeviceResource(HWND hWnd);
	void OnResize(UINT width, UINT height);

	void BeginDraw();
	void EndDraw();

	HRESULT CreateBitmap(
		_Out_ ID2D1Bitmap** ppBitmap,
		_In_ std::wstring filePath,
		_In_ float alphaThresholdPercent = 0.0f,
		_In_ WICBitmapDitherType dither = WICBitmapDitherTypeNone,
		_In_ WICBitmapPaletteType palette = WICBitmapPaletteTypeCustom);

	HRESULT CreateTextFormat(
		_Out_ IDWriteTextFormat** ppWriteTextFormat,
		_In_ std::wstring fontName,
		_In_ DWRITE_FONT_WEIGHT weight = DWRITE_FONT_WEIGHT_NORMAL,
		_In_ DWRITE_FONT_STYLE style = DWRITE_FONT_STYLE_NORMAL,
		_In_ DWRITE_FONT_STRETCH stretch = DWRITE_FONT_STRETCH_NORMAL,
		_In_ float fontSize = 14.0f);

};

#define _RenderDevice DX2DDevice::Get()
#define _RenderTarget DX2DDevice::Get()->RenderTarget()