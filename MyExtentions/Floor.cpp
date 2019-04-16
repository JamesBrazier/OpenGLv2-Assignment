#include "Floor.h"

namespace Project
{
	Floor::Floor() : GLobject(0, 0, 0, 0)
	{ }

	void Floor::displayLines(void)
	{
		glDisable(GL_LIGHTING);
		glColor3f(0.0, 0.5, 0.0); //Floor colour
		glPushMatrix();

		for (int i = -100; i <= 100; i++) {
			glBegin(GL_LINES);			//A set of grid lines on the xz-plane

			glVertex3f(-100, floorHight, i);
			glVertex3f(100, floorHight, i);
			glVertex3f(i, floorHight, -100);
			glVertex3f(i, floorHight, 100);

			glEnd();
		}

		glPopMatrix();
		glEnable(GL_LIGHTING);
	}

	void Floor::display(float shadowMatrix[16])
	{
		glColor4f(1, 1, 1, 1);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, floorTex);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glPushMatrix();

		glBegin(GL_QUADS);
		glNormal3f(0, 1, 0);
		for (int x = -floorRadius; x <= floorRadius; x += 1) {
			for (int z = -floorRadius; z <= floorRadius; z += 1) {
				glTexCoord2f(0.3, 0.10);
				glVertex3f(x, floorHight, z);
				glTexCoord2f(0.35, 0.10);
				glVertex3f(x, floorHight, z + 1);
				glTexCoord2f(0.35, 0.05);
				glVertex3f(x + 1, floorHight, z + 1);
				glTexCoord2f(0.3, 0.05);
				glVertex3f(x + 1, floorHight, z);
			}
		}
		glEnd();

		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
	}

	void Floor::loadTextures(TextureManager& manager)
	{ 
		floorTex = manager.loadTexture("SkyBox.bmp", loadBMP);
	}
}