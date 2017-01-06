#include "AnimManager.h"

namespace anim 
{
	namespace Rings 
	{
		struct Data 
		{
			int divider;
			uint8_t t;
		};
	
		void init_data(void * data);
		void play(void * data);
	}
}
