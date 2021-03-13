#include "stdafx.h"
#include "SpriteModule.h"

SpriteModule* SpriteModule::CreateSprite(std::wstring filePath)
{
	SpriteModule* sprite = new SpriteModule();

	HRESULT hr = _Renderer.CreateBitmap(&sprite->m_Bitmap, filePath);
	if (FAILED(hr)) { SAFE_DELETE(sprite); }
	else
	{
		sprite->BitmapSize = sprite->m_Bitmap->GetSize();
	}

	return sprite;
}

SpriteModule::SpriteModule()
	: m_Bitmap(nullptr)
{
}

SpriteModule::~SpriteModule()
{
	SAFE_RELEASE(m_Bitmap);
}

void SpriteModule::Draw(float x, float y, float opacity)
{
	if (!m_Bitmap) return;

	D2D1_RECT_F UVPixel = D2D1::RectF(
		x,
		y,
		x + _Application.Width,
		y + _Application.Height
	);

	D2D1_RECT_F viewSize = D2D1::RectF(
		BitmapSize.width,
		BitmapSize.height
	);

	_Renderer.RenderTarget()->DrawBitmap(
		m_Bitmap,
		UVPixel,
		opacity,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		viewSize
	);
}
