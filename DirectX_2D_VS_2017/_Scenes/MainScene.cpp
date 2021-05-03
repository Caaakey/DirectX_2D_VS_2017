#include "stdafx.h"
#include "MainScene.h"

MainScene::MainScene()
	: m_Sprite(nullptr), m_Pawn(nullptr)
{
}

MainScene::~MainScene()
{
	SAFE_DELETE(m_Sprite);
	SAFE_DELETE(m_Pawn);
}

HRESULT MainScene::Start()
{
	//m_Sprite = SpriteModule::CreateSprite(L"../_Resources/Iceland1.jpg");
	m_Pawn = new GameObject("Pawn");
	m_Pawn->Start();

	return S_OK;
}

void MainScene::Update()
{
	if (m_Pawn) m_Pawn->Update();
}

void MainScene::Render()
{
	if (m_Pawn) {
		m_Pawn->transform->SetTransform();
		m_Pawn->Render();
	}
	//if (m_Sprite) m_Sprite->Draw(0, 0);
}

void MainScene::OnGUI()
{
}
