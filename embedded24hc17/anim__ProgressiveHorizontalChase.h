#include "AnimManager.h"

#ifndef ANIM__PROGRESSIVE_HORIZONTAL_CHASE__H
#define ANIM__POGRESSIVE_HORIZONTAL_CHASE__H

namespace anim
{
	
	namespace ProgressiveHorizontalChase
	{
		struct Data
		{
			int divider;
			int wait;
			int step;
			const int* ring;
			int dir;
			uint8_t times[4];
			uint8_t dt;
			uint8_t r;
			uint8_t g;
			uint8_t b;
			bool done;
		};

		void init_data(void * data, int ring = 1, int dir = 0, int wait = 20, CRGB color = CRGB::Red);
		
		void play(void * data);

		void increase_wait(void* p);
		void decrease_wait(void* p);
		void inverse_dir(void* p);
	}

}

#endif