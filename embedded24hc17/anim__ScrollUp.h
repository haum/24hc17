#include "AnimManager.h"

namespace anim 
{
	namespace ScrollUp 
	{
	
		struct Data 
			{
				int divider;
				int color;
				uint8_t t;
				uint8_t r;
				uint8_t g;
				uint8_t b;
			};
	
		void init_data(void * data, uint8_t r, uint8_t g, uint8_t b);
		void play(void * data);
	}
}
