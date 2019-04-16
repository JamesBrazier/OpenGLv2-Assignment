// header file for the Castle class
// Author: jbr 185

#pragma once

#include "Objects.h"

namespace Project
{
	// This is the object class for the castle
	class Castle : public GLobject, public GLtextured
	{
	private:

		GLuint wallTex;
		int size = 0; // size of the castle, scales all aspects to fit
		bool shadowOn = true; // whether the castle's shadow should be rendered

		void drawGate(float x, float y, float z);

		void drawTower(float x, float y, float z);

		void drawWall(float x, float y, float z, float orientation, int length);

		void drawObject(void); // draws the full object, allows for duplication for the shadow

	public:

		Castle(float x, float y, float z, float orientation, int size);

		// builds and displayes the castle ands its shadow if on
		void display(float shadowMatrix[16]) override;

		void loadTextures(TextureManager& manager) override;

		void setSize(int value);

		int getSize();

		void disableShadow(void);

		void enableShadow(void);

	};
}