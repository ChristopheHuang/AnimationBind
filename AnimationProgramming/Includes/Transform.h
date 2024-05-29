#pragma once

#include "../MathTool.h"

class Transform
{
public:
	MathTool::Matrix4 m_worldTransform;
	MathTool::Matrix4 m_localTransform;
	MathTool::Matrix4 m_initialTransform;
	MathTool::Matrix4 m_initialWorldTransform;

	MathTool::Quaternion m_worldRotation;
	MathTool::Quaternion m_localRotation;
	MathTool::Quaternion m_initalRotation;
	MathTool::Quaternion m_oldRotation;
	MathTool::Quaternion m_newRotation;

	MathTool::Vector3 m_worldPosition;
	MathTool::Vector3 m_localPosition;
	MathTool::Vector3 m_initalPosition;
	MathTool::Vector3 m_oldPosition;
	MathTool::Vector3 m_newPosition;

public:
	Transform();
	~Transform() = default;

	void NormalizeLocalRotation();
	void InitLocalTransform();
};

