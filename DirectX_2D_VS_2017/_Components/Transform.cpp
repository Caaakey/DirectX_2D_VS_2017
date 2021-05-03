#include "stdafx.h"
#include "Transform.h"

namespace Components
{
	Transform::Transform()
		: m_WorldMatrix(D2D1::Matrix3x2F::Identity())
	{

	}

	Transform::~Transform()
	{
	}
}