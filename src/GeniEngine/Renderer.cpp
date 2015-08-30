#include "Renderer.hpp"

#include <allegro5\allegro.h>
#include <cmath>

#include "Sprite.hpp"

namespace GeniEngine
{
	Renderer::Renderer()
	{	
		root_ = new Node();
		auto master = std::unique_ptr<Sprite>(new Sprite("assets/icon64.png"));
		master->translate(400.0f, 300.0f);

		auto node = std::unique_ptr<Sprite>(new Sprite("assets/icon64.png"));
		node->translate(50.0f, 50.0f);
		nodes[0] = master->addChild(std::move(node));

		for (int i = 1; i < NUM_NODES; ++i)
		{
			auto node = std::unique_ptr<Sprite>(new Sprite("assets/icon64.png"));
			node->scale(.8f);
			node->translate(30.0f, 30.0f);
			nodes[i] = nodes[i-1]->addChild(std::move(node));
		}

		master_ = root_->addChild(std::move(master));
	}

	Renderer::~Renderer()
	{

	}

	void Renderer::render()
	{
		static float rotation = 0.0f;
		rotation += 0.01f;
		master_->rotate(rotation);

		for (int i = 0; i < NUM_NODES; ++i)
		{
			nodes[i]->rotate(rotation);
		}

		root_->draw();
	}
}