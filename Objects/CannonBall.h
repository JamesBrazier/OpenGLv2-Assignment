// header file for the cannonBall class
// Author: jbr 185

#pragma once

#include "Objects.h"

namespace Project
{
	// the cannon ball
	class CannonBall : public GLobject, public GLanimated
	{
	private:

		float velX = 0, velZ = 0, velY = 0; // the speed of the ball in each axis
		bool rolling = false; // whether we need to rotate the ball

	public:

		CannonBall(float posX, float posY, float posZ, float velX, float velY, float velZ);

		void display(float shadowMatrix[16]) override;

		void fire(void);

		void updateAnimation(void) override;

	};
}