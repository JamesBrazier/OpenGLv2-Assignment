#include "SpaceShip.h"

namespace Project
{
	extern GLUquadric* quadric;

	inline void SpaceShip::drawHull(void)
	{ 
		glColor3f(0.5, 0.5, 0.5);
		//glEnable(GL_TEXTURE_2D);
		glMaterialfv(GL_FRONT, GL_SPECULAR, white);
		glPushMatrix();
		glTranslatef(0, 11.5, 0);

		glPushMatrix();
		glScalef(20, 4, 20);
		gluSphere(quadric, 1, 40, 40);
		glPopMatrix();

		glPushMatrix();
		glScalef(10, 3, 10);
		glTranslatef(0, 1.5, 0);
		gluSphere(quadric, 1, 30, 30);
		glPopMatrix();

		glDisable(GL_TEXTURE_2D);
		glPushMatrix();
		glColor3f(0.8, 0.8, 1);
		glScalef(5, 4, 5);
		glTranslatef(0, 1.5, 0);
		gluSphere(quadric, 1, 20, 20);
		glPopMatrix();

		glPushMatrix();
		glRotatef(spin, 0, 1, 0);
		for (char i = 0; i < 3; i++) {
			glPushMatrix();
			glRotatef(120 * i, 0, 1, 0);
			spotlights[i].setDirection(0, -2, 1);
			spotlights[i].setPosition(0, -3.8, 8.5);
			spotlights[i].display();
			glPopMatrix();
		}
		glColor3f(0.2, 0.2, 0.2);
		glTranslatef(0, 5, 0);
		glRotatef(90, 1, 0, 0);
		drawCylinder(quadric, 10.2, 10.2, 8.7, 30, 20);
		glPopMatrix();

		glPopMatrix();
		glMaterialfv(GL_FRONT, GL_SPECULAR, black);
		glDisable(GL_TEXTURE_2D);
	}

	inline void SpaceShip::drawLandGear(void)
	{ 
		glColor3f(0.2, 0.2, 0.2);
		glPushMatrix();

		glRotatef(45, 0, 1, 0);
		for (char i = 0; i < 4; i++) {
			glPushMatrix();
			glRotatef(90 * i, 0, 1, 0);
			glTranslatef(11.5, 8.6, 0);
			glRotatef(30, 0, 0, 1);

			glPushMatrix(); // draw foot
			glTranslatef(0, -upperGearLen - lowerGearLen, 0);
			glRotatef(footTilt - 30, 0, 0, 1);
			glScalef(2.5, 0.4, 2.5);
			drawCube(1);
			glPopMatrix();

			glPushMatrix(); // lower leg
			glTranslatef(0, -(upperGearLen + (lowerGearLen / 2)), 0);
			glScalef(0.5, lowerGearLen, 0.5);
			drawCube(1);
			glPopMatrix();

			glPushMatrix(); // upper leg
			glTranslatef(0, -(upperGearLen / 2), 0);
			glScalef(0.8, upperGearLen, 0.8);
			drawCube(1);
			glPopMatrix();

			glPopMatrix();
		}

		glPopMatrix();
	}

	SpaceShip::SpaceShip(float x, float y, float z, float orientation) : GLobject(x, y, z, orientation)
	{ 
		animationSpeed = 1;
		GLenum light = GL_LIGHT7; // start from max light as to minimise interfrence
		for (char i = 0; i < 3; i++) {
			spotlights[i] = Spotlight(light--);
			spotlights[i].setColour(0, 1, 0.8);
		}
	}

	void SpaceShip::initialize(void)
	{ 
		for (char i = 0; i < 3; i++) {
			spotlights[i].initialize();
		}
	}

	void SpaceShip::display(float shadowMatrix[16])
	{
		glPushMatrix();
		//glBindTexture(GL_TEXTURE_2D, hullTex);
		glTranslatef(posX, posY, posZ);
		glRotatef(orientation, 0, 1, 0);

		drawLandGear();

		drawHull();

		glPopMatrix();
	}

	void SpaceShip::updateAnimation(void)
	{ 
		switch (animationState) {
			case 1:
				if (footTilt < 15) {
					footTilt += animationSpeed;
				}
				if (upperGearLen >= 0.5) {
					upperGearLen -= animationSpeed / 10;
				}
				lowerGearLen -= animationSpeed / 10;
				if (lowerGearLen <= 0.3) {
					animationState = 2;
					cout << posY;
				}
			case 2:
				posY += SSflySpeed;
				if (posY >= maxHeight) {
					animationState = 3;
				}
			case 3:
				spin = spin + ((int) animationSpeed * 10) % 360;
				break;
			case 4:
				if (footTilt > 0) {
					footTilt -= animationSpeed;
				}
				if (upperGearLen < 5) {
					upperGearLen += animationSpeed / 10;
				}
				lowerGearLen += animationSpeed / 10;
				if (lowerGearLen >= 5) {
					footTilt = 0;
					upperGearLen = 5;
					lowerGearLen = 5;
					animationState = 5;
				}
			case 5:
				posY -= SSflySpeed;
				if (posY <= 5) {
					animationState = 4;
				}
				if (posY <= minHeight) {
					posY = minHeight;
					animationState = 0;
				}
				spin = spin + ((int) animationSpeed * 10) % 360;
				break;
			case 0:
			default:
				spin = spin + ((int) animationSpeed) % 360;
				break;
		}
	}

	void SpaceShip::liftOff(void)
	{
		animationState = 1;
	}

	void SpaceShip::land(void)
	{
		animationState = 5;
	}

	bool SpaceShip::isLanded(void)
	{
		return posY <= 0;
	}
}