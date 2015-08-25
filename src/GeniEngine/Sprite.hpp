#pragma once

#include "Node.hpp"

struct ALLEGRO_BITMAP;

namespace GeniEngine
{
	class Sprite : public Node
	{
	public:
		Sprite(const char* path);
		virtual ~Sprite();

		virtual void draw(ALLEGRO_TRANSFORM transform) override;

	private:
		ALLEGRO_BITMAP* bitmap_;

	};
}