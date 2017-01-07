#include "anim__ScrollUp.h"

namespace anim 
{
namespace ScrollUp 
{

	void init_data(void* p, uint8_t r, uint8_t g, uint8_t b) 
	{
		auto d = static_cast<Data*>(p);
		d->divider = 0;
		d->t = 0;
		d->r = r;
		d->g = g;
		d->b = b;
		AnimManager::clear();
	}

	void play(void* p) 
	{
		
		auto d = static_cast<Data*>(p);
		d->t++;
		uint8_t scaler, r, g, b;
		CRGB color;
		
		scaler = sin8(d->t + 128);
		r = scale8(150, scaler);
		g = 0;
		b = scale8(180, scaler);
		color = CRGB(r, g, b);
		AnimManager::setBottomRing(color);
		
		scaler = sin8(d->t+64);
		r = scale8(150, scaler);
		g = 0;
		b = scale8(180, scaler);
		color = CRGB(r, g, b);
		AnimManager::setMiddleRing(color);
		
		scaler = sin8(d->t);
		r = scale8(150, scaler);
		g = 0;
		b = scale8(180, scaler);
		color = CRGB(r, g, b);
		AnimManager::setTopRing(color);		

	}

}
}
