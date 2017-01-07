#include "AnimManager.h"

#ifndef ANIM__HORIZONTAL_CHASE__H
#define ANIM__HORIZONTAL_CHASE__H

namespace anim
{
	
	namespace HorizontalChase
	{
		struct Data
		{
			int divider;
			int wait;
			int step;
			const int* ring;
			int dir;
			int color;
		};

		void init_data(void * data, int ring = 1, int dir = 0, int wait = 20, CRGB color = CRGB::Red);
		
		void play(void * data);

		void increase_wait(void* p);
		void decrease_wait(void* p);
		void inverse_dir(void* p);
	}

}

#endif