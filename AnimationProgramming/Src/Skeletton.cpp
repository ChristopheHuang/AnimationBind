#include "Skeleton.h"
#include "Transform.h"
#include "../Engine.h"
#include <vector>
#include <iomanip>
#include <iostream>


Skeleton::Skeleton()
{
	timeSinceLastUpdate = 0.0f;
	timeToUpdate = 0.03333f;
}

int Skeleton::FindLongestString(std::string _option)
{
	std::string currentString, longestString;

	for (int i = 0; i < m_boneCount; i++) {
		if (_option == "index") {
			currentString = m_bones[i].index;
			if (currentString.size() > longestString.size()) {
				longestString = currentString;
			}
		}
		else if (_option == "name") {
			currentString = m_bones[i].name;
			if (currentString.size() > longestString.size()) {
				longestString = currentString;
			}
		}
		else if (_option == "parentIndex") {
			currentString = m_bones[i].parentIndex;
			if (currentString.size() > longestString.size()) {
				longestString = currentString;
			}
		}
		else if (_option == "parentName") {
			continue;
		}
	}
	return longestString.size();
}

void Skeleton::PrintBones()
{
	int longestIndex = FindLongestString("index");
	int longestName = FindLongestString("name");
	int longestParentIndex = FindLongestString("parentIndex");
	std::string index = "index", name = "name", parentIndex = "parent index";

	std::cout << std::setw(longestIndex + index.size() + 1) << std::left << index << std::setw(longestName + name.size()) << std::left << name << std::setw(longestParentIndex + parentIndex.size()) << std::left << parentIndex << "\n\n";
	for (int i = 0; i < m_boneCount; i++) {
		std::cout << std::setw(longestIndex + index.size()) << std::left << m_bones[i].index << " " << std::setw(longestName + name.size()) << std::left << m_bones[i].name << std::setw(longestParentIndex + parentIndex.size()) << m_bones[i].parentIndex << std::endl;
	}
}

void Skeleton::InitBones()
{
	m_boneCount = GetSkeletonBoneCount() - 7;		// remove 7 for the IK bones (Inverse Kinematic) because not needed.
	m_bones.reserve(m_boneCount);

	Bone bone;

	for (int i = 0; i < m_boneCount; i++)
	{
		bone.SetupBoneIndex(i);
		m_bones.push_back(bone);
		//std::cout << m_bones[i].index << " " << m_bones[i].name << "\t\t\t" << m_bones[i].parentIndex << std::endl;
	}
}

void Skeleton::InitBonesTransform()
{
	float xPos;
	float yPos;
	float zPos;

	float wValue;
	float xValue;
	float yValue;
	float zValue;

	for (int i = 0; i < m_boneCount; i++)
	{
		GetSkeletonBoneLocalBindTransform(m_bones[i].index, xPos, yPos, zPos, wValue, xValue, yValue, zValue);

		Transform* transform = &m_bones[i].transform;
		transform->m_localPosition = MathTool::Vector3(xPos, yPos, zPos);
		transform->m_localRotation = MathTool::Quaternion(xValue, yValue, zValue, wValue);
		transform->NormalizeLocalRotation();
		transform->InitLocalTransform();

		if (m_bones[i].parentIndex != -1)
		{
			transform->m_worldTransform = GetBonesByIndex(m_bones[i].parentIndex).transform.m_worldTransform * m_bones[i].transform.m_localTransform;
		}
		else
		{
			transform->m_worldTransform = m_bones[i].transform.m_localTransform;
		}

		transform->m_initialTransform = m_bones[i].transform.m_localTransform;
		transform->m_initialWorldTransform = m_bones[i].transform.m_worldTransform;
		transform->m_oldPosition = m_bones[i].transform.m_initalPosition;
		transform->m_oldRotation = m_bones[i].transform.m_initalRotation;
		transform->m_newPosition = m_bones[i].transform.m_initalPosition;
		transform->m_newRotation = m_bones[i].transform.m_initalRotation;
	}
}

void Skeleton::Update(float deltaTime)
{
	timeSinceLastUpdate += deltaTime;

	while (timeSinceLastUpdate >= timeToUpdate)
	{
		UpdateAnimation();
		m_currentKeyFrame++;
		timeSinceLastUpdate -= timeToUpdate;

		if (m_currentKeyFrame == m_keyCount)
			m_currentKeyFrame = 0;
	}
	LerpAnimation();
	UpdateMesh();
}

