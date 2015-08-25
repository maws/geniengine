#pragma once

#include <vector>
#include <memory>

namespace GeniEngine
{
	class Node
	{
	public:
		using NodePtr = std::unique_ptr < Node > ;

		Node();

		void addChild(NodePtr child);
		NodePtr removeChild(const Node& node);

		Node* getParent() { return parent_; }
		void setParent(Node* parent) { parent_ = parent; }

	private:
		Node* parent_;
		std::vector<NodePtr> children_;
	};
}