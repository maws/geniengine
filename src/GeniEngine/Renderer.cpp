#include "Renderer.hpp"

#include <allegro5\allegro.h>
#include <cmath>

#include "Sprite.hpp"

#include <thread>
#include <functional>

struct AsyncAsset
{
	AsyncAsset(char* fileName)
	{
		bitmap = al_load_bitmap("assets/factory.png");
		abitmap = nullptr;
		std::thread th(&AsyncAsset::Load, this, fileName, std::ref(abitmap));
		th.join();
	}

	void Load(char* fileName, ALLEGRO_BITMAP* bitmap)
	{
		bitmap = al_load_bitmap(fileName);
	}
	
	ALLEGRO_BITMAP* bitmap;
	ALLEGRO_BITMAP* abitmap;
};


namespace GeniEngine
{
	Renderer::Renderer()
	{	
		// Create test asset
		asset_ = new AsyncAsset("assets/factory.png");

		// al_hold_bitmap_demo
		// complete with memory leaks
		auto bitmap = al_load_bitmap("assets/icon64.png");
		root_ = new Node();
		auto master = std::unique_ptr<Sprite>(new Sprite(bitmap));
		master->translate(400.0f, 300.0f);

		auto node = std::unique_ptr<Sprite>(new Sprite(bitmap));
		node->translate(50.0f, 50.0f);
		nodes[0] = master->addChild(std::move(node));

		for (int i = 1; i < NUM_NODES; ++i)
		{
			auto node = std::unique_ptr<Sprite>(new Sprite(bitmap));
			node->scale(1.0f);
			node->translate(15.0f, 15.0f);
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

		al_hold_bitmap_drawing(true);
		root_->draw();
		if (asset_->abitmap == nullptr)
			al_draw_bitmap(asset_->bitmap, 100.0f, 100.0f, 0);
		else
		{
			al_draw_bitmap(asset_->abitmap, 100.0f, 100.0f, 0);
		}
		al_hold_bitmap_drawing(false);
	}
}