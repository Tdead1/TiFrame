#include <Components/Component.h>
#include <Elements/Entity.h>
using namespace Ti;
Component::Component()
{
	owner = nullptr;
}

Component::Component(Entity* _owner)
{
	owner = _owner;
}
Component::~Component()
{
}

void Component::Update()
{

}

void Ti::Component::Destroy()
{
	delete(this);
}
