#include "AnimManager.h"
#include <random>


namespace anim
{

	namespace LightStorm
	{
	
		struct Data
		{
			int divider;
			int loopSteps;
			int wait;
		};

	 	void init_data(void* p, int wait = 20, int loopSteps = 3);

		void play(void* p);		
	}

}
