#pragma once

#include "Transform.h"


class Bone
{
public:
	Transform transform;
	int	index;
	int	parentIndex;
	bool hasParent;
	std::string name;

public:
	Bone();
	~Bone() = default;

	void SetupBoneIndex(int p_index);
	void DrawJoint(); 
};
