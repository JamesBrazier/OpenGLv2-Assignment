#include "MyExtentions.h"

namespace Project
{
	void drawCube(double size)
	{
		drawCube(size, 1); // draw cube with texture scale 1
	}

	void drawQuad(double width, double height)
	{
		double x = width / 2;
		double y = height / 2;

		// draw a quad around the origin
		glBegin(GL_QUADS);

		glTexCoord2f(0.01, 0.01);
		glVertex3f(-x, -y, 0);
		glTexCoord2f(0.01, 0.99);
		glVertex3f(-x, y, 0);
		glTexCoord2f(0.99, 0.99);
		glVertex3f(x, y, 0);
		glTexCoord2f(0.99, 0.01);
		glVertex3f(x, -y, 0);

		glEnd();
	}

	void drawBillboard(double width, double height, double locX, double locY, double locZ, double camX, double camY, double camZ)
	{
		double deltaX = camX - locX; // get the distance to the camera
		double deltaZ = camZ - locZ;
		float rotY = atan(deltaX / deltaZ); // orientate it to look at the camera
		// we use the hypotenuse of the x and z distances for the angle around x
		float rotX = -atan((camY - locY) / sqrt(pow(deltaX, 2) + pow(deltaZ, 2))); // orientate it to look up at the camera

		if (deltaZ < 0) // aton is always positive so we need to flip it
			rotX = -rotX;

		glPushMatrix();
		glTranslatef(locX, locY, locZ);
		glRotatef(radianToDegree(rotY), 0, 1, 0);
		glRotatef(radianToDegree(rotX), 1, 0, 0);
		drawQuad(width, height);
		glPopMatrix();
	}

	void drawCube(double size, float textureScale)
	{
		double temp = size / 2;

		glBegin(GL_QUADS);

		glNormal3f(0, 0, 1);
		glTexCoord2f(textureScale, textureScale);
		glVertex3f(temp, temp, temp);
		glTexCoord2f(textureScale, 0);
		glVertex3f(temp, -temp, temp);
		glTexCoord2f(0, 0);
		glVertex3f(-temp, -temp, temp);
		glTexCoord2f(0, textureScale);
		glVertex3f(-temp, temp, temp);

		glNormal3f(0, 0, -1);
		glTexCoord2f(textureScale, textureScale);
		glVertex3f(temp, temp, -temp);
		glTexCoord2f(textureScale, 0);
		glVertex3f(temp, -temp, -temp);
		glTexCoord2f(0, 0);
		glVertex3f(-temp, -temp, -temp);
		glTexCoord2f(0, textureScale);
		glVertex3f(-temp, temp, -temp);

		glNormal3f(1, 0, 0);
		glTexCoord2f(textureScale, textureScale);
		glVertex3f(temp, temp, temp);
		glTexCoord2f(textureScale, 0);
		glVertex3f(temp, -temp, temp);
		glTexCoord2f(0, 0);
		glVertex3f(temp, -temp, -temp);
		glTexCoord2f(0, textureScale);
		glVertex3f(temp, temp, -temp);

		glNormal3f(-1, 0, 0);
		glTexCoord2f(textureScale, textureScale);
		glVertex3f(-temp, temp, temp);
		glTexCoord2f(textureScale, 0);
		glVertex3f(-temp, -temp, temp);
		glTexCoord2f(0, 0);
		glVertex3f(-temp, -temp, -temp);
		glTexCoord2f(0, textureScale);
		glVertex3f(-temp, temp, -temp);

		glNormal3f(0, 1, 0);
		glTexCoord2f(textureScale, textureScale);
		glVertex3f(temp, temp, temp);
		glTexCoord2f(textureScale, 0);
		glVertex3f(temp, temp, -temp);
		glTexCoord2f(0, 0);
		glVertex3f(-temp, temp, -temp);
		glTexCoord2f(0, textureScale);
		glVertex3f(-temp, temp, temp);

		glNormal3f(0, -1, 0);
		glTexCoord2f(textureScale, textureScale);
		glVertex3f(temp, -temp, temp);
		glTexCoord2f(textureScale, 0);
		glVertex3f(temp, -temp, -temp);
		glTexCoord2f(0, 0);
		glVertex3f(-temp, -temp, -temp);
		glTexCoord2f(0, textureScale);
		glVertex3f(-temp, -temp, temp);

		glEnd();
	}

	void drawCylinder(GLUquadric* quadric, double baseRadius, double topRadius, double height, int slices, int stacks)
	{ 
		glPushMatrix();
		gluDisk(quadric, 0, baseRadius, slices, 1);
		gluCylinder(quadric, baseRadius, topRadius, height, slices, stacks);
		glTranslatef(0, 0, height);
		gluDisk(quadric, 0, topRadius, slices, 1);
		glPopMatrix();
	}

	void drawHollowCylinder(GLUquadric * quadric, double baseRadius, double baseOpeningRadius, double topRadius, double topOpeningRadius, double height, int slices, int stacks)
	{ 
		glPushMatrix();
		gluDisk(quadric, baseOpeningRadius, baseRadius, slices, 1);
		gluCylinder(quadric, baseRadius, topRadius, height, slices, stacks);
		gluCylinder(quadric, baseOpeningRadius, topOpeningRadius, height, slices, stacks);
		glTranslatef(0, 0, height);
		gluDisk(quadric, topOpeningRadius, topRadius, slices, 1);
		glPopMatrix();
	}

	void drawCone(GLUquadric * quadric, double baseRadius, double height, int slices, int stacks)
	{ 
		gluDisk(quadric, 0, baseRadius, slices, stacks);
		gluCylinder(quadric, baseRadius, 0, height, slices, 1);
	}
}