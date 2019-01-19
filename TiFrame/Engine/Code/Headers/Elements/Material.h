#pragma once
#include <Elements/Texture.h>
#include <string>
namespace Ti
{
	//! Not used yet.
	class Material
	{
	public:
		Material() {};
		~Material() {};

		std::string filePath;
		const char *data;
	};
}
