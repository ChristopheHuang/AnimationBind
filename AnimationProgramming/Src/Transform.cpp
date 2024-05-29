#include "Transform.h"



Transform::Transform() : m_worldPosition(1.0f, 1.0f, 1.0f), m_localPosition(1.0f, 1.0f, 1.0f)
{
}

void Transform::NormalizeLocalRotation()
{
	if (!m_localRotation.IsNormalized())
	{
		m_localRotation.Normalize();
	}
}

void Transform::InitLocalTransform()
{
	m_localTransform = MathTool::Matrix4::Translation(m_localPosition) * m_localRotation.ToMatrix4();
}