#include "AnimManager.h"
#include <random>


namespace anim
{

	namespace RandomTicking
	{
	
		struct Data
		{
			int divider;
			int wait;
			bool blink;
			std::default_random_engine generator;
			std::uniform_int_distribution<int> distribution(1, 100);
		};

	 	void init_data(void * data, int wait);

		void play(void * data);
	}

}
