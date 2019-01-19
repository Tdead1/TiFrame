#include <Components/TransformComponent.h>
using namespace Ti;


TransformComponent::TransformComponent(Entity *_owner) : owner(_owner)
{
	transform = Transform(Vec3(0, 0, 0), Vec3(0, 0, 0), Vec3(1, 1, 1));
}


TransformComponent::~TransformComponent()
{
}

void TransformComponent::Update()
{
	matrix = Mat4::CreateMatrix(transform.position, transform.rotation, transform.scale);
}

void Ti::TransformComponent::Destroy()
{
	delete(this);
}
