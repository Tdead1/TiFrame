#pragma once
#include <Elements/Texture.h>
#include <string>
namespace Ti
{
	//! Loads texture from file.
	class TextureLoader
	{
	public:
		//! Stores data in a new texture object, then returns a pointer to it.
		static Texture *loadTexture(std::string _filePath, std::string _textureName);
	};
}