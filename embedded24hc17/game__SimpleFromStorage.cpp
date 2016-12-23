#include "game__SimpleFromStorage.h"
#include "EncodedState.h"
#include <cstring>
#include <FS.h>

namespace game {
namespace SimpleFromStorage {
	void init_data(void * data, const char * const name) {
		Data * d = static_cast <Data*> (data);
		size_t n = strlen(name);
		if (n > sizeof(d->name))
			n = sizeof(d->name);
		memcpy(d->name, name, n);
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
		char ans[255];
		info.comm.write("\nAnswer: ", 9);
		int len = info.comm.read(ans, sizeof(ans));
		snprintf(file, sizeof(file), "/%s/answer%d", d->name, choice);
		int fault = 1;
		char goodans[255];
		File f = SPIFFS.open(file, "r");
		if (f) {
			int r = f.readBytes(goodans, sizeof(goodans));
			if (goodans[r-1] == '\n')
				r -= 1;
			if (!strncmp(ans, goodans, r))
				fault = 0;
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
