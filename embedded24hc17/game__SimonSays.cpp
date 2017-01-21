#include "game__SimonSays.h"
#include "EncodedState.h"
#include <Arduino.h>
#include "AnimManager.h"
#include <cstring>

namespace game {
namespace SimonSays {
		
	const constexpr int n = 16;

	void init_data(void * data, int len, int wait) {
		Data * d = static_cast <Data*> (data);
		if(len > 0 and len < n) {
			d->len = len;
		} else {
			d->len = n-1;
		}
		d->wait = wait;
	}

	bool play(void * data, GameManager::GameInfo & info) {
		Data * d = static_cast <Data*> (data);

		char sequence[n];

		for (int i = 0; i<d->len; i++) {
			switch(random(4)) {
				case 0:
					sequence[i] = 'r';
					break;
				case 1:
					sequence[i] = 'g';
					break;
				case 2:
					sequence[i] = 'b';
					break;
				default:
					sequence[i] = 'y';
			}
		}
		sequence[d->len] = '\0';

		char ans_line[2 * n];
		int ans_line_len;

		int faults = 0;

		info.comm.dump_file("/SimonSays/message");
		
		AnimManager::setSimonSaysParam(sequence, d->wait);
		
		ans_line_len = info.comm.read(ans_line, sizeof(ans_line)-1);

		if (ans_line_len == d->len) {
			faults = strncmp (sequence, ans_line, d->len);
		} else {
			faults = 1;
		}
		
		//Write Token
		EncodedState newstate = info.state;
		newstate.faults() = (faults != 0);
		newstate.finalsuccess() = !faults;
		newstate.direction() = 1;
		newstate.sentence() = random(32);
		char token[22];
		newstate.toString(token);
		info.comm.write("\nVitellius: ", 12);
		info.comm.write(token, sizeof(token));
		info.comm.write("\n", 1);
		return true;
		
	}
}
}

