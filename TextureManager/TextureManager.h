// header file for the textureManager class
// Author: jbr 185

#pragma once

#include <GL/freeglut.h>
#include <string>
#include <map>
#include "loadBMP.h"
#include "loadTGA.h"

using namespace std;

namespace Project
{
	// a simple map based class for holding loaded textures to avoid reloading
	class TextureManager
	{
	private:

		string filePath = "Resources/";
		map<string, GLuint> textures = map<string, GLuint>();

	public:

		TextureManager();

		// return s the texture name for a loaded texture or loads it if it hasn't been
		GLuint loadTexture(string fileName, void(*loadFunc)(const string&));

	};
}