#pragma once

namespace Components
{
	class Transform;
	class GameObject : public Object
	{
	public:
		GameObject(std::string name);
		~GameObject();
		
		void Start();
		void Update();
		void Render();

	public:
		Transform* transform;

	};
}
