#pragma once
#include <string>
#include <vector>

namespace Components
{
	class Object
	{
	public:
		Object(std::string name) : Name(name) { }
		virtual ~Object()
		{
			if (m_Component.size() != 0)
			{
				for (Component* c : m_Component)
				{
					c->Destroy();
					SAFE_DELETE(c);
				}
			}

			std::vector<Component*>().swap(m_Component);
		}

		void Start()
		{
			for (Component* c : m_Component)
				c->Start();
		}
		void Update()
		{
			for (Component* c : m_Component)
				c->Update();
		}
		void Render()
		{
			for (Component* c : m_Component)
				c->Render();
		}

		std::string Name;

	private:
		std::vector<Component*> m_Component;

	public:
		template <typename ComponentType>
		inline ComponentType* GetComponent()
		{
			ComponentType* pResult = nullptr;
			for (Component* c : m_Component)
			{
				pResult = dynamic_cast<ComponentType*>(c);
				if (pResult) break;
			}

			return pResult;
		}

		template <typename ComponentType>
		inline ComponentType* AddComponent()
		{
			ComponentType* pResult = GetComponent<ComponentType>();
			if (!pResult)
			{
				pResult = new ComponentType(this);
				m_Component.emplace_back(pResult);
			}

			return pResult;
		}

		template <typename ComponentType>
		inline void RemoveComponent()
		{
			ComponentType* pResult = GetComponent<ComponentType>();
			if (pResult)
			{
				m_Component.erase(pResult);
				delete pResult;
			}
		}
	};
}
