#pragma once

#include "Node.hpp"
#include "Sprite.hpp"

#define NUM_NODES 1500

namespace GeniEngine 
{
	class Renderer
	{
	public:
		Renderer();
		~Renderer();

		void render();

	private:
		Node* root_;

		Node* master_;
		Node* slave_;

		Node* nodes[NUM_NODES];

	};
}