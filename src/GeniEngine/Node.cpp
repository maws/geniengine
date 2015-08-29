#include "Node.hpp"

#include <algorithm>

namespace GeniEngine
{
	Node::Node()
	: parent_(nullptr)
	, x_(0.0f)
	, y_(0.0f)
	, theta_(0.0f)
	, scale_(1.0f)
	{
		al_identity_transform(&local_transform_);
	}

	Node* Node::addChild(NodePtr child)
	{
		auto ref = child.get();
		child->setParent(this);
		children_.push_back(std::move(child));
		return ref;
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

	void Node::draw()
	{
		drawChildren();
	}

	void Node::drawChildren()
	{
		for (auto& i : children_)
		{
			i->draw();
		}
	}

	ALLEGRO_TRANSFORM Node::getWorldTransform()
	{
		al_build_transform(&local_transform_, x_, y_, scale_, scale_, theta_);
		ALLEGRO_TRANSFORM world_transform = local_transform_;
		for (Node* p = parent_; p != nullptr; p = p->getParent())
		{
			al_compose_transform(&world_transform, &p->getLocalTransform());
		}

		return world_transform;
	}
}