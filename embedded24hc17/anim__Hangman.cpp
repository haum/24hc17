#include "anim__Hangman.h"

namespace anim
{

	namespace Hangman
	{
		void init_data(void* p, int gallow)
		{
			auto d = static_cast<Data*>(p);

			d->gallow = gallow;
			d->divider = 0;
			AnimManager::clear();
		}
		
		void reset(void* p)
		{
			auto d = static_cast<Data*>(p);
			d->gallow = 8;
		}

		void advance_gallow(void* p)
		{
			auto d = static_cast<Data*>(p);
			d->gallow--;
			play(p);
		}

		void play(void* p)
		{
			const constexpr int wait = 200;
			auto d = static_cast<Data*>(p);
			if (d->divider == wait) {
				
				d->divider = 0;
				
				AnimManager::clear();

				if (d->gallow>1)
				{
					AnimManager::setBottomRing(CRGB::Orange);
					if (d->gallow>3)
					{
						AnimManager::setMiddleRing(CRGB::Orange);
						if (d->gallow>5)
						{
							AnimManager::setTopRing(CRGB::Orange);
							if (d->gallow==8)
							{
								AnimManager::setLed(9, CRGB::Orange);					  
							}
							else if(d->gallow==7)
							{
								AnimManager::setLed(9, CRGB::Red);
							}
						}
						else if(d->gallow==5)
						{
							AnimManager::setTopRing(CRGB::Red);
						}
					}
					else if(d->gallow==3)
					{
						AnimManager::setMiddleRing(CRGB::Red);
					}
				}
				else if (d->gallow==1)
				{
					AnimManager::setBottomRing(CRGB::Red);
				}
			}
			else
			{
				d->divider++;
			}
		}

	}

}