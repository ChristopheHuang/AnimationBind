#include "../Includes/Bone.h"
#include "../Engine.h"


Bone::Bone() : index(0), parentIndex(0), hasParent(false) {}

void Bone::SetupBoneIndex(int p_index)
{
	index = p_index;
	parentIndex = GetSkeletonBoneParentIndex(index);
	hasParent = parentIndex != -1;
	name = GetSkeletonBoneName(p_index);
}

void Bone::DrawJoint()
{
	MathTool::Vector4 position(transform.m_worldTransform.GetColumn(3));

	DrawLine(position.x - 1, position.y - 100, position.z, position.x + 1, position.y - 100, position.z, 1, 0, 0);
	DrawLine(position.x, position.y - 100, position.z - 1, position.x, position.y - 100, position.z + 1, 1, 0, 0);
}