#include "stdafx.h"
#include "DX2DDevice.h"

DX2DDevice::DX2DDevice()
	: m_D2DFactory(nullptr), m_DWriteFactory(nullptr), m_WICFactory(nullptr), m_RenderTarget(nullptr),
	m_AntialiasMode(D2D1_ANTIALIAS_MODE_PER_PRIMITIVE),
	m_SolidBrush(nullptr)
{
}

DX2DDevice::~DX2DDevice()
{
	SAFE_RELEASE(m_SolidBrush);
	SAFE_RELEASE(m_RenderTarget);
	SAFE_RELEASE(m_WICFactory);
	SAFE_RELEASE(m_DWriteFactory);
	SAFE_RELEASE(m_D2DFactory);

	CoUninitialize();
}

HRESULT DX2DDevice::OnCreateDeviceResource(HWND hWnd)
{
	RECT rect;
	GetClientRect(hWnd, &rect);

	D2D1_SIZE_U size = D2D1::SizeU(rect.right - rect.left, rect.bottom - rect.top);
	HResult(D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, &m_D2DFactory));

	HResult(
		DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(m_DWriteFactory),
			reinterpret_cast<IUnknown**>(&m_DWriteFactory)));

	CoInitialize(nullptr);
	HResult(CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC, IID_PPV_ARGS(&m_WICFactory)));

	HResult(
		m_D2DFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(hWnd, size),
			&m_RenderTarget));

	m_RenderTarget->SetAntialiasMode(m_AntialiasMode);

	HResult(
		m_RenderTarget->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF::Black),
			&m_SolidBrush));

	return S_OK;
}

void DX2DDevice::OnResize(UINT width, UINT height)
{
	if (m_RenderTarget) {
		m_RenderTarget->Resize(D2D1::SizeU(width, height));
		_Application->Width = width;
		_Application->Height = height;
	}
}

void DX2DDevice::BeginDraw()
{
	m_RenderTarget->BeginDraw();
	m_RenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::DarkGray));
}

void DX2DDevice::EndDraw()
{
	m_RenderTarget->EndDraw();
}

HRESULT DX2DDevice::CreateBitmap(
	_Out_ ID2D1Bitmap** ppBitmap,
	_In_ std::wstring filePath,
	_In_ float alphaThresholdPercent,
	_In_ WICBitmapDitherType dither,
	_In_ WICBitmapPaletteType palette)
{
	IWICFormatConverter* pWICConverter = nullptr;
	IWICBitmapFrameDecode* pWICFrameDecode = nullptr;
	IWICBitmapDecoder* pWICDecoder = nullptr;

	try
	{
		std::string convertStr = StringUtility::ConvertString(filePath);
		if (!FileUtility::Exists(convertStr))
			HThrow((HRESULT)0x80070002);

		HThrow(m_WICFactory->CreateDecoderFromFilename(
			filePath.c_str(),
			nullptr,
			GENERIC_READ,
			WICDecodeMetadataCacheOnDemand,
			&pWICDecoder));

		HThrow(m_WICFactory->CreateFormatConverter(&pWICConverter));
		HThrow(pWICDecoder->GetFrame(0, &pWICFrameDecode));
		HThrow(pWICConverter->Initialize(
			pWICFrameDecode,
			GUID_WICPixelFormat32bppPRGBA,
			dither,
			nullptr,
			alphaThresholdPercent,
			palette
		));

		HThrow(m_RenderTarget->CreateBitmapFromWicBitmap(
			pWICConverter,
			nullptr,
			ppBitmap
		));
	}
	catch (const HRESULT hr)
	{
		SAFE_RELEASE(pWICConverter);
		SAFE_RELEASE(pWICDecoder);
		SAFE_RELEASE(pWICFrameDecode);

		return hr;
	}
	
	SAFE_RELEASE(pWICConverter);
	SAFE_RELEASE(pWICDecoder);
	SAFE_RELEASE(pWICFrameDecode);

	return S_OK;
}

HRESULT DX2DDevice::CreateTextFormat(
	_Out_ IDWriteTextFormat** ppWriteTextFormat,
	_In_ std::wstring fontName,
	_In_ DWRITE_FONT_WEIGHT weight,
	_In_ DWRITE_FONT_STYLE style,
	_In_ DWRITE_FONT_STRETCH stretch,
	_In_ float fontSize)
{
	HResult(m_DWriteFactory->CreateTextFormat(
		fontName.c_str(),
		nullptr,
		weight, style, stretch,
		fontSize,
		L"",
		ppWriteTextFormat));

	return S_OK;
}
