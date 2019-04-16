#include "Cannon.h"

namespace Project
{
	extern GLUquadric* quadric; // the quadric for drawing

	void Cannon::drawBarrel(float rotation, float shadowMatrix[16])
	{
		glPushMatrix();
		glTranslatef(1.8, 2.45, 0);
		glRotatef(rotation, 0, 0, 1);
		glTranslatef(-3.4, 0, 0);
		glRotatef(90, 0, 1, 0);

		glPushMatrix();
		glTranslatef(0, 0, 7.5);
		drawHollowCylinder(quadric, 0.585, 0.385, 0.7, 0.4, 0.25, 20, 5);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0, 0, 7);
		drawHollowCylinder(quadric, 0.6, 0.4, 0.585, 0.385, 0.5, 20, 5);
		drawHollowCylinder(quadric, 0.65, 0.4, 0.65, 0.4, 0.1, 20, 1);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0, 0, 3);
		drawHollowCylinder(quadric, 0.7, 0.5, 0.6, 0.4, 4, 20, 10);
		drawHollowCylinder(quadric, 0.75, 0.5, 0.75, 0.5, 0.1, 20, 1);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0, 0, 1);
		drawCylinder(quadric, 0.8, 0.7, 2, 20, 20);
		drawCylinder(quadric, 0.85, 0.85, 0.1, 20, 1);
		glPopMatrix();

		drawCylinder(quadric, 0.9, 0.8, 1, 20, 10);
		drawCylinder(quadric, 0.95, 0.95, 0.1, 20, 1);

		glPushMatrix();
		glScalef(1, 1, 0.5);
		gluSphere(quadric, 0.9, 20, 20);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0, 0, -0.8);
		drawCylinder(quadric, 0.25, 0.2, 0.5, 8, 3);
		gluSphere(quadric, 0.25, 10, 10);
		glPopMatrix();

		glDisable(GL_LIGHTING);
		glColor3f(0, 0, 0);
		glTranslatef(0, 0, 3.6);
		gluDisk(quadric, 0, 0.6, 10, 1);
		glEnable(GL_LIGHTING);

		glPopMatrix();
		glMaterialfv(GL_FRONT, GL_SPECULAR, black);
	}

	void Cannon::drawBase()
	{
		glColor3ub(89, 49, 0);
		glBindTexture(GL_TEXTURE_2D, baseTex);
		glPushMatrix();

		glTranslatef(0, 0.6, 0);

		for (char i = -1; i < 2; i += 2) {
			glPushMatrix();

			glPushMatrix();
			glTranslatef(1, 1, 1.1 * i);
			glScalef(3, 2, 0.3);
			drawCube(1);
			glPopMatrix();

			glTranslatef(-1, 0.7, 1.1 * i);
			glScalef(1, 1, 0.3);
			drawCube(1);
			glPopMatrix();
		}

		glPushMatrix();
		glTranslatef(1.8, 0.6, 0);
		glScalef(1, 0.8, 2.3);
		drawCube(1);
		glPopMatrix();

		glPushMatrix();
		glScalef(5, 0.5, 2.5);
		drawCube(1);
		glPopMatrix();

		glColor3f(0.4, 0.4, 0.4);
		glBindTexture(GL_TEXTURE_2D, barrelTex);
		glMaterialfv(GL_FRONT, GL_SPECULAR, white);
		for (char i = -1; i < 2; i += 2) {
			glPushMatrix();
			glTranslatef(0.3 + (1.6 * i), 0, 1.25);
			drawCylinder(quadric, 0.75, 0.75, 0.3, 20, 2);
			drawCylinder(quadric, 0.3, 0.3, 0.35, 15, 1);
			drawCylinder(quadric, 0.2, 0.2, 0.45, 10, 1);
			glPopMatrix();
		}

		for (char i = -1; i < 2; i += 2) {
			glPushMatrix();
			glTranslatef(0.3 + (1.6 * i), 0, -1.55);
			drawCylinder(quadric, 0.75, 0.75, 0.3, 20, 2);
			glTranslatef(0, 0, -0.05);
			drawCylinder(quadric, 0.3, 0.3, 0.35, 15, 1);
			glTranslatef(0, 0, -0.1);
			drawCylinder(quadric, 0.2, 0.2, 0.45, 10, 1);
			glPopMatrix();
		}

		glTranslatef(1.8, 1.85, -1.3);
		drawCylinder(quadric, 0.2, 0.2, 2.6, 8, 5);

		glPopMatrix();
	}

	Cannon::Cannon(float x, float y, float z, float orientation, int cannonBallLimit) : GLobject(x, y, z, orientation)
	{ 
		this->cannonBallLimit = cannonBallLimit;
		animationSpeed = 1; // we want a slow recoil animation, it doesn't look good too fast
	}

	void Cannon::display(float shadowMatrix[16])
	{
		glEnable(GL_TEXTURE_2D);
		glPushMatrix();
		glTranslatef(posX, posY, posZ);
		glRotatef(orientation, 0, 1, 0);

		drawBase();

		drawBarrel(rotationX, shadowMatrix);

		glPopMatrix();

		for (CannonBall& ball : balls) { // draw all the cannon balls
			ball.display(shadowMatrix);
		}

		particles.display(shadowMatrix);

		glDisable(GL_TEXTURE_2D);
	}

	void Cannon::loadTextures(TextureManager& manager)
	{
		barrelTex = manager.loadTexture("Metal.bmp", loadBMP);
		baseTex = manager.loadTexture("Wood.bmp", loadBMP);
	}

	void Cannon::fire(void)
	{
		static int ball = 0; // the current ball we are firing
		static bool ballsGenerated = false; // whether all the balls have been generated in the vector

		if (!firing) {
			firing = true;
			float sinY = sin(degreeToRadian(rotationX));
			float cosY = cos(degreeToRadian(rotationX));
			float sinX = sin(-degreeToRadian(orientation));
			float cosX = cos(-degreeToRadian(orientation));
			float endPosX = posX + (cosX * cosY * 6);
			float endPosY = posY + (sinY * 6) + (2.2 * cosY);
			float endPosZ = posZ + (sinX * cosY * 6);

			if (!ballsGenerated) {
				balls.push_back(CannonBall(endPosX, endPosY, endPosZ, cosX * cosY * cannonVel, sinY * cannonVel, sinX * cosY * cannonVel));
			} else {
				balls[ball] = CannonBall(endPosX, endPosY, endPosZ, cosX * cosY * cannonVel, sinY * cannonVel, sinX * cosY * cannonVel);
			}

			particles.setOrientation(-orientation); // the orientation for a cannon and particle source are opposite directions
			particles.setPosition(endPosX, endPosY, endPosZ);
			particles.fire();
			balls.at(ball).fire();
			ball++;

			if (ball >= cannonBallLimit) {
				ballsGenerated = true; // we've now generated all the balls
				ball = 0;
			}
		}
	}

	void Cannon::updateAnimation(void)
	{
		for (CannonBall& ball : balls) {
			ball.updateAnimation();
		}

		particles.updateAnimation();

		static float oldRotation; // the old state for the rorarion around x axis

		switch (animationState) {
			case 0:
				if (firing) {
					animationState = 1;
					oldRotation = rotationX;
				}
				break;
			case 1:
				rotationX += animationSpeed;
				animationCounterA++;
				if (rotationX >= 15 || animationCounterA >= 2) { // move the barrel up for a bit
					animationCounterA = 0;
					animationState = 2;
				}
				break;
			case 2:
				rotationX -= animationSpeed;
				if (rotationX <= oldRotation) { // move it back down
					rotationX = oldRotation;
					animationState = 3;
				}
				break;
			case 3:
				animationCounterA++;
				if (animationCounterA >= 60) { // timeout before we can fire again
					animationCounterA = 0;
					animationState = 0;
					firing = false;
				}
				break;
		}
	}

	void Cannon::setRotationAroundX(float value)
	{ 
		rotationX = value;
	}

	float Cannon::getRotationAroundX(void)
	{
		return rotationX;
	}

	bool Cannon::isFiring(void)
	{
		return firing;
	}
}