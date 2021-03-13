#include "stdafx.h"
#include "MainScene.h"

MainScene::MainScene()
	:m_Sprite(nullptr)
{
}

MainScene::~MainScene()
{
	SAFE_DELETE(m_Sprite);
}

HRESULT MainScene::Start()
{
	m_Sprite = SpriteModule::CreateSprite(L"../_Resources/Iceland.jpg");

	return S_OK;
}

void MainScene::Update()
{
}

void MainScene::Render()
{
	if (m_Sprite) m_Sprite->Draw(0, 0);
}

void MainScene::OnGUI()
{
}
