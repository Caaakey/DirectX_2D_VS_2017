#pragma once

using namespace Components;
class MainScene : public IScene
{
public:
	MainScene();
	~MainScene();

private:

public:
	// IScene을(를) 통해 상속됨
	virtual HRESULT Start() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void OnGUI() override;
};

