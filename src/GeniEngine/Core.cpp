#include "Core.hpp"

#include <allegro5\allegro.h>
#include <allegro5\display.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>

#include "Renderer.hpp"
#include "Memory.hpp"

namespace GeniEngine {
	Core::Core()
		: display_(nullptr)
		, event_queue_(nullptr)
		, timer_(nullptr)
		, renderer_(nullptr)
		, debug_font_(nullptr)
	{
			
	}

	Core::~Core()
	{
		Memory::shutdown();
		al_destroy_font(debug_font_);
		al_destroy_display(display_);
		al_destroy_event_queue(event_queue_);
		al_destroy_timer(timer_);
		delete renderer_;
	}

	void Core::init()
	{
		al_init();
		al_init_image_addon();
		al_init_font_addon();
		al_init_ttf_addon();

		Memory::init();

		// NOTE: Allocation test code
		auto p = defaultAllocator().allocate(256);
		//defaultAllocator().deallocate(p);

		debug_font_ = al_load_ttf_font("assets/veramono.ttf", 12.0f, 0);
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
				al_clear_to_color(al_map_rgb(0, 0, 0));
				renderer_->render();

				// NOTE: Demonstration code
				// Renderer should have the responsibility over
				// backbuffer, etc
				ALLEGRO_TRANSFORM t;
				al_identity_transform(&t);
				al_use_transform(&t);
				al_draw_text(debug_font_, al_map_rgb(255, 255, 255), 0.0f, 0.0f, 0, "Default Allocator:");
				al_draw_textf(debug_font_, al_map_rgb(255, 255, 255), 0.0f, 14.0f, 0, "Allocated size: %i bytes", defaultAllocator().getNumAllocatedBytes());
				al_flip_display();
			}
			if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			{
				break;
			}
		}
	}
}