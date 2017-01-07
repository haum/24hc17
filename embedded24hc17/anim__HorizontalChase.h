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
			int ring[4];
			int dir;
			int color;
		};

		void init_data(void * data, int ring = 1, int dir = 0, int wait = 20, CRGB color = CRGB::Red);
		
		void play(void * data);
	}

}

#endif