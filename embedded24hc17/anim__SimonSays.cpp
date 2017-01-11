#include "anim__SimonSays.h"

namespace anim {
	
	namespace SimonSays {
		
		void init_data(void* p, char* sequence, int wait) {
			auto d = static_cast<Data*>(p);
			d->divider = 0;
			d->blink = true;
			d->wait = wait;
			d->i = 0;
			strncpy(d->sequence, sequence, 14);
			d->led;
			d->color;
			AnimManager::clear();
		}

		void play(void* p) {
			auto d = static_cast<Data*>(p);
			if (d->sequence[d->i] != '\0') {
				if (d->divider == d->wait/10 && d->blink == true) {
					d->divider = 0;
					d->blink = !d->blink;
					char color = d->sequence[d->i];
					get_led(p, color);
					AnimManager::setLed(d->led, d->color);
				} else if(d->divider ==d->wait/10 && d->blink == false){
					d->divider =0;
					d->blink = !d->blink;
					d->i++;
					AnimManager::clear();
				} else {
					d->divider++;
				}
			}
		}
	
		void get_led(void* p, char color) {
			auto d = static_cast<Data*>(p);
			d->color = color;
			switch (d->color) {
				case 'r':
				case 'R':
					d->led = 2;
					d->color = 0xFF0000;
					break;
				case 'g':
				case 'G':
					d->led = 10;
					d->color = 0x00FF00;
					break;
				case 'b':
				case 'B':
					d->led = 8;
					d->color = 0x0000FF;
					break;
				case 'y':
				case 'Y':
					d->led = 3;
					d->color = 0xFFFF00;
					break;
			}
		}
	}
}
