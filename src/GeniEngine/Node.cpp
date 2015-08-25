#include "Node.hpp"

#include <algorithm>

namespace GeniEngine
{
	Node::Node()
	: parent_(nullptr)
	{

	}

	void Node::addChild(NodePtr child)
	{
		child->setParent(this);
		children_.push_back(std::move(child));
	}

	Node::NodePtr Node::removeChild(const Node& node)
	{
		auto find = std::find_if(children_.begin(), children_.end(), [&node](NodePtr& child)
		{
			return child.get() == &node;
		});

		if (find != children_.end())
		{
			NodePtr r = std::move(*find);
			r->setParent(nullptr);
			children_.erase(find);
			return r;
		}

		return nullptr;
	}

	void Node::draw(ALLEGRO_TRANSFORM transform)
	{

	}

	ALLEGRO_TRANSFORM Node::getWorldTransform()
	{
		ALLEGRO_TRANSFORM transform;

		for (Node* p = parent_; p != nullptr; p = p->getParent())
		{
			al_compose_transform(&transform, &p->getLocalTransform());
		}

		return transform;
	}
}