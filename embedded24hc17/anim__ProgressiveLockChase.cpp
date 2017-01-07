#include "anim__ProgressiveLockChase.h"
#include "Arduino.h"

namespace anim {
	
	namespace ProgressiveLockChase {

		void init_data(void * p, int bottomWait, int bottomDir, int middleWait, int middleDir, int topWait, int topDir)
		{
			auto d = static_cast<Data*>(p);
			anim::ProgressiveHorizontalChase::init_data(&(d->bottom), 0, bottomDir, bottomWait);
			anim::ProgressiveHorizontalChase::init_data(&(d->middle), 1, middleDir, middleWait);
			anim::ProgressiveHorizontalChase::init_data(&(d->top), 2, topDir, topWait);
			(d->bottom).step = random(0, 3);
			(d->middle).step = random(0, 3);
			(d->top).step = random(0, 3);
			d->unlocked = false;
			AnimManager::clear();
		}

		void play(void* p)
		{
			auto d = static_cast<Data*>(p);
			anim::ProgressiveHorizontalChase::play(&(d->bottom));
			anim::ProgressiveHorizontalChase::play(&(d->middle));
			anim::ProgressiveHorizontalChase::play(&(d->top));

			d->unlocked = d->unlocked or (((d->bottom).step == (d->middle).step) and ((d->top).step == (d->middle).step));
		}

		void increase_bottomWait(void* p)
		{
			auto d = static_cast<Data*>(p);
			anim::ProgressiveHorizontalChase::increase_wait(&(d->bottom));			
		}

		void decrease_bottomWait(void* p)
		{
			auto d = static_cast<Data*>(p);
			anim::ProgressiveHorizontalChase::decrease_wait(&(d->bottom));			
		}
		
		void inverse_bottomDir(void* p)
		{
			auto d = static_cast<Data*>(p);
			anim::ProgressiveHorizontalChase::inverse_dir(&(d->bottom));			
		}

		void increase_middleWait(void* p)
		{
			auto d = static_cast<Data*>(p);
			anim::ProgressiveHorizontalChase::increase_wait(&(d->middle));			
		}

		void decrease_middleWait(void* p)
		{
			auto d = static_cast<Data*>(p);
			anim::ProgressiveHorizontalChase::decrease_wait(&(d->middle));			
		}
		
		void inverse_middleDir(void* p)
		{
			auto d = static_cast<Data*>(p);
			anim::ProgressiveHorizontalChase::inverse_dir(&(d->middle));			
		}

		void increase_topWait(void* p)
		{
			auto d = static_cast<Data*>(p);
			anim::ProgressiveHorizontalChase::increase_wait(&(d->top));			
		}

		void decrease_topWait(void* p)
		{
			auto d = static_cast<Data*>(p);
			anim::ProgressiveHorizontalChase::decrease_wait(&(d->top));			
		}
		
		void inverse_topDir(void* p)
		{
			auto d = static_cast<Data*>(p);
			anim::ProgressiveHorizontalChase::inverse_dir(&(d->top));			
		}		
		
		bool is_unlocked(void* p)
		{
			auto d = static_cast<Data*>(p);
			return d->unlocked;
		}
	}

}
