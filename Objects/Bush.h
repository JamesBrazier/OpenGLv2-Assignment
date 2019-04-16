// header file for the Bush class
// Author: jbr 185

#pragma once

#include "Objects.h"

namespace Project
{
	// a hashed shape of quads for a bush
	class Bush : public GLobject, public GLtextured
	{
	private:

		GLuint texture;
		float size = 0; // the size of the bush

	public:

		Bush(float x, float y, float z, float size);

		void display(float shadowMatrix[16]) override;

		void loadTextures(TextureManager& manager) override;

	};
}