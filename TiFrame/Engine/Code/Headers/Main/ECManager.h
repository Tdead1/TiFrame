#pragma once
#include <Elements/Entity.h>
#include <vector>
namespace Ti
{
	class GameState;

	//! Entity component manager. Handels all entities and other related logic. Call init and update to make it work.
	class ECManager
	{
	public:
		ECManager(GameState * _gs);
		~ECManager();

		GameState * gs;

		bool Init();
		void Update(double dt);

		Entity * CreateEntity(std::string _name = " ");
		void DestroyEntity(Entity *_entity);
		std::vector<Entity*> entityList;
	};

}