// header file for the Tree class
// Author: jbr 185

#pragma once

#include "Objects.h"

namespace Project
{
	// a simple pine-like tree
	class Tree : public GLobject, public GLtextured
	{
	private:

		GLuint leafTex;
		GLuint trunkTex;
		float height = 0, size = 0;

	public:

		Tree(float x, float y, float z, float leafHeight, float CanopyHeight);

		void display(float shadowMatrix[16]);

		void loadTextures(TextureManager& manager) override;

	};
}