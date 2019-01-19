#include <Components/CameraComponent.h>

#include <Elements/Entity.h>

using namespace Ti;

CameraComponent::CameraComponent(Entity* _owner) : owner(_owner)
{
	centerLocation = Vec3(0, 0, 0);
	eyeLocation = Vec3(1, 1, 0);
	up = Vec3(0, 1, 0);
}


CameraComponent::~CameraComponent()
{
}

void CameraComponent::Update()
{
	counter += 0.01f;
	projection = Mat4::CreatePerspective(80.f, screenSize.x / screenSize.y, 0.01f, 10000.f);
	view = Mat4::CreateLookAt(eyeLocation, centerLocation, up);
	//view = view.CreateRotateY(1.f);
}

void Ti::CameraComponent::Destroy()
{
	delete(this);
}
