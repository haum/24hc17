 #include "SerialCommunicator.h"
#include "EncodedState.h"
#include "GameManager.h"
#include "AnimManager.h"

#include <FS.h>

namespace {
	const constexpr int led = 2;
	SerialCommunicator comm;
	EncodedState state;
	GameManager::GameInfo info {
		comm,
		state,
	};
}

void setup() {
	pinMode(led, OUTPUT);
	digitalWrite(led, HIGH);

	comm.write("24hc17\n", 7);

	EncodedState::ourid = ESP.getChipId();
	state.id() = EncodedState::ourid;

	SPIFFS.begin();

	AnimManager::setup();

	AnimManager::set(42);
	long start_millis = millis();
	char * code = "Je suis un hacker !";
	while (millis()-start_millis < 10*60*1000) {
		char c = random(0,255);
		comm.write(&c, 1);
		if (comm.available()) {
			char ans;
			Serial.readBytes(&ans, 1);
			if (*code == ans) code++;
			if (*code == 0) break;
		}
		AnimManager::animate();
	}
	AnimManager::set(3);
}

void loop() {
	if (!GameManager::play(info))
		return;

	comm.write("\nVitellius' answer: ", 20);
	char token[22];
	int len = comm.read(token, sizeof(token));

	EncodedState newstate;
	if (newstate.fromString(token) && newstate.id() == EncodedState::ourid && newstate.direction() == 0) {
		comm.write("\n", 1);
/*
		comm.write(token, len);
		comm.write("\n", 1);
*/
		state = newstate;
//		state.print(comm);
		if (state.sentence()!=0) {
			char file[20];
			snprintf(file, sizeof(file), "/Sentences/s%d", (int)(state.sentence()));
			comm.dump_file(file);
		}
		GameManager::set(state.riddle());
		AnimManager::set(state.animation());
	} else {
		comm.write("I don't understand his answer, it's total gibberish !\n\n", 55);
	}
}
