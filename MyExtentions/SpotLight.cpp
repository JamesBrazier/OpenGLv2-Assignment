#include "SpotLight.h"

namespace Project
{
	extern GLUquadric* quadric; // the quadric we are using to draw

	Spotlight::Spotlight()
	{ }

	Spotlight::Spotlight(GLenum light)
	{ 
		switch (light) { // ensure the GLenum given is a GL light
			case GL_LIGHT1:
			case GL_LIGHT2:
			case GL_LIGHT3:
			case GL_LIGHT4:
			case GL_LIGHT5:
			case GL_LIGHT6:
			case GL_LIGHT7:
				this->light = light;
				break;
			default:
				throw -1; // crash otherwise 
		}
	}

	Spotlight::Spotlight(GLenum light, float posX, float posY, float posZ,
						 float dirX, float dirY, float dirZ, 
						 float clrR, float clrG, float clrB) : Spotlight(light)
	{ 
		this->pos[0] = posX; this->pos[1] = posY; this->pos[2] = posZ;
		this->dir[0] = dirX; this->dir[1] = dirY; this->dir[2] = dirZ;
		this->colour[0] = clrR; this->colour[1] = clrG; this->colour[2] = clrB; 
	}

	void Spotlight::initialize(void)
	{
		glEnable(light);
		glLightf(light, GL_SPOT_CUTOFF, 30);
		glLightf(light, GL_SPOT_EXPONENT, 0.1);
	}

	void Spotlight::display(void)
	{ 
		glLightfv(light, GL_DIFFUSE, colour);
		glLightfv(light, GL_SPECULAR, colour);
		glLightfv(light, GL_SPOT_DIRECTION, dir);
		glLightfv(light, GL_POSITION, pos);
		glDisable(GL_LIGHTING);
		glColor4f(colour[0], colour[1], colour[2], 0.5);
		glPushMatrix();

		glTranslatef(pos[0], pos[1], pos[2]);
		gluSphere(quadric, 0.2, 8, 8); // draw a wee sphere as the 'source'

		glPopMatrix();
		glEnable(GL_LIGHTING);
	}

	void Spotlight::setPosition(float x, float y, float z)
	{ 
		pos[0] = x; pos[1] = y; pos[2] = z;
	}

	void Spotlight::setDirection(float x, float y, float z)
	{ 
		dir[0] = x; dir[1] = y; dir[2] = z;
	}

	void Spotlight::setColour(float r, float g, float b)
	{ 
		this->colour[0] = r; this->colour[1] = g; this->colour[2] = b;
		glLightfv(light, GL_DIFFUSE, colour);
		glLightfv(light, GL_SPECULAR, colour);
	}

	void Spotlight::getPosition(float* x, float* y, float* z)
	{ 
		*x = pos[0]; *y = pos[1]; *z = pos[2];
	}

	void Spotlight::getDirection(float* x, float* y, float* z)
	{ 
		*x = dir[0]; *y = dir[1]; *z = dir[2];
	}

	void Spotlight::getColour(float* r, float* g, float* b)
	{ 
		*r = colour[0]; *g = colour[1]; *b = colour[2];
	}
}