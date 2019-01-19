#include <Components/ModelComponent.h>

#include <Main/DrawManager.h>

using namespace Ti;

ModelComponent::ModelComponent(Entity* _owner, Model *_model, DrawManager *_dm) : owner(_owner), model(_model), dm(_dm)
{
	dm->modelList.push_back(this);
	dm->modelAmount++;
	if (owner->GetComponent<TransformComponent>() == nullptr)
	{
		owner->AddComponent<TransformComponent>();
	}
	//localtransform = Mat4();
}


ModelComponent::~ModelComponent()
{
}

void ModelComponent::Update()
{
}

void Ti::ModelComponent::Destroy()
{
	dm->RemoveModel(this);
	delete(this);
}
