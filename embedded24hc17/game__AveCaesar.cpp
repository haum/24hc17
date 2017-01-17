#include "game__AveCaesar.h"
#include "EncodedState.h"
#include <Arduino.h>

namespace game {
namespace AveCaesar {
	void init_data(void * data) {
		Data * d = static_cast <Data*> (data);
		d->faults = 0;
	}

	bool play(void * data, GameManager::GameInfo & info) {
		Data * d = static_cast <Data*> (data);

		info.comm.dump_file("/AveCaesar/message");

		char ans[255];
		int len = info.comm.read(ans, sizeof(ans));
		if (len == 3 && ans[0] == 'a' && ans[1] == 'v' && ans[2] == 'e') {
			EncodedState newstate;
			newstate.faults() = d->faults;
			newstate.riddle() = 0;
			newstate.finalsuccess() = 1;
			newstate.direction() = 1;
			newstate.sentence() = random(32);
			char token[22];
			newstate.toString(token);
			info.comm.write("\nAve! Here is the next message to Nero:\n", 40);
			info.comm.write(token, sizeof(token));
			info.comm.write("\n", 1);
			return true;
		} else {
			d->faults++;
		}
		return false;
	}
}
}
