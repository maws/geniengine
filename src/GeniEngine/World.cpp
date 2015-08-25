#include "World.hpp"

#include <assert.h>

namespace GeniEngine
{
	World::World()
		: next_id_(0)
		, total_created_(0)
		, total_removed_(0)
		, component_batches_(Component::NUM_TYPES)
		, systems_(System::NUM_TYPES)
	{

	}

	World::~World()
	{

	}

	void World::tick()
	{
		for (int i = 0; i < systems_.getCapacity(); ++i)
		{
			if (systems_.get(i) != nullptr)
			{
				systems_.get(i)->process();
			}
		}
	}

	Entity& World::createEntity()
	{
		Entity* entity = nullptr;
		if (free_entities_.isEmpty())
		{
			entity = new Entity(next_id_++, this);
			entities_.set(entity->getId(), entity);
		}
		else
		{
			// Re use freed entity
			entity = free_entities_.removeLast();
		}

		++total_created_;
		return *entity;
	}

	void World::removeEntity(Entity& entity)
	{
		removeComponents(entity);
		entities_.set(entity.getId(), nullptr);
		free_entities_.add(&entity);
		++total_removed_;
	}

	Entity& World::getEntity(int id)
	{
		return *entities_.get(id);
	}

	void World::addComponent(Entity& entity, Component* component)
	{
		// If component id exceeds number different types in batches
		// resize the container to fit the new types
		if (component->getType() >= component_batches_.getCapacity())
		{
			component_batches_.set(component->getType(), nullptr);
		}

		// Is there a batch already created of this type?
		// If not create a fresh batch in its place
		ComponentBatch* batch = component_batches_.get(component->getType());
		if (batch == nullptr)
		{
			batch = new ComponentBatch();
			component_batches_.set(component->getType(), batch);
		}
		else
		{
			// Check if entity already has this component
			// TODO: Replace old with new instead
			assert(batch->get(entity.getId()) == nullptr);
		}

		// Set component for this entity
		batch->set(entity.getId(), component);
	}

	void World::removeComponent(Entity& entity, Component::Type type)
	{
		auto batch = component_batches_.get(type);
		delete batch->get(entity.getId());
		batch->set(entity.getId(), nullptr);
	}

	void World::removeComponents(Entity& entity)
	{
		for (int i = 0; i < component_batches_.getCapacity(); i++)
		{
			auto batch = component_batches_.get(i);

			// If the entity got component of current type
			if (batch != nullptr && batch->get(entity.getId()) != nullptr)
			{
				// Delete and reset it
				auto component = batch->get(entity.getId());
				delete batch->get(entity.getId());
				batch->set(entity.getId(), nullptr);
			}
		}
	}

	void World::addSystem(System* system)
	{
		systems_.set(system->getType(), system);
	}

	void World::removeSystem(System& system)
	{
		delete systems_.get(system.getType());
		systems_.set(system.getType(), nullptr);
	}

	Component* World::getComponent(Entity& entity, Component::Type type)
	{
		ComponentBatch* batch = component_batches_.get(type);
		if (batch != nullptr)
		{
			return batch->get(entity.getId());
		}

		return nullptr;
	}
}