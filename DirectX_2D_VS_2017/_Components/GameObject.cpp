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
}
