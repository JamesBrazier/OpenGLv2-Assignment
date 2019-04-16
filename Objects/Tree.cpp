#include "Tree.h"

namespace Project
{
	extern GLUquadric* quadric;

	Tree::Tree(float x, float y, float z, float leafHeight, float CanopyHeight) : GLobject(x, y, z, 0)
	{ 
		this->height = leafHeight;
		this->size = CanopyHeight;
	}

	void Tree::display(float shadowMatrix[16])
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, leafTex);
		glPushMatrix();
		glTranslatef(posX, posY, posZ);
		glRotatef(-90, 1, 0, 0);
		glTranslatef(0, 0, height - 1);

		glColor3f(0.4, 0.6, 0.4);
		for (float i = size / 2; i >= 0; i--) { // dynamically draw and size leaves
			glPushMatrix();

			glTranslatef(0, 0, size - (i * 2));
			drawCylinder(quadric, 1 + 0.5 * i, 0.5 * i, 2, 32, 5);

			glPopMatrix();
		}

		glBindTexture(GL_TEXTURE_2D, trunkTex);
		glColor3f(0.8, 0.6, 0.4);
		glRotatef(180, 1, 0, 0);
		drawCylinder(quadric, 0.5, 0.5, height, 16, height);

		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
	}

	void Tree::loadTextures(TextureManager& manager)
	{ 
		leafTex = manager.loadTexture("Leaves.bmp", loadBMP);
		trunkTex = manager.loadTexture("Bark.bmp", loadBMP);
	}
}