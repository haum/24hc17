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
		};

	 	void init_data(void * data);

		void play(void * data);
	}

}
