#include "anim__TestsLVA.h"

namespace anim 
{
	namespace TestsLVA 
	{

		void init_data(void* p) 
		{
			auto d = static_cast<Data*>(p);
			d->divider = 0;
			d->t = 0;
			AnimManager::clear();
		}

		void play(void* p) 
		{
			
			auto d = static_cast<Data*>(p);
			d->t++;
			uint8_t scaler, r, g, b;
			CRGB color;
			
			scaler = triwave8(d->t);
			r = scaler;
			g = scaler;
			b = scaler;
			color = CRGB(r, g, b);
			AnimManager::setTopRing(color);
			
			scaler = triwave8(d->t + 64);
			r = scale8(150, scaler);
			g = 0;
			b = 0;
			color = CRGB(r, g, b);
			AnimManager::setMiddleRing(color);
			
		}
	}
}
