#include "GameManager.h"

namespace game {
	namespace SimonSays {
		struct Data { 
                            int len;
                            int wait;
		};
		void init_data(void * data, int len = 7, int wait = 200);
		bool play(void * data, GameManager::GameInfo & info);
	}
}

