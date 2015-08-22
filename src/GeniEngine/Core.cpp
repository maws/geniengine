#include "Core.h"

#include <allegro5\allegro.h>
#include <allegro5\display.h>

namespace GeniEngine {
	Core::Core()
		: _display(nullptr)
		, _eventQueue(nullptr)
		, _timer(nullptr)
	{
			
	}

	Core::~Core()
	{
		al_destroy_display(_display);
		al_destroy_event_queue(_eventQueue);
		al_destroy_timer(_timer);
	}

	void Core::init()
	{
		al_init();
		_display = al_create_display(800, 600);
		_eventQueue = al_create_event_queue();
		_timer = al_create_timer(1 / 60.0);
	}

	void Core::run()
	{
		// Main loop
		while (true)
		{
			ALLEGRO_EVENT ev;
			al_wait_for_event(_eventQueue, &ev);

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