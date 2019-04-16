#include "Robot.h"

namespace Project
{
	extern GLUquadric* quadric; // drawing quadric

	inline void Robot::drawLeg(float height, float offset, float legLift, float legRotation, float lowLegLift, float footLift, int sideMod)
	{
		glPushMatrix();
		glTranslatef(offset, height + 1.6, 0);

		glColor3f(0.2, 0.2, 0.2);
		drawCube(0.3); // draw hip

		glRotatef(legRotation * sideMod, 0, 1, 0);
		glRotatef(-legLift, 1, 0, 0);
		glTranslatef(0, -0.75, 0);

		glColor3f(0.5, 0.5, 0.5);
		glPushMatrix(); // draw upper leg
		glTranslatef(0, 0.375, 0);
		glScalef(0.2, 0.75, 0.2);
		drawCube(1);
		glPopMatrix();

		glColor3f(0.2, 0.2, 0.2);
		drawCube(0.3); // draw knee

		glRotatef(lowLegLift, 1, 0, 0);
		glTranslatef(0, -0.75, 0);

		glColor3f(0.5, 0.5, 0.5);
		glPushMatrix(); // draw lower leg
		glTranslatef(0, 0.375, 0);
		glScalef(0.2, 0.75, 0.2);
		drawCube(1);
		glPopMatrix();

		glColor3f(0.2, 0.2, 0.2);
		drawCube(0.3); // draw ankle

		glColor3f(0.5, 0.5, 0.5);
		glRotatef(-footLift, 1, 0, 0);
		glTranslatef(0, -0.1, 0.1); // draw foot
		glScalef(0.5, 0.2, 0.7);
		drawCube(1);

		glPopMatrix();
	}

	inline void Robot::drawArm(float height, float offset, float shoulderRotation, float armRotation, float armLift, float wristRotation, float forearmLift, float handLift, int sideMod)
	{
		glPushMatrix();
		glTranslatef(offset + (0.2 * sideMod), height, 0);

		glColor3f(0.2, 0.2, 0.2);
		glPushMatrix(); // draw shoulder
		glTranslatef(0.1 * -sideMod, 0, 0);
		glScalef(0.5, 0.4, 0.4);
		drawCube(1);
		glPopMatrix();

		glRotatef(-shoulderRotation, 1, 0, 0);
		glRotatef(armLift * sideMod, 0, 0, 1);
		glRotatef(armRotation * sideMod, 0, 1, 0);
		glTranslatef(0, -0.75, 0);

		glColor3f(0.5, 0.5, 0.5);
		glPushMatrix(); // draw upperArm
		glTranslatef(0, 0.375, 0);
		glScalef(0.2, 0.75, 0.2);
		drawCube(1);
		glPopMatrix();

		glColor3f(0.2, 0.2, 0.2);
		drawCube(0.3); // draw elbow

		glRotatef(-forearmLift, 1, 0, 0);
		glRotatef(wristRotation * sideMod, 0, 1, 0);
		glTranslatef(0, -0.75, 0);

		glColor3f(0.5, 0.5, 0.5);
		glPushMatrix(); // draw forearm
		glTranslatef(0, 0.375, 0);
		glScalef(0.2, 0.75, 0.2);
		drawCube(1);
		glPopMatrix();

		glColor3f(0.2, 0.2, 0.2);
		drawCube(0.3); // draw wrist

		glColor3f(0.5, 0.5, 0.5);
		glTranslatef(0, -0.2, 0); // draw hand
		glRotatef(-handLift * sideMod, 0, 0, 1);
		glTranslatef(0, -0.1, 0);
		glScalef(0.2, 0.6, 0.5);
		drawCube(1);

		glPopMatrix();
	}

	inline void Robot::drawHead(float x, float y, float z, float rotation, float lookUp)
	{
		glPushMatrix();
		glTranslatef(x, y, z); // universal tranformations
		glRotatef(rotation, 0, 1, 0);
		glRotatef(-lookUp, 1, 0, 0);
		glTranslatef(0, 0.8, 0);

		glColor3f(0.2, 0.2, 0.2);
		glPushMatrix(); // draw the antenna
		glRotatef(-120, 1, 0, 0);
		drawCone(quadric, 0.1, 0.65, 10, 4);
		glTranslatef(0, 0, 0.6);
		glColor3f(0.5, 0.5, 0.5);
		gluSphere(quadric, 0.075, 16, 16);
		glPopMatrix();

		for (char i = -1; i < 2; i += 2) {
			glColor3f(0.2, 0.2, 0.2);
			glPushMatrix(); // draw an ear
			glTranslatef(0.4 * i, -0.35, 0);
			glScalef(0.15, 0.2, 0.1);
			drawCube(1);
			glPopMatrix();

			glPushMatrix(); // draw the mouth
			glTranslatef(0, -0.65, 0.2);
			if (i == 1) { // only once
				glPushMatrix(); // draw the middle
				glScalef(0.3, 0.2, 0.4);
				drawCube(1);
				glPopMatrix();
			}
			glTranslatef(0.15 * i, 0, 0);
			drawCylinder(quadric, 0.1, 0.1, 0.2, 16, 16);
			glPopMatrix();

			glDisable(GL_LIGHTING);
			glColor3f(0, 1, 0.8);
			glPushMatrix(); // draw an eye
			glTranslatef(0.18 * i, -0.35, 0.2);
			drawCylinder(quadric, 0.1, 0.1, 0.2, 16, 16);
			glPopMatrix();
			glEnable(GL_LIGHTING);
		}

		glColor3f(0.5, 0.5, 0.5);

		glRotatef(90, 1, 0, 0); // draw the skull
		drawCylinder(quadric, 0.4, 0.4, 0.8, 20, 20);
		glScalef(1, 1, 0.5);
		gluSphere(quadric, 0.4, 20, 20);

		glPopMatrix();
	}

	inline void Robot::drawTorso(float x, float y, float z)
	{
		glPushMatrix();
		glTranslatef(x, y, z);

		glColor3f(0.2, 0.2, 0.2); // draw the front panel
		glPushMatrix();
		glScalef(0.8, 1.2, 0.4);
		glTranslatef(0, 0.9, 0.8);
		drawCube(1);
		glPopMatrix();

		glColor3f(0.5, 0.5, 0.5); // draw the body
		glTranslatef(0, 1.8, 0);
		glScalef(0.7, 1, 0.5);
		glRotatef(90, 1, 0, 0);
		drawCylinder(quadric, 1, 0.8, 1.8, 20, 20);
		glScalef(1, 1, 0.5);
		gluSphere(quadric, 1, 20, 20);

		glPopMatrix();
	}

	Robot::Robot(float x, float y, float z, float orientation) : GLobject(x, y, z, orientation)
	{ }

	void Robot::display(float shadowMatrix[16])
	{
		glColor3f(0.5, 0.5, 0.5);
		glMaterialfv(GL_FRONT, GL_SPECULAR, white);
		glPushMatrix();
		glTranslatef(posX, posY, posZ); // universal transformations
		glRotatef(orientation, 0, 1, 0);

		glRotatef(bodyTilt, 1, 0, 0);

		drawHead(0, 3.8, 0, headSpin, headTilt);

		drawTorso(0, 1.5, 0);

		drawArm(3.3, 0.7, LshoulderRotation, LarmRotation, LarmLift, LwristRotation, LforearmLift, LhandLift, 1);
		drawArm(3.3, -0.7, RshoulderRotation, RarmRotation, RarmLift, RwristRotation, RforearmLift, RhandLift, -1);

		drawLeg(0, 0.35, LlegLift, LlegRotation, LlowLegLift, LfootLift, 1);
		drawLeg(0, -0.35, RlegLift, RlegRotation, RlowLegLift, RfootLift, -1);

		glPopMatrix();
		glMaterialfv(GL_FRONT, GL_SPECULAR, black);
	}
}