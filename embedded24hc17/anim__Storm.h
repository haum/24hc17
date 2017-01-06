#include "AnimManager.h"
#include <random>


namespace anim
{

	namespace Storm
	{
	
		struct Data
		{
			int divider;
			int loopSteps;
			int wait;
			int step;
			int leds[13];
		};

	 	void init_data(void* p, int wait = 7, int loopSteps = 3);

		void play(void* p);		
	}

}
