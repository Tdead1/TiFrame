#pragma once
#include <Components/Component.h>
#include <Elements/Matrix.h>

namespace Ti
{
	//! Camera component, can be added to any entity. Set the maincamera var in the drawmanager to activate the current camera.
	class CameraComponent :	public Component
	{
	public:
		CameraComponent(Entity* _owner);
		~CameraComponent();

		Entity* owner;

		Vec2 screenSize;

		Vec3 centerLocation;
		Vec3 eyeLocation;
		Vec3 up;

		//! View matrix to be used by drawmanager.
		Mat4 view;
		//! Projection matrix to be used by drawmanager.
		Mat4 projection;


		void Update() override;
		void Destroy() override;
		//! Temporary variables
		float counter = 0.5f;
	};
}

