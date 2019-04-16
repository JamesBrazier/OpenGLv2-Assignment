#include "TextureManager.h"

namespace Project {

	TextureManager::TextureManager()
	{ }

	GLuint TextureManager::loadTexture(string fileName, void(*loadFunc)(const string &))
	{
		try {
			return textures.at(fileName);
		} catch (out_of_range err) {
			GLuint texture;

			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			loadFunc(filePath + fileName);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			textures[fileName] = texture;

			return texture;
		}
	}
}
