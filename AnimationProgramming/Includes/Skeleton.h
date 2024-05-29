#pragma once

#include <vector>
#include "Bone.h"



class Skeleton
{
private:
	std::vector<Bone> m_bones;
	size_t m_currentKeyFrame;
	size_t m_keyCount;
	size_t m_boneCount;
	std::string m_animationName;

	float timeToUpdate;
	float timeSinceLastUpdate;

public:
	Skeleton();
	~Skeleton() = default;

	void PrintBones();
	int FindLongestString(std::string _option);
	void InitBones();
	void InitBonesTransform();
	void Update(float deltaTime);
	void UpdateAnimation();
	void BindAnimation(const std::string& p_file);
	void LerpAnimation();
	void Draw();
	void UpdateMesh();

	Bone& GetBonesByIndex(int p_index);
};
