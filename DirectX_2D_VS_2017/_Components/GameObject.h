#pragma once

namespace Components
{
	class Transform;
	class GameObject : public Object
	{
	public:
		GameObject(std::string name);
		~GameObject();
		
	public:
		Transform* transform;

	};
}
