#include "Particle.h"

namespace Project
{
	constexpr int maxHight = 100;
	constexpr int frictionFactor = 10;

	extern Camera camera;

	Particle::Particle() : GLobject(0, 0, 0, 0)
	{ }

	Particle::Particle(float posX, float posY, float posZ, float velX, float velY, float velZ) : GLobject(posX, posY, posZ, 0)
	{
		this->velX = velX;
		this->velY = velY;
		this->velZ = velZ;
	}

	void Particle::display(float shadowMatrix[16])
	{ 
		float camX, camY, camZ;
		camera.getPosition(&camX, &camY, &camZ);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture);
		glDisable(GL_LIGHTING);
		drawBillboard(1, 1, posX, posY, posZ, camX, camY, camZ);
		glEnable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);
	}

	void Particle::loadTextures(TextureManager& manager)
	{
		texture = manager.loadTexture("Smoke.tga", loadTGA);
	}

	void Particle::updateAnimation(void)
	{
		switch (animationState) {
			case 0:
				if (velX < 0) { // reduce velocity toward 0
					velX += friction * frictionFactor;
					if (velX >= 0) {
						velX = 0;
					}
				} else {
					velX -= friction * frictionFactor;
					if (velX <= 0) {
						velX = 0;
					}
				}
				posX += velX; // add the velocity to position
				posY += velY; // the particle floats infinitely upwards
				if (velZ < 0) {
					velZ += friction * frictionFactor;
					if (velZ >= 0) {
						velZ = 0;
					}
				} else {
					velZ -= friction * frictionFactor;
					if (velZ <= 0) {
						velZ = 0;
					}
				}
				posZ += velZ;
				if (posY >= maxHight) {
					animationState = 1; // once we reach the maxHeight we stop
				}
				break;
			case 1:
				break;
		}
	}

	bool Particle::finished(void)
	{
		return posY >= maxHight;
	}
}