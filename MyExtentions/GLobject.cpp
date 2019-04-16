#include "GLobject.h"

namespace Project
{

	GLobject::GLobject(float x, float y, float z, float orientation)
	{ 
		posX = x; posY = y; posZ = z;
		this->orientation = orientation;
	}

	/*void GLobject::display(float Shaowmatrix[16])
	{ }*/

	void GLobject::setPosition(float x, float y, float z)
	{
		posX = x; posY = y; posZ = z;
	}

	void GLobject::setOrientation(float value)
	{
		orientation = value;
	}
	void GLobject::getPosition(float* x, float* y, float* z)
	{
		*x = posX; *y = posY; *z = posZ;
	}

	float GLobject::getOrientation()
	{
		return orientation;
	}
}