#pragma once

namespace Components
{
	class Transform
	{
	public:
		Transform();
		~Transform();

	public:
		D2D_VECTOR_3F Position;
		D2D_VECTOR_3F Rotation;
		D2D_VECTOR_3F Scale;


	private:
		D2D1::Matrix3x2F m_WorldMatrix;

	public:
		const D2D1::Matrix3x2F* WorldMatrix() const { return &m_WorldMatrix; }
		D2D1::Matrix3x2F* WorldMatrix() { return &m_WorldMatrix; }
	};
}
