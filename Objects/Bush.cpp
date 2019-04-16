#include "Bush.h"

namespace Project
{
	Bush::Bush(float x, float y, float z, float size) : GLobject(x, y, z, 0)
	{
		this->size = size;
	}

	void Bush::display(float shadowMatrix[16])
	{
		glEnable(GL_TEXTURE_2D);
		glColor3f(1, 1, 1);
		glBindTexture(GL_TEXTURE_2D, texture);
		glPushMatrix();
		glTranslatef(posX, posY, posZ);

		float half = size / 2;
		float quarter = size / 4;

		glBegin(GL_QUADS);

		for (char i = -1; i < 2; i += 2) {
			glTexCoord2f(0.01, 0.01);
			glVertex3f(half, 0, quarter * i);
			glTexCoord2f(0.01, 0.99);
			glVertex3f(half, size, quarter * i);
			glTexCoord2f(0.99, 0.99);
			glVertex3f(-half, size, quarter * i);
			glTexCoord2f(0.99, 0.01);
			glVertex3f(-half, 0, quarter * i);
		}

		for (char i = -1; i < 2; i += 2) {
			glTexCoord2f(0.01, 0.01);
			glVertex3f(quarter * i, 0, half);
			glTexCoord2f(0.01, 0.99);
			glVertex3f(quarter * i, size, half);
			glTexCoord2f(0.99, 0.99);
			glVertex3f(quarter * i, size, -half);
			glTexCoord2f(0.99, 0.01);
			glVertex3f(quarter * i, 0, -half);
		}

		glEnd();

		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
	}

	void Bush::loadTextures(TextureManager& manager)
	{
		texture = manager.loadTexture("Bush.tga", loadTGA);
	}
}