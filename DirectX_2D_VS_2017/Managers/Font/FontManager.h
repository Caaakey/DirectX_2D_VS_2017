#pragma once
#include <map>

class FontManager
{
public:
	static IDWriteTextFormat* Default() { return Get()->m_Fonts.begin()->second; }
	static FontManager* Get() {
		static FontManager instance;
		return &instance;
	}

	FontManager();
	FontManager(FontManager const&) = delete;
	~FontManager();

	void operator=(FontManager const&) = delete;

private:
	std::map<std::wstring, IDWriteTextFormat*> m_Fonts;

public:
	HRESULT LoadFromFile(std::wstring name, std::wstring filePath);

};

#define _Font FontManager::Get()