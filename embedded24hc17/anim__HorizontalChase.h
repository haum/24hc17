#include "AnimManager.h"

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
		};

		void init_data(void * data, int ring = 1, int wait = 20);
		
		void play(void * data);
	}

}
