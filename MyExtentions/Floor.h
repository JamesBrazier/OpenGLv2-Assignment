// header file for the floor class
// Author: jbr 185

#pragma once

#include "MyExtentions.h"

namespace Project
{
	// The class for the ground of the scene
	class Floor : public GLobject, public GLtextured
	{
	private:

		GLuint floorTex;

	public:

		Floor();

		static void displayLines(void);

		void display(float shadowMatrix[16]) override;

		void loadTextures(TextureManager& manager) override;

	};
}