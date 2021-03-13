#pragma once

class SpriteModule
{
public:
	static SpriteModule* CreateSprite(std::wstring filePath);

	SpriteModule();
	~SpriteModule();

public:
	D2D1_SIZE_F BitmapSize;

private:
	ID2D1Bitmap* m_Bitmap;

public:
	void Draw(float x, float y, float opacity = 1.0f);

};

