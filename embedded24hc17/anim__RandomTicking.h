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
		};

	 	void init_data(void * data, int wait);

		void play(void * data);
	}

}
