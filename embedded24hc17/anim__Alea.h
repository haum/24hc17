#include "AnimManager.h"
#include <random>


namespace anim
{

	namespace Alea
	{
	
		struct Data
		{
			int divider;
			int led;
			std::default_random_engine generator;
			std::uniform_int_distribution<int> distribution(0,12);
		};

	 	void init_data(void * data);

		void play(void * data);
	}

}
