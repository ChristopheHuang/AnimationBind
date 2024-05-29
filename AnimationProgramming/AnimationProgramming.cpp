// AnimationProgramming.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Engine.h"
#include "Simulation.h"
#include <iostream>
#include <unordered_map>
#include <Windows.h>

class CSimulation : public ISimulation
{
	Skeleton skeleton;

	virtual void Init() override;

	virtual void Update(float frameTime) override;

	void InputEvent();

	std::unordered_map<char, bool> m_keyPressedEvents;
	std::unordered_map<char, bool> m_keyReleasedEvents;
	std::unordered_map<char, bool> m_keyStates;

	bool play = true;
};

void CSimulation::Init()
{
	skeleton.InitBones();
	skeleton.InitBonesTransform();
	skeleton.PrintBones();
	skeleton.BindAnimation("ThirdPersonRun.anim");
}

void CSimulation::Update(float frameTime)
{
	DrawLine(0, 0, 0, 100, 0, 0, 1, 0, 0); // X axis
	DrawLine(0, 0, 0, 0, 100, 0, 0, 1, 0); // Y axis
	DrawLine(0, 0, 0, 0, 0, 100, 0, 0, 1); // Z axis

	if (play) {
		skeleton.Update(frameTime);
	}
	skeleton.Draw();
	InputEvent();
}

void CSimulation::InputEvent()
{
	m_keyPressedEvents.clear();
	m_keyReleasedEvents.clear();

	for (uint8_t i = 0; i < 255; ++i) {
		bool isKeyDown = GetKeyState(static_cast<int>(i)) & 0x8000; // Check if high-order bit is set to 1 (1 << 15), Equivalent is to check if value is negative

		m_keyPressedEvents[i] = isKeyDown && !m_keyStates[i];
		m_keyReleasedEvents[i] = !isKeyDown && m_keyStates[i];

		m_keyStates[i] = isKeyDown;
	}

	if (m_keyPressedEvents['1']) {
		skeleton.BindAnimation("ThirdPersonRun.anim");
	}
	if (m_keyPressedEvents['2']) {
		skeleton.BindAnimation("ThirdPersonWalk.anim");
	}
	if (m_keyPressedEvents['3']) {
		play = !play;
	}
}


int main()
{
	CSimulation simulation;
	Run(&simulation, 1400, 800);

    return 0;
}

