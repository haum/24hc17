#include "game__SimonSays.h"
#include "EncodedState.h"
#include <Arduino.h>
#include "AnimManager.h"
#include <cstring>

namespace game {
namespace SimonSays {
	void init_data() {
	}

	bool play(void * data, GameManager::GameInfo & info) {
		Data * d = static_cast <Data*> (data);
		char sequence[8] = "rgbbgry";
		char ans_line[18];
		int ans_line_len;

		int faults = 0;

		info.comm.dump_file("/SimonSays/message");
		
		AnimManager::setSimonSaysParam(sequence, 200);
		
		ans_line_len = info.comm.read(ans_line, sizeof(ans_line)-1);
		
		faults = strcmp (sequence, ans_line);
		
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

