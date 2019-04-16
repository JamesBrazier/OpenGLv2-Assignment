// header file for the spaceShip class
// Author: jbr 185

#pragma once

#include "Objects.h"

namespace Project
{
	// The class for the spaceship object
	class SpaceShip : public GLobject, public GLanimated, public GLlight
	{
	private:

		int spin = 0; // the current spin and rate of the center
		float const maxHeight = 150; float const minHeight = 0;
		float upperGearLen = 5, lowerGearLen = 5, footTilt = 0; float const SSflySpeed = 0.1;; // for retracting the landing gear
		Spotlight spotlights[3]; // array of the lights on the ship

		void drawHull(void);

		void drawLandGear(void);

	public:

		SpaceShip(float x, float y, float z, float orientation);

		// initializes the lights on the ship
		void initialize(void) override;

		void display(float shadowMatrix[16]) override;

		// updates the animation of the ship
		void updateAnimation(void) override;

		void liftOff(void);

		void land(void);

		bool isLanded(void);

	};
}