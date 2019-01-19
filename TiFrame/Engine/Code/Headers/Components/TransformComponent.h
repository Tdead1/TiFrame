#pragma once
#include <Components/Component.h>
#include <Elements/Matrix.h>

namespace Ti
{
	//! The transformcomponent holds the position/rotation/scale of the entity in the world/scene.
	class TransformComponent : public Component
	{
	public:
		TransformComponent(Entity *_owner);
		~TransformComponent();

		Entity* owner;

		//! Global transform in the current world.
		Transform transform;

		Mat4 matrix;

		void Update() override;
		void Destroy() override;
	};

}