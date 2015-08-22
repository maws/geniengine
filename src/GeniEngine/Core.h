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
		ALLEGRO_DISPLAY* _display;
		ALLEGRO_EVENT_QUEUE* _eventQueue;
		ALLEGRO_TIMER* _timer;

	};
}