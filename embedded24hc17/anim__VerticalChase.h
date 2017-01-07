#include "AnimManager.h"

namespace anim
{
	
	namespace VerticalChase
	{
		struct Data
		{
			int divider;
			int wait;
			int step;
			int ring[7];
			int dir;
		};

		void init_data(void * data, int ring = 1, int wait = 20);
		
		void play(void * data);
	}

}