void Skeleton::UpdateAnimation()
{
	float xPos;
	float yPos;
	float zPos;

	float wValue;
	float xValue;
	float yValue;
	float zValue;

	MathTool::Vector3	 animPos;
	MathTool::Quaternion animRot;

	for (int i = 0; i < m_boneCount; i++)
	{
		GetAnimLocalBoneTransform(m_animationName.c_str(), m_bones[i].index, m_currentKeyFrame, xPos, yPos, zPos, wValue, xValue, yValue, zValue);

		animPos.x = xPos;
		animPos.y = yPos;
		animPos.z = zPos;

		animRot.SetXAxisValue(xValue);
		animRot.SetYAxisValue(yValue);
		animRot.SetZAxisValue(zValue);
		animRot.SetRealValue(wValue);

		if (!animRot.IsNormalized())
		{
			animRot.Normalize();
		}
		Transform* transform = &m_bones[i].transform;
		transform->m_oldPosition = m_bones[i].transform.m_newPosition;
		transform->m_oldRotation = m_bones[i].transform.m_newRotation;
		transform->m_newPosition = animPos;
		transform->m_newRotation = animRot;
	}
}

void Skeleton::BindAnimation(const std::string& p_file)
{
	m_currentKeyFrame = 0.0f;
	m_keyCount = GetAnimKeyCount(p_file.c_str());
	m_animationName = p_file;
	std::cout << "Key count : " << m_keyCount << std::endl;
}

void Skeleton::LerpAnimation()
{
	MathTool::Vector3		 position;
	MathTool::Quaternion	 rotation;

	float coefficient = timeSinceLastUpdate / timeToUpdate;

	for (int i = 0; i < m_bones.size(); i++)
	{
		position = MathTool::Vector3::Lerp(m_bones[i].transform.m_oldPosition, m_bones[i].transform.m_newPosition, coefficient);
		rotation = MathTool::Quaternion::Slerp(m_bones[i].transform.m_oldRotation, m_bones[i].transform.m_newRotation, coefficient);
		Transform* transform = &m_bones[i].transform;
		transform->m_localTransform = MathTool::Matrix4::Translation(position) * rotation.ToMatrix4();

		transform->m_localTransform = m_bones[i].transform.m_initialTransform * m_bones[i].transform.m_localTransform;

		if (m_bones[i].parentIndex != -1)
		{
			transform->m_worldTransform = GetBonesByIndex(m_bones[i].parentIndex).transform.m_worldTransform * m_bones[i].transform.m_localTransform;
		}
		else
		{
			transform->m_worldTransform = m_bones[i].transform.m_localTransform;
		}
	}
}

Bone& Skeleton::GetBonesByIndex(int p_index)
{
	for (int i = 0; i < m_bones.size(); i++)
	{
		if (m_bones[i].index == p_index)
			return m_bones[i];
	}
}

void Skeleton::Draw()
{
	for (int i = 0; i < m_boneCount; i++)
	{
		m_bones[i].DrawJoint();

		if (m_bones[i].parentIndex != -1)
		{
			DrawLine(m_bones[i].transform.m_worldTransform.GetColumn(3).x, m_bones[i].transform.m_worldTransform.GetColumn(3).y - 100, m_bones[i].transform.m_worldTransform.GetColumn(3).z, GetBonesByIndex(m_bones[i].parentIndex).transform.m_worldTransform.GetColumn(3).x, GetBonesByIndex(m_bones[i].parentIndex).transform.m_worldTransform.GetColumn(3).y - 100, GetBonesByIndex(m_bones[i].parentIndex).transform.m_worldTransform.GetColumn(3).z, 1, 0, 1);
		}
	}
}

void Skeleton::UpdateMesh()
{
	std::vector<float> matrices;

	for (int i = 0; i < m_bones.size(); i++)
	{
		MathTool::Matrix4 meshWorldMatrix = m_bones[i].transform.m_worldTransform * m_bones[i].transform.m_initialWorldTransform.Inverse();
		for (int j = 0; j < 16; j++)
		{
			matrices.push_back(meshWorldMatrix.ToArray()[j]);
		}
	}
	SetSkinningPose(matrices.data(), m_boneCount);
}