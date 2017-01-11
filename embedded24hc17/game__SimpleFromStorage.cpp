#include "game__SimpleFromStorage.h"
#include "EncodedState.h"
#include <cstring>
#include <FS.h>

namespace game {
namespace SimpleFromStorage {
	void init_data(void * data, const char * const name) {
		Data * d = static_cast <Data*> (data);
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

		// Prelude
		snprintf(file, sizeof(file), "/%s/prelude", d->name);
		info.comm.dump_file(file);

		// List enigmas
		snprintf(file, sizeof(file), "/%s/", d->name);
		Dir dir = SPIFFS.openDir(file);
		snprintf(file, sizeof(file), "/%s/enigma", d->name);
		int nb_enigmas = 0;
		int enigma_len = strlen(file);
		while (dir.next()) {
			if (!strncmp(dir.fileName().c_str(), file, enigma_len))
				nb_enigmas++;
		}

		// Display enigma
		int choice = random(nb_enigmas)+1;
		snprintf(file, sizeof(file), "/%s/enigma%d", d->name, choice);
		info.comm.dump_file(file);

		// Check answer
		info.comm.write("\nAnswer: ", 9);
		snprintf(file, sizeof(file), "/%s/answer%d", d->name, choice);
		int fault = 0;
		char ans_line[255];
		char goodans_line[255];
		char goodans_buffer[255];
		int goodans_buffer_len = 0;
		File f = SPIFFS.open(file, "r");
		bool run = true;
		if (f) while (run) {
			int ans_line_len = info.comm.read(ans_line, sizeof(ans_line));
			int len = f.readBytes(&goodans_buffer[goodans_buffer_len], sizeof(goodans_buffer) - goodans_buffer_len);
			if (len < 0)
				run = false;
			else
				goodans_buffer_len += len;
			int goodans_line_len = 0;
			while (goodans_line_len < goodans_buffer_len) {
				char r = goodans_buffer[goodans_line_len];
				if (r != '\n') {
					goodans_line[goodans_line_len] = r;
					goodans_line_len++;
				} else {
					break;
				}
			}
			goodans_buffer_len -= goodans_line_len + 1;
			memcpy(goodans_buffer, &goodans_buffer[goodans_line_len + 1], goodans_buffer_len);

			if (ans_line_len != goodans_line_len) {
				fault = 1;
				run = false;
			} else if (goodans_buffer_len == 0) {
				run = false;
			} else if (strncmp(ans_line, goodans_line, ans_line_len)) {
				fault = 1;
			}
		}

		// Write token
		EncodedState newstate;
		newstate.faults() = fault;
		newstate.riddle() = info.state.riddle() + 1;
		char token[22];
		newstate.toString(token);
		info.comm.write("\nToken: ", 8);
		info.comm.write(token, sizeof(token));
		info.comm.write("\n", 1);
		return true;
	}
}
}
