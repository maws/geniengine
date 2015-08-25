#pragma once

#include <vector>

#include "Utils\ExpandingArray.hpp"
#include "ECS\Entity.hpp"
#include "ECS\System.hpp"
#include "ECS\Component.hpp"

namespace GeniEngine
{
	class World
	{
	public:
		typedef Utils::ExpandingArray<Entity*> EntityArray;
		typedef Utils::ExpandingArray<System*> SystemArray;
		typedef Utils::ExpandingArray<Component*> ComponentBatch;
		typedef Utils::ExpandingArray<Utils::ExpandingArray<Component*>*> ComponentBatches;

		World();
		~World();

		void tick();

		Entity& createEntity();
		Entity& getEntity(int id);
		void removeEntity(Entity& entity);
		
		void addComponent(Entity& entity, Component* component);
		Component* getComponent(Entity& entity, Component::Type type);
		void removeComponent(Entity& entity, Component::Type type);
		void removeComponents(Entity& entity);

		void addSystem(System* system);
		void removeSystem(System& system);

		template<typename T>
		T* getComponent(Entity& entity)
		{
			auto batch = getComponentBatch<T>();
			auto component = (T*)batch->get(entity.getId());
			return component;
		}

		template<typename T>
		Utils::ExpandingArray<T*>* getComponentBatch()
		{
			auto batch = (Utils::ExpandingArray<T*>*)component_batches_.get(T::getType());
			return batch;
		}

	private:
		int next_id_;
		int total_created_;
		int total_removed_;
		SystemArray systems_;
		EntityArray entities_;
		EntityArray free_entities_;
		ComponentBatches component_batches_;
	};
}