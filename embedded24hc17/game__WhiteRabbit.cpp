#include "game__WhiteRabbit.h"
#include "EncodedState.h"
#include <cstring>
#include <FS.h>
#include <Arduino.h>

namespace game {
namespace WhiteRabbit {
	void init_data(void * data, int min, const char * const name) {
		Data * d = static_cast <Data*> (data);
		d->min = min;
		size_t n = strlen(name);
		if (n > sizeof(d->name)-1)
			n = sizeof(d->name)-1;
		memcpy(d->name, name, n);
		d->name[n] = 0;
		d->name[sizeof(d->name)-1] = 0;
	}

	bool play(void * data, GameManager::GameInfo & info) {
		Data * d = static_cast <Data*> (data);
		char file[sizeof(d->name)+50];

		// Get good answer
		snprintf(file, sizeof(file), "/%s/answer", d->name);
		File f = SPIFFS.open(file, "r");
		char goodans_buffer[255];
		int goodans_buffer_len = f.readBytes(&goodans_buffer[goodans_buffer_len], sizeof(goodans_buffer));
		f.close();

		// Prelude
		snprintf(file, sizeof(file), "/%s/prelude", d->name);
		info.comm.dump_file(file);

		char ans_line[255];
		int ans_line_len;
		bool run = true;
		int jumps = 0;
		while (run) {
			info.comm.write("\nGo to: ", 8);
			ans_line_len = info.comm.read(ans_line, sizeof(ans_line)-1);
			if (ans_line_len > 4) break; // Answer found
			jumps++;

			// Find new node
			ans_line[ans_line_len] = 0; // since snprintf has no support for "%.*s"
			snprintf(file, sizeof(file), "/%s/node_%s", d->name, ans_line);
			File f = SPIFFS.open(file, "r");
			if (f) {
				// Display node
				f.close();
				info.comm.dump_file(file);
			} else {
				// List catches
				snprintf(file, sizeof(file), "/%s/", d->name);
				Dir dir = SPIFFS.openDir(file);
				snprintf(file, sizeof(file), "/%s/catch", d->name);
				int nb_catches = 0;
				int len = strlen(file);
				while (dir.next()) {
					if (!strncmp(dir.fileName().c_str(), file, len))
						nb_catches++;
				}
				// Display one catch
				int choice = random(nb_catches)+1;
				snprintf(file, sizeof(file), "/%s/catch%d", d->name, choice);
				info.comm.dump_file(file);
			}
		}

		// Check answer
		int faults = 0;
		if (ans_line_len != goodans_buffer_len) {
			faults = 1;
		} else if (strncmp(ans_line, goodans_buffer, ans_line_len)) {
			faults = 2;
		} else if (jumps < d->min) {
			faults = 3;
		}

		// Write token
		EncodedState newstate = info.state;
		newstate.faults() = faults;
		newstate.finalsuccess() = !faults;
		newstate.direction() = 1;
		newstate.sentence() = random(32);
		char token[22];
		newstate.toString(token);
		info.comm.write("\nToken: ", 8);
		info.comm.write(token, sizeof(token));
		info.comm.write("\n", 1);
		return true;
	}
}
}
