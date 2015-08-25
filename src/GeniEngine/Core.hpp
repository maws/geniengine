#pragma once

struct ALLEGRO_DISPLAY;
struct ALLEGRO_EVENT_QUEUE;
struct ALLEGRO_TIMER;

namespace GeniEngine 
{
	class Core
	{
	public:
		Core();
		~Core();

		void init();
		void run();

	private:
		ALLEGRO_DISPLAY* display_;
		ALLEGRO_EVENT_QUEUE* event_queue_;
		ALLEGRO_TIMER* timer_;

	};
}