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

		Node* addChild(NodePtr child);
		NodePtr removeChild(const Node& node);

		Node* getParent() { return parent_; }
		void setParent(Node* parent) { parent_ = parent; }

		virtual void draw();

		ALLEGRO_TRANSFORM getWorldTransform();
		ALLEGRO_TRANSFORM& getLocalTransform() { return local_transform_; }

		void translate(float x, float y) { x_ = x; y_ = y; }
		void rotate(float theta) { theta_ = theta; }
		void scale(float scale) { scale_ = scale; }
		float x_, y_, theta_, scale_;

	protected:
		virtual void drawChildren();
		Node* parent_;
		std::vector<NodePtr> children_;
		ALLEGRO_TRANSFORM local_transform_;
	};
}