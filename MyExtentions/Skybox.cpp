#include "SkyBox.h"

namespace Project
{
	SkyBox::SkyBox() : GLobject(0, 0, 0, 0)
	{ }

	void SkyBox::display(float shadowMatrix[16])
	{
		glColor3f(1, 1, 1); // white colour so no colour masking
		glDisable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, currentTex);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glPushMatrix();

		// draw a cube with texture coords for the skybox files
		glBegin(GL_QUADS);

		glNormal3f(0, 0, 1);
		glTexCoord2f(0.9999, 0.6666);
		glVertex3f(500, 500, 500);
		glTexCoord2f(0.9999, 0.5001);
		glVertex3f(500, -0.2, 500);
		glTexCoord2f(0.7501, 0.5001);
		glVertex3f(-500, -0.2, 500);
		glTexCoord2f(0.7501, 0.6666);
		glVertex3f(-500, 500, 500);

		glNormal3f(0, 0, -1);
		glTexCoord2f(0.2501, 0.6666);
		glVertex3f(500, 500, -500);
		glTexCoord2f(0.2501, 0.5001);
		glVertex3f(500, -0.2, -500);
		glTexCoord2f(0.4999, 0.5001);
		glVertex3f(-500, -0.2, -500);
		glTexCoord2f(0.4999, 0.6666);
		glVertex3f(-500, 500, -500);

		glNormal3f(1, 0, 0);
		glTexCoord2f(0.01, 0.6666);
		glVertex3f(500, 500, 500);
		glTexCoord2f(0.01, 0.5001);
		glVertex3f(500, -0.2, 500);
		glTexCoord2f(0.2499, 0.5001);
		glVertex3f(500, -0.2, -500);
		glTexCoord2f(0.2499, 0.6666);
		glVertex3f(500, 500, -500);

		glNormal3f(-1, 0, 0);
		glTexCoord2f(0.7499, 0.6666);
		glVertex3f(-500, 500, 500);
		glTexCoord2f(0.7499, 0.5001);
		glVertex3f(-500, -0.2, 500);
		glTexCoord2f(0.5001, 0.5001);
		glVertex3f(-500, -0.2, -500);
		glTexCoord2f(0.5001, 0.6666);
		glVertex3f(-500, 500, -500);

		glNormal3f(0, 1, 0);
		glTexCoord2f(0.251, 0.999);
		glVertex3f(500, 500, 500);
		glTexCoord2f(0.251, 0.665);
		glVertex3f(500, 500, -500);
		glTexCoord2f(0.499, 0.665);
		glVertex3f(-500, 500, -500);
		glTexCoord2f(0.499, 0.999);
		glVertex3f(-500, 500, 500);

		glNormal3f(0, -1, 0);
		glTexCoord2f(0.4999, 0.3333);
		glVertex3f(500, -0.2, 500);
		glTexCoord2f(0.4999, 0.0001);
		glVertex3f(500, -0.2, -500);
		glTexCoord2f(0.2501, 0.0001);
		glVertex3f(-500, -0.2, -500);
		glTexCoord2f(0.3501, 0.3333);
		glVertex3f(-500, -0.2, 500);

		glEnd();

		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
		glEnable(GL_LIGHTING);
	}

	void SkyBox::loadTextures(TextureManager& manager)
	{
		dayTex = manager.loadTexture("SkyBox.bmp", loadBMP);
		nightTex = manager.loadTexture("SkyBox Night.bmp", loadBMP);
		currentTex = dayTex;
	}

	void SkyBox::setDay(bool state)
	{ 
		if (state) {
			currentTex = dayTex;
		} else {
			currentTex = nightTex;
		}
	}
}