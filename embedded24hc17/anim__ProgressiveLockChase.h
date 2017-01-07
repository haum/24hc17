#include "AnimManager.h"
#include "anim__ProgressiveHorizontalChase.h"

namespace anim
{
	
	namespace ProgressiveLockChase
	{

		struct Data
		{
			anim::ProgressiveHorizontalChase::Data bottom;
			anim::ProgressiveHorizontalChase::Data middle;
			anim::ProgressiveHorizontalChase::Data top;
			bool unlocked;
		};

		void init_data(void * p, int bottomWait, int bottomDir, int middleWait, int middleDir, int topWait, int topDir);
		
		void play(void * p);

		void increase_bottomWait(void* p);
		void decrease_bottomWait(void* p);
		void inverse_bottomDir(void* p);

		void increase_middleWait(void* p);
		void decrease_middleWait(void* p);
		void inverse_middleDir(void* p);

		void increase_topWait(void* p);
		void decrease_topWait(void* p);
		void inverse_topDir(void* p);

		bool is_unlocked(void* p);
	}

}
