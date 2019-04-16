// header file for the skyBox class
// Author: jbr 185

#pragma once

#include "MyExtentions.h"

namespace Project
{
	// the object class for the world skybox
	class SkyBox : public GLobject, public GLtextured
	{
	private:

		GLuint dayTex; // the texture for day
		GLuint nightTex; // the texture for night
		GLuint currentTex;

	public:

		SkyBox();

		void display(float shadowMatrix[16]) override;

		void loadTextures(TextureManager& manager) override;

		void setDay(bool state);

	};
}