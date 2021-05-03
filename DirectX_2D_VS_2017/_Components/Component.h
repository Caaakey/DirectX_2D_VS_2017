#pragma once

namespace Components
{
	class Component
	{
	public:
		Component() = delete;
		Component(const Component&) = delete;
		Component(Component&&) = delete;
		Component& operator=(const Component&) = delete;
		Component& operator=(Component&&) = delete;
		virtual ~Component() { Destroy(); }

		virtual void Start() {}
		virtual void Destroy() {}
		virtual void Update() {}
		virtual void Render() {}

	};
}