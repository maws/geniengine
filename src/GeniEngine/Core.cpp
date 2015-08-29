#include "Core.hpp"

#include <allegro5\allegro.h>
#include <allegro5\display.h>
#include <allegro5\allegro_image.h>

#include "Renderer.hpp"

namespace GeniEngine {
	Core::Core()
		: display_(nullptr)
		, event_queue_(nullptr)
		, timer_(nullptr)
		, renderer_(nullptr)
	{
			
	}

	Core::~Core()
	{
		al_destroy_display(display_);
		al_destroy_event_queue(event_queue_);
		al_destroy_timer(timer_);
		delete renderer_;
	}

	void Core::init()
	{
		al_init();
		al_init_image_addon();

		display_ = al_create_display(800, 600);
		event_queue_ = al_create_event_queue();
		timer_ = al_create_timer(1 / 60.0);
		renderer_ = new Renderer();

		al_register_event_source(event_queue_, al_get_timer_event_source(timer_));
		al_register_event_source(event_queue_, al_get_display_event_source(display_));
	}

	void Core::run()
	{
		// Main loop
		al_start_timer(timer_);
		while (true)
		{
			ALLEGRO_EVENT ev;
			al_wait_for_event(event_queue_, &ev);

			if (ev.type == ALLEGRO_EVENT_TIMER)
			{
				// TODO: Tick our game and tell it to draw
				renderer_->render();
			}
			if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			{
				break;
			}
		}
	}
}