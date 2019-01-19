#pragma once
#include <string>
#include <vector>

namespace Ti
{
	//! Contains the data needed for drawing. Will be sent as is to the GPU.
	struct Vertex
	{
		float pos[3];
		float tex[2];
		float nor[3];
	};


	//! Not used yet.
	class Mesh
	{
	public:
		Mesh() {};
		~Mesh() {};

		std::string filePath;
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
	};


}