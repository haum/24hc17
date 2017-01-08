#include "AnimManager.h"

namespace anim 
{
	namespace ScrollUp_Fire 
	{
	
		struct Data 
			{
				int divider;
				int color;
				uint8_t t;
			};
	
		void init_data(void * data);
		void play(void * data);
	}
}
