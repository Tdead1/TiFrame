#pragma once

#include <Elements/Material.h>
#include <Elements/Mesh.h>

namespace Ti
{
	//! The model contains a reference to the component, vertices and indices for drawing.
	class Model
	{
	public:
		Model() {};
		~Model() {};

		Material *material;
		Texture *texture;
		Mesh *mesh;
	};
}