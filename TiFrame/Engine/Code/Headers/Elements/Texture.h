#pragma once
#include <string>
namespace Ti
{
	//! Not used yet.
	class Texture
	{
	public:
		Texture() {};
		~Texture() {};

		std::string filePath;
		unsigned char* data;
		int width, height;
		int channels;
	};
}

