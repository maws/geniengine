#pragma once

namespace GeniEngine
{
	/// \brief Entity class
	class World;
	class Component;
	class Entity
	{
	public:
		Entity(int id, World* world);

		int getId() { return id_; }
		World* getWorld() { return world_; }

		

	private:
		int id_;
		World* world_;

	};
}