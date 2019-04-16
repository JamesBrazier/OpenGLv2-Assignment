#include "Castle.h"

namespace Project
{
	extern GLUquadric* quadric; // the quadric to draw with

	void Castle::drawGate(float x, float y, float z)
	{ 
		glPushMatrix();
		glTranslatef(x, y, z);

		glBegin(GL_QUAD_STRIP);

		glNormal3f(0, -1, 0);
		glTexCoord2f(0, 1);
		glVertex3f(-10, 0, 1.5);
		glTexCoord2f(0, 0);
		glVertex3f(-10, 0, -1.5);

		char t = 1;

		// draw the parabolic curve
		for (float x = -5; x <= 5; x += 1) {
			float y = -0.32 * pow(x, 2) + 8;
			for (float z = 1.5; z > -4; z -= 3) {
				glTexCoord2f(x, t);
				glVertex3f(x, y, z);
				t = !t;
			}
		}

		glTexCoord2f(0, 1);
		glVertex3f(10, 0, 1.5);
		glTexCoord2f(0, 0);
		glVertex3f(10, 0, -1.5);

		glNormal3f(1, 0, 0);
		for (int y = 1; y <= 12; y++) {
			for (float z = -1.5; z < 4; z += 3) {
				glTexCoord2f(y, t);
				glVertex3f(10, y, z);
				t = !t;
			}
		}

		glNormal3f(0, 1, 0);
		for (int x = 9; x >= -10; x--) {
			for (float z = -1.5; z < 4; z += 3) {
				glTexCoord2f(x, t);
				glVertex3f(x, 12, z);
				t = !t;
			}
		}

		glNormal3f(-1, 0, 0);
		for (int y = 11; y >= 0; y--) {
			for (float z = -1.5; z < 4; z += 3) {
				glTexCoord2f(x, t);
				glVertex3f(-10, y, z);
				t = !t;
			}
		}

		glEnd();

		// draw the front and back
		for (float z = -1.5; z < 2; z += 3) {
			glBegin(GL_QUAD_STRIP);

			if (z < 0) {
				glNormal3f(0, 0, -1);
			} else {
				glNormal3f(0, 0, 1);
			}
			float x = -5;
			for (float y = 0; y <= 12; y++) {
				glTexCoord2f(-5, y / 2);
				glVertex3f(-10, y, z);
				float archY = -0.32 * pow(x, 2) + 8;
				glTexCoord2f(x / 2, archY / 2);
				glVertex3f(x, archY, z);
				x = fminf(0, x + 1);
			}
			for (float y = 12; y >= 0; y--) {
				glTexCoord2f(5, y / 2);
				glVertex3f(10, y, z);
				float archY = -0.32 * pow(x, 2) + 8;
				glTexCoord2f(x / 2, archY / 2);
				glVertex3f(x, archY, z);
				x = fminf(5, x + 1);
			}

			glEnd();
		}

		glPopMatrix();
	}

	void Castle::drawTower(float x, float y, float z)
	{ 
		glPushMatrix();
		glTranslatef(x, y, z);

		drawCylinder(quadric, 4, 4, 14, 20, 20);
		glTranslatef(0, 0, 14);
		drawCylinder(quadric, 5, 5, 3, 25, 5);

		for (char i = 0; i < 8; i++) {
			glPushMatrix();
			glRotatef(45 * i, 0, 0, 1);
			glTranslatef(4.35, 0, 3.65);
			drawCube(1.5, 0.3);
			glPopMatrix();
		}

		glPopMatrix();
	}

	void Castle::drawWall(float x, float y, float z, float orientation, int length)
	{ 
		glPushMatrix();
		glTranslatef(x, y, z);
		glRotatef(orientation, 0, 1, 0);
		glTranslatef(0, 6, 0);

		for (int i = 0; i < length; i += 2) {
			glPushMatrix();

			glTranslatef(-((length - 1) / 2), 6.5, 0);

			glPushMatrix();
			glTranslatef(i, 0, 1.1);
			drawCube(1, 0.3);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(i, 0, -1.1);
			drawCube(1, 0.3);
			glPopMatrix();

			glPopMatrix();
		}
		glScalef(length, 12, 3);
		drawCube(1, 4);

		glPopMatrix();
	}

	void Castle::drawObject(void)
	{ 
		float halfSize = size / 2, quarterSize = size / 4;

		glTranslatef(posX, posY, posZ);
		glRotatef(orientation, 0, 1, 0);

		drawGate(0, 0, -halfSize);

		// dynamically adjust based on size
		drawWall(quarterSize + 6, 0, -halfSize, 0, (size - 20) / 2);
		drawWall(-(quarterSize + 6), 0, -halfSize, 0, (size - 20) / 2);
		drawWall(0, 0, halfSize, 0, size);
		drawWall(halfSize, 0, 0, 90, size);
		drawWall(-halfSize, 0, 0, 90, size);

		glRotatef(-90, 1, 0, 0); //the towers draw sideways by the x axis

		//Gate towers
		drawTower(-10, halfSize, 0);
		drawTower(10, halfSize, 0);
		//Corner towers
		drawTower(-halfSize, halfSize, 0);
		drawTower(halfSize, halfSize, 0);
		drawTower(-halfSize, -halfSize, 0);
		drawTower(halfSize, -halfSize, 0);
	}

	Castle::Castle(float x, float y, float z, float orientation, int size) : GLobject(x, y, z, orientation)
	{ 
		this->size = size;
	}

	void Castle::display(float shadowMatrix[16])
	{
		glColor3f(1, 1, 1);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, wallTex);
		glPushMatrix();
		drawObject();
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);

		if (shadowOn) { // draw the ugly shadow
			glColor3f(0, 0, 0);
			glDisable(GL_LIGHTING);
			glPushMatrix();
			glMultMatrixf(shadowMatrix);
			drawObject();
			glPopMatrix();
			glEnable(GL_LIGHTING);
		}
	}

	void Castle::loadTextures(TextureManager& manager)
	{ 
		wallTex = manager.loadTexture("Brick.bmp", loadBMP);
	}

	void Castle::setSize(int value)
	{
		size = value;
	}

	int Castle::getSize()
	{
		return size;
	}

	void Castle::disableShadow(void)
	{ 
		shadowOn = false;
	}

	void Castle::enableShadow(void)
	{ 
		shadowOn = true;
	}
}
