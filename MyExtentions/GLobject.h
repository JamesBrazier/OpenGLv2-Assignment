// header file for the GLobject class
// Author: jbr 185

#pragma once

namespace Project
{
	// A basic gl object in this scene, this is an abstract class with some basic common implementation
	class GLobject
	{
	protected:

		float posX = 0, posY = 0, posZ = 0; // The position of the object
		float orientation = 0; // The rotation around the y axis

	public:

		GLobject(float x, float y, float z, float orientation);

		// displays the object in the scene, shadow matrix given for shadow rendering
		virtual void display(float shadowMatrix[16]) = 0;

		virtual void setPosition(float x, float y, float z);

		virtual void setOrientation(float value);

		virtual void getPosition(float* x, float* y, float* z);

		virtual float getOrientation();

	};
}