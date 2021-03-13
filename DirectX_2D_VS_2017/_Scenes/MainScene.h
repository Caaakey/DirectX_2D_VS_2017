#pragma once
#include "_Components/Sprite/SpriteModule.h"

class MainScene : public IScene
{
public:
	MainScene();
	~MainScene();

private:
	SpriteModule* m_Sprite;

public:
	// IScene을(를) 통해 상속됨
	virtual HRESULT Start() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void OnGUI() override;
};

