#include "stdafx.h"
#include "Transform.h"

namespace Components
{
	Transform::Transform()
		: m_Position({ 0, }), m_Rotation(0), m_Scale({ 1, 1 }),
		m_Pivot({ 0.5f, 0.5f }), m_Size({ 100.0f, 100.0f }),
		  m_WorldMatrix(D2D1::Matrix3x2F::Identity())
	{
		UpdateLocalSize();
	}
	Transform::~Transform()
	{
	}

	void Transform::SetTransform()
	{
		auto world = m_WorldMatrix * _Camera->WorldMatrix();
		_RenderTarget->SetTransform(world);
	}

	void Transform::SetPosition(float x, float y)
	{
		m_Position = { x, y };

		UpdateMatrix();
	}
	void Transform::SetRotation(float angle)
	{
		m_Rotation = angle;

		UpdateMatrix();
	}
	void Transform::SetScale(float x, float y)
	{
		m_Scale = { x, y };

		UpdateMatrix();
	}

	void Transform::SetPivot(float x, float y)
	{
		m_Pivot = { x, y };

		UpdateLocalSize();
	}

	void Transform::SetSize(float x, float y)
	{
		m_Size = { x, y };

		UpdateLocalSize();
	}

	void Transform::UpdateMatrix()
	{
		m_WorldMatrix =
			D2D1::Matrix3x2F::Scale({ m_Scale.x, m_Scale.y }, m_LocalSize) *
			D2D1::Matrix3x2F::Rotation(m_Rotation, m_LocalSize) *
			D2D1::Matrix3x2F::Translation({ m_Position.x, m_Position.y });
	}
	void Transform::UpdateLocalSize()
	{
		m_LocalSize = { m_Size.x * m_Pivot.x, m_Size.y * m_Pivot.y };
	}
}