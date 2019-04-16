// header file for the particleSource class
// Author: jbr 185

#pragma once

#include "MyExtentions.h"

namespace Project
{
	class Particle;

	// an object that fires particles out of the front of it
	class ParticleSource : public GLobject, public GLanimated
	{
	private:

		int amount = 0; // the amount of particles fired
		GLuint texture;
		Particle* particles;

		// randomly generates a velocity and direction for the particle
		Particle genParticle(void);

	public:

		ParticleSource(float posX, float posY, float posZ, float orientation, int amount);

		~ParticleSource();

		void updateAnimation(void) override;

		// fires the particles
		void fire(void);

		void display(float shadowMatrix[16]) override;

		void setOrientation(float value) override;

	};
}