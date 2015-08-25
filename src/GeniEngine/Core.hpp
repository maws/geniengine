#pragma once

struct ALLEGRO_DISPLAY;
struct ALLEGRO_EVENT_QUEUE;
struct ALLEGRO_TIMER;

namespace GeniEngine 
{
	class Renderer;
	class Core
	{
	public:
		Core();
		~Core();

		void init();
		void run();

	private:
		Renderer* renderer_;
		ALLEGRO_DISPLAY* display_;
		ALLEGRO_EVENT_QUEUE* event_queue_;
		ALLEGRO_TIMER* timer_;

	};
}