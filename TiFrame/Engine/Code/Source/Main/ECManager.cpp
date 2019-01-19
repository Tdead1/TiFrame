#include <Main/ECManager.h>

#include <GameState.h>
#include <Utility/Logger.h>

using namespace Ti;

ECManager::ECManager(GameState * _gs)
{
	gs = _gs;
}
ECManager::~ECManager() 
{ 
}

bool ECManager::Init()
{
	Logger::Print("Entity component manager initialized.", LogType::SUCCESS);
	return true;
}

void ECManager::Update(double dt)
{
	for (unsigned int i = 0; i < entityList.size(); i++)
	{
		entityList[i]->UpdateAllComponents();
	}
}

Entity * ECManager::CreateEntity(std::string name)
{
	Entity *entity = new Entity;
	if (name == " ")
		entity->name = "Entity #" + std::to_string(entityList.size());
	else
		entity->name = name;
	entityList.push_back(entity);
	entity->AddComponent<TransformComponent>();
	return entity;
}

void Ti::ECManager::DestroyEntity(Entity * _entity)
{
	unsigned int size = entityList.size();
	for (unsigned int i = 0; i < size; i++)
	{
		if (entityList[i] == _entity)
		{
			entityList[i]->DeleteAllComponents();
			delete(entityList[i]);
			entityList.erase(entityList.begin() + i);
			break;
		}
	}
}
