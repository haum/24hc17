#include "anim__ScrollUp_Fire.h"

namespace anim 
{
namespace ScrollUp_Fire 
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
		
		scaler = sin8(d->t + 128);
		r = scale8(255, scaler);
		g = scale8(69, scaler);
		b = 0;
		color = CRGB(r, g, b);
		AnimManager::setBottomRing(color);
		
		scaler = sin8(d->t+64);
		r = scale8(255, scaler);
		g = scale8(165, scaler);
		b = 0;
		color = CRGB(r, g, b);
		AnimManager::setMiddleRing(color);
		
		scaler = sin8(d->t);
		r = scale8(255, scaler);
		g = scale8(215, scaler);
		b = 0;		
		color = CRGB(r, g, b);
		AnimManager::setTopRing(color);		

	}

}
}
