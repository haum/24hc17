#include "AnimManager.h"

namespace anim
{
	
	namespace ProgressiveVerticalChase
	{
		struct Data
		{
			int divider;
			int wait;
			const int* ring;
			uint8_t times[7];
			uint8_t dt;
			int step;
			int dir;
			uint8_t r;
			uint8_t g;
			uint8_t b;
			bool done;
		};

		void init_data(void * data, int ring = 1, int wait = 20, CRGB  color = CRGB::Red);
		
		void play(void * data);
	}

}
