#include "AnimManager.h"
#include <random>


namespace anim
{

	namespace Fiesta
	{
	
		struct Data
		{
			int divider;
		};

	 	void init_data(void * data);

		void play(void * data);
	}

	CRGB *colors;

}
