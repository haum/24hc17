#include "AnimManager.h"
#include <random>


namespace anim
{

	namespace Fiesta
	{
	
		struct Data
		{
			int divider;
			int loopSteps;
			int wait;
		};

	 	void init_data(void * data, int wait, int loopSteps);

		void play(void * data);		
	}

}
