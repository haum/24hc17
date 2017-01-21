#include "game__Pong.h"
#include "EncodedState.h"
#include <Arduino.h>
#include <string.h>
#include <stdio.h>

namespace game {
namespace Pong {
	void init_data(void * data) {
		Data * d = static_cast <Data*> (data);
	}

	bool play(void * data, GameManager::GameInfo & info) {
		Data * d = static_cast <Data*> (data);
		char file[50];

		// Prelude
		snprintf(file, sizeof(file), "/Pong/prelude");
		info.comm.dump_file(file);

		// Check answer
		char ans_line[255];
		int ans_line_len = info.comm.read(ans_line, sizeof(ans_line));

		char * ans1 = "Keep on keeping on!";
		char * ans2 = "Monday is an awful way to spend one seventh of your life.";

		bool ok1 = false;
		bool ok2 = false;

		if (ans_line_len == strlen(ans1) && !strncmp(ans1, ans_line, ans_line_len)) {
			ok1 = true;
		}
		if (ans_line_len == strlen(ans2) && !strncmp(ans2, ans_line, ans_line_len)) {
			ok2 = true;
		}

		if (ok1 || ok2) {
			info.comm.write("\nAnd what says the other?\n", 26);
			int ans_line_len = info.comm.read(ans_line, sizeof(ans_line));

			if (ans_line_len == strlen(ans1) && !strncmp(ans1, ans_line, ans_line_len)) {
				ok1 = true;
			}
			if (ans_line_len == strlen(ans2) && !strncmp(ans2, ans_line, ans_line_len)) {
				ok2 = true;
			}
		}

		int faults = 2;
		if (ok1) faults -= 1;
		if (ok2) faults -= 1;

		// Write token
		EncodedState newstate = info.state;
		newstate.faults() = faults;
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
