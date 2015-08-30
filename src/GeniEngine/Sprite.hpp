#pragma once

#include "Node.hpp"

struct ALLEGRO_BITMAP;

namespace GeniEngine
{
	class Sprite : public Node
	{
	public:
		using SpritePtr = std::unique_ptr < Sprite > ;
		Sprite(const char* path);
		Sprite(ALLEGRO_BITMAP* bitmap);
		virtual ~Sprite();

		virtual void draw() override;

	protected:
		

	private:
		ALLEGRO_BITMAP* bitmap_;

	};
}