#pragma once
#include <Components/Component.h>
#include <Elements/Model.h>
namespace Ti
{
	class DrawManager;

	//! Model component contains a local transform and a model. The mesh component will be used to render an object.
	class ModelComponent : public Component
	{
	public:
		ModelComponent(Entity* _owner, Model* _model, DrawManager* dm);
		~ModelComponent();

		void Update() override;
		void Destroy() override;
		//! transform of the vertices (offset from entity).
		//Mat4 localtransform;
		
		Model *model;
		Entity *owner;
		DrawManager *dm;
	};

}