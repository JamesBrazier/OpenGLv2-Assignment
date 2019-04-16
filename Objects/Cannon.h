// header file for the cannon class
// Author: jbr 185

#pragma once

#include "Objects.h"

namespace Project
{
	class CannonBall;

	// The cannon object, which can fire a cannonball
	class Cannon : public GLobject, public GLanimated, public GLtextured
	{
	private:

		GLuint baseTex;
		GLuint barrelTex;
		float rotationX = 12; // the rotation aroun the x axis for the fire animation
		bool firing = false; // whether we need to run the firing animation
		int cannonBallLimit = 0; // the max amount of cannon balls at once
		vector<CannonBall> balls = vector<CannonBall>();
		ParticleSource particles = ParticleSource(0, 0, 0, 0, 100);

		void drawBarrel(float rotation, float shadowMatrix[16]);

		void drawBase();

	public:

		Cannon(float x, float y, float z, float orientation, int cannonBallLimit);

		void display(float shadowMatrix[16]) override;

		void loadTextures(TextureManager& manager) override;

		void fire(void);

		void updateAnimation(void) override;

		void setRotationAroundX(float value);

		float getRotationAroundX(void);

		bool isFiring(void);

	};
}