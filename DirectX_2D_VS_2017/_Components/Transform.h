#pragma once

namespace Components
{
	class Transform
	{
	public:
		Transform();
		~Transform();

		void SetTransform();

	private:
		D2D_POINT_2F m_Position;
		float m_Rotation;
		D2D_POINT_2F m_Scale;

		D2D_POINT_2F m_Pivot;
		D2D_POINT_2F m_Size;
		D2D_POINT_2F m_LocalSize;

		D2D1::Matrix3x2F m_WorldMatrix;

	public:
		const D2D_POINT_2F GetPosition() const { return m_Position; }
		const float GetRotation() const { return m_Rotation; }
		const D2D_POINT_2F GetScale() const { return m_Scale; }
		const D2D_POINT_2F GetPivot() const { return m_Pivot; }
		const D2D_POINT_2F GetSize() const { return m_Size; }

		void SetPosition(float x, float y);
		void SetRotation(float angle);
		void SetScale(float x, float y);
		void SetPivot(float x, float y);
		void SetSize(float x, float y);
		void SetSize(UINT x, UINT y)
		{
			SetSize((float)x, (float)y);
		}

		const D2D1::Matrix3x2F WorldMatrix() const { return m_WorldMatrix; }
		D2D1::Matrix3x2F* WorldMatrixPtr() { return &m_WorldMatrix; }

	private:
		void UpdateMatrix();
		void UpdateLocalSize();
	};
}
