#pragma once
#include <Elements/Mesh.h>
#include <string>
namespace Ti
{
	//! Static optimized loader for currently only.obj.
	class MeshLoader
	{
	public:
		//! Loads in an obj from the filepath, and returns the data.
		static Mesh *LoadMesh(std::string _filePath, std::string _modelName);
	};
}