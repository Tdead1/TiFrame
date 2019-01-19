#include <Static/TextureLoader.h>


#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

using namespace Ti;

Texture *TextureLoader::loadTexture(std::string _filePath, std::string _textureName)
{
	Texture* texture = new Texture;
	texture->filePath = _filePath;

	unsigned char* data = stbi_load(_filePath.c_str(), &texture->width, &texture->height, &texture->channels, 0);

	texture->filePath = _filePath;
	texture->data = data;

	return texture;
}
