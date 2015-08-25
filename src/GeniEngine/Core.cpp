#include "Core.hpp"

#include <allegro5\allegro.h>
#include <allegro5\display.h>

namespace GeniEngine {
	Core::Core()
		: display_(nullptr)
		, event_queue_(nullptr)
		, timer_(nullptr)
	{
			
	}

	Core::~Core()
	{
		al_destroy_display(display_);
		al_destroy_event_queue(event_queue_);
		al_destroy_timer(timer_);
	}

	void Core::init()
	{
		al_init();
		display_ = al_create_display(800, 600);
		event_queue_ = al_create_event_queue();
		timer_ = al_create_timer(1 / 60.0);
	}

	void Core::run()
	{
		// Main loop
		while (true)
		{
			ALLEGRO_EVENT ev;
			al_wait_for_event(event_queue_, &ev);

			if (ev.type == ALLEGRO_EVENT_TIMER)
			{
				// Tick our game and tell it to draw
			}
			if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			{
				break;
			}
		}
	}
}