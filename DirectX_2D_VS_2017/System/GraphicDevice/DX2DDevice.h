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

	ID2D1SolidColorBrush* m_SolidBrush;

public:
	ID2D1HwndRenderTarget* RenderTarget() const { return m_RenderTarget; }
	ID2D1SolidColorBrush* GetBrush() const { return m_SolidBrush; }

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

#define _DXDevice DX2DDevice::Get()
#define _RenderTarget DX2DDevice::Get()->RenderTarget()
