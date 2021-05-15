#include "stdafx.h"
#include "FontManager.h"

FontManager::FontManager()
{
	IDWriteTextFormat* pTextFormat = nullptr;
	try {
		HThrow(
			_RenderDevice->CreateTextFormat(
				&pTextFormat,
				L"Arial"));

		m_Fonts.insert(std::make_pair(L"default", pTextFormat));
	}
	catch (...)
	{
		PostQuitMessage(0);
	}
}

FontManager::~FontManager()
{
}

HRESULT FontManager::LoadFromFile(std::wstring name, std::wstring filePath)
{
	if (!FileUtility::Exists(filePath))
		HResult(0x80070002);

	return S_OK;
}
