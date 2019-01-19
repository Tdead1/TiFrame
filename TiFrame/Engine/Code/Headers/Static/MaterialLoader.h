#pragma once
#include <Elements/Material.h>

namespace Ti
{
	//! Not used yet.
	class MaterialLoader
	{
	public:
		static Material *LoadMaterial(std::string _filePath, std::string _modelName);
	};
}