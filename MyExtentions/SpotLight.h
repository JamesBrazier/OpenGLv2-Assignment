// header file for the spotlight class
// Author: jbr 185

#pragma once

#include "MyExtentions.h"

namespace Project
{
	// A simple class for a spotlight and a sphere for the "source" of the light
	class Spotlight : public GLlight
	{
	private:

		GLenum light; // the light value
		float pos[4] = { 0, 0, 0, 1 }; // the position
		float dir[4] = { 0, 0, 0, 1 }; // the direction
		float colour[4] = { 0, 0, 0, 1 }; // the colour

	public:

		Spotlight();

		Spotlight(GLenum light);

		Spotlight(GLenum light, float posX, float posY, float posZ,
				  float dirX, float dirY, float dirZ,
				  float clrR, float clrG, float clrB);

		// enable and set the colour of the light
		void initialize(void) override;

		void display(void);

		void setPosition(float x, float y, float z);

		void setDirection(float x, float y, float z);

		void setColour(float r, float g, float b);

		void getPosition(float* x, float* y, float* z);

		void getDirection(float* x, float* y, float* z);

		void getColour(float* r, float* g, float* b);

	};
}