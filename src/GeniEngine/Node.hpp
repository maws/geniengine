#pragma once

#include <vector>
#include <memory>
#include <allegro5\allegro.h>

namespace GeniEngine
{
	class Node
	{
	public:
		using NodePtr = std::unique_ptr < Node > ;

		Node();
		virtual ~Node() {}

		void addChild(NodePtr child);
		NodePtr removeChild(const Node& node);

		Node* getParent() { return parent_; }
		void setParent(Node* parent) { parent_ = parent; }

		virtual void draw(ALLEGRO_TRANSFORM transform);

		ALLEGRO_TRANSFORM getWorldTransform();
		ALLEGRO_TRANSFORM getLocalTransform() { return local_transform_; }
	private:
		Node* parent_;
		std::vector<NodePtr> children_;
		ALLEGRO_TRANSFORM local_transform_;
	};
}