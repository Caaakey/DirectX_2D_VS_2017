#include "stdafx.h"
#include "GameObject.h"

namespace Components
{
	GameObject::GameObject(std::string name) : Object(name)
	{
		transform = new Transform();
	}

	GameObject::~GameObject()
	{
		SAFE_DELETE(transform);
	}

	void GameObject::Start()
	{
		//transform->SetPosition(640, 360);

		Object::Start();
	}
	void GameObject::Update()
	{
		if (_KeyCode->GetKey('A'))
		{
			auto rotation = _Camera->GetRotation();
			_Camera->SetRotation(rotation - 1.0f);
		}
		else if (_KeyCode->GetKey('D'))
		{
			auto rotation = _Camera->GetRotation();
			_Camera->SetRotation(rotation + 1.0f);
		}

		if (_KeyCode->GetKey('Q'))
		{
			auto scale = transform->GetScale();
			transform->SetScale(scale.x - 0.01f, scale.y - 0.01f);
		}
		else if (_KeyCode->GetKey('W'))
		{
			auto scale = transform->GetScale();
			transform->SetScale(scale.x + 0.01f, scale.y + 0.01f);
		}

		if (_KeyCode->GetKey(VK_LEFT))
		{
			auto position = transform->GetPosition();
			transform->SetPosition(position.x - 1.0f, position.y);

			printf("%f\n", transform->GetPosition().x);
		}
		else if (_KeyCode->GetKey(VK_RIGHT))
		{
			auto position = transform->GetPosition();
			transform->SetPosition(position.x + 1.0f, position.y);

			printf("%f\n", transform->GetPosition().x);
		}

		Object::Update();
	}
	void GameObject::Render()
	{
		auto position = transform->GetPosition();
		D2D1_RECT_F rect = D2D1::RectF(
			position.x,
			position.y,
			position.x + 100.0f,
			position.y + 100.0f);

		_RenderTarget->DrawRectangle(rect, _DXDevice->GetBrush());
		Object::Render();
	}
}
