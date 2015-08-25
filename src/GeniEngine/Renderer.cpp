#include "Renderer.hpp"

#include <allegro5\allegro.h>

namespace GeniEngine
{
	Renderer::Renderer()
	{

	}

	Renderer::~Renderer()
	{

	}

	void Renderer::render()
	{
		al_clear_to_color(al_map_rgb(0, 0, 0));

		ALLEGRO_TRANSFORM transform;
		al_identity_transform(&transform);

		al_flip_display();
	}
}