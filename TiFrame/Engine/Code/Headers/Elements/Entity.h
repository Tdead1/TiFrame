#pragma once
#include <Components\Component.h>
#include <Components\TransformComponent.h>
#include <Components\ModelComponent.h>
#include <Components\CameraComponent.h>

#include <vector>
namespace Ti
{
	//! The entity class is the base for any gameobject/entity that has components. Header only.
	class Entity
	{
	public:
		Entity() {};
		~Entity() {
			DeleteAllComponents();
		};

		//! Runs every frame and updates all components in the component list.
		void UpdateAllComponents()
		{
			for (unsigned int i = 0; i < componentList.size(); i++)
			{
				componentList[i]->Update();
			}
			return;
		};

		void DeleteComponent(Component* component) {
			for (unsigned int i = 0; i < componentList.size(); i++)
			{
				if (component == componentList[i])
				{
					component->Destroy();
					componentList.erase(componentList.begin() + i);
					break;
				}
			}
		}

		void DeleteAllComponents()
		{
			unsigned int amount = componentList.size();
			for (unsigned int i = 0; i < amount; i++)
			{
				componentList[0]->Destroy();
				componentList.erase(componentList.begin());
			}
		}

		//! Correct usage example: entity.AddComponent<TransformComponent>(); Adds a component of the input type to the entity.
		/** Uses TArgs as template arguments. Adding arguments will send them through to the constructor.		*/
		template<typename TComponent, typename ... TArgs>
		TComponent* AddComponent(TArgs ... args)
		{
			TComponent *tcomponent = new TComponent(this, args...);
			componentList.push_back(tcomponent);
			return tcomponent;
		};

		//! Correct usage example: entity.GetComponent<TransformComponent>(); Returns the first transform component added to this entity.
		template<class TComponent = typename std::enable_if<std::is_base_of<Component, TComponent>::value>::type>
		TComponent* GetComponent()
		{
			TComponent* currentComponent;
			for (unsigned int i = 0; i < componentList.size(); i++)
			{
				currentComponent = dynamic_cast<TComponent*>(componentList[i]);
				if (currentComponent != nullptr)
					return currentComponent;
			}
			return nullptr;
		};

		//! The list of components that the entity currenlty has.
		std::vector<Component*> componentList;

		std::string name;
		char namebuffer[64];
	};
}

