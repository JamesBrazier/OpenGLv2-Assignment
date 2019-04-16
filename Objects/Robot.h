// header file for the Robot class
// Author: jbr 185

#pragma once

#include "Objects.h"

namespace Project
{
	// the base class for all the robots, with all the drawing functions
	class Robot : public GLobject, public GLanimated
	{
	protected:

		float headSpin = 0, headTilt = 0; // the tilt and spin of the head
		float bodyTilt = 0; // the tilt of the body
		float LshoulderRotation = 0, LarmRotation = 0, LarmLift = 0, LwristRotation = 0, LforearmLift = 0, LhandLift = 0; // all left arm movements
		float RshoulderRotation = 0, RarmRotation = 0, RarmLift = 0, RwristRotation = 0, RforearmLift = 0, RhandLift = 0; // right arm
		float LlegLift = 0, LlegRotation = 0, LlowLegLift = 0, LfootLift = 0; // left leg
		float RlegLift = 0, RlegRotation = 0, RlowLegLift = 0, RfootLift = 0; // left arm

		void drawTorso(float x, float y, float z);

		void drawHead(float x, float y, float z, float rotation, float lookUp);

		void drawArm(float height, float offset, float shoulderRotation, float armRotation,
					 float armLift, float wristRotation, float forearmLift, float handLift, int sideMod);

		void drawLeg(float height, float offset, float legLift, float legRotation,
					 float lowLegLift, float footLift, int sideMod);

	public:

		Robot(float x, float y, float z, float orientation);

		void display(float shadowMatrix[16]) override;

		virtual void updateAnimation(void) = 0;

	};

	class Guard1 : public Robot
	{
	public:

		using Robot::Robot;

		void updateAnimation(void) override;

		using Robot::display;

	};

	// the left guard
	class Guard2 : public Robot
	{
	public:

		using Robot::Robot;

		void updateAnimation(void) override;

		using Robot::display;

	};

	// the cannon observer
	class Scout1 : public Robot
	{
	public:

		using Robot::Robot;

		void updateAnimation(void) override;

		using Robot::display;

	};

	// the roamer
	class Scout2 : public Robot
	{
	public:

		using Robot::Robot;

		void updateAnimation(void) override;

		using Robot::display;

	};
}