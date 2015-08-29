#include "Sprite.hpp"

#include <allegro5\bitmap.h>

namespace GeniEngine
{
	Sprite::Sprite(const char* path)
	{
		bitmap_ = al_load_bitmap(path);
	}

	Sprite::~Sprite()
	{
		al_destroy_bitmap(bitmap_);
	}

	void Sprite::draw()
	{
		drawChildren();

		al_use_transform(&getWorldTransform());
		al_draw_bitmap(bitmap_, 0.0f - 32.0f, 0.0f - 32.0f, 0);
	}
}