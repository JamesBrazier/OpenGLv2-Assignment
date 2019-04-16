#include "CannonBall.h"

namespace Project
{
	extern GLUquadric* quadric; // the drawing quadric

	CannonBall::CannonBall(float posX, float posY, float posZ, float velX, float velY, float velZ) : GLobject(posX, posY, posZ, 0)
	{
		this->velX = velX;
		this->velY = velY;
		this->velZ = velZ;
	}

	void CannonBall::display(float shadowMatrix[16])
	{
		glColor3f(0.4, 0.4, 0.4);
		glPushMatrix();
		glTranslatef(posX, posY, posZ);
		if (rolling) { // only rotate if we are rolling
			glRotatef(velX * 1000, 1, 0, 0);
			glRotatef(velZ * 1000, 0, 0, 1);
		}

		gluSphere(quadric, 0.4, 16, 16);

		glPopMatrix();
	}

	void CannonBall::fire()
	{
		animationState = 1;
	}

	void CannonBall::updateAnimation()
	{
		switch (animationState) {
			case 0:
				break;
			case 1:
				posX += velX; // add the velocities
				posZ += velZ;
				velY -= gravity + friction; // remove gravity and friction from the air
				posY += velY;
				if (posY <= 0.2) { // if we are in the ground
					animationState = 3; // start rolling
					orientation = 0;
					velX /= 2; // half the velocity
					velZ /= 2;
					rolling = true;
				}
				break;
			case 3:
				if (velX < 0) { // move the velocity towards zero
					velX += friction * 20; // high friction
				} else {
					velX -= friction * 20;
				}
				posX += velX;
				if (velZ < 0) {
					velZ += friction * 20;
				} else {
					velZ -= friction * 20;
				}
				posZ += velZ;
				if (velZ <= 0.01 && velZ >= -0.01 && velX <= 0.01 && velX >= -0.01) { // if the velocity in x & z are about zero, stop
					animationState = 0;
					rolling = false;
				}
				break;
		}
	}
}