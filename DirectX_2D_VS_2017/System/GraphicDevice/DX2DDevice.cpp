#include "stdafx.h"
#include "DX2DDevice.h"

DX2DDevice::DX2DDevice()
	: m_D2DFactory(nullptr), m_DWriteFactory(nullptr), m_WICFactory(nullptr), m_RenderTarget(nullptr)
{
}

DX2DDevice::~DX2DDevice()
{
	SAFE_RELEASE(m_D2DFactory);
	SAFE_RELEASE(m_DWriteFactory);
	SAFE_RELEASE(m_WICFactory);
	SAFE_RELEASE(m_RenderTarget);

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

	return S_OK;
}

void DX2DDevice::OnResize(UINT width, UINT height)
{
	if (m_RenderTarget) m_RenderTarget->Resize(D2D1::SizeU(width, height));
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
	_Out_ ID2D1Bitmap** pBitmap,
	_In_ std::wstring filePath, _In_ float width, _In_ float height, 
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
		{
			HThrow((HRESULT)0x80070002);
		}

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
			pBitmap
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
