// header file for the Particle class
// Author: jbr 185

#pragma once

#include "MyExtentions.h"

namespace Project
{
	// a simple billboard with a velocity and movement animation
	class Particle : public GLanimated, public GLobject, public GLtextured
	{
	private:

		float velX = 0, velY = 0, velZ = 0; // the speed in each direction for the particle to move
		GLuint texture;

	public:

		Particle();

		Particle(float posX, float posY, float posZ, float velX, float velY, float velZ);

		void display(float shadowMatrix[16]) override;

		void loadTextures(TextureManager& manager) override;

		void updateAnimation(void) override;

		// whether the particle has reached above maxHeight constant
		bool finished(void);

	};
}