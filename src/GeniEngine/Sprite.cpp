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

	void Sprite::draw(ALLEGRO_TRANSFORM transform)
	{
		al_use_transform(&transform);

		al_draw_bitmap(bitmap_, 0.0f, 0.0f, 0);
	}
}