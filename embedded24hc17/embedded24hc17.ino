#include "SerialCommunicator.h"
#include "EncodedState.h"
#include "GameManager.h"

#include <ESP8266WiFi.h>

namespace {
  const constexpr int led = 2;
  const constexpr int wait = 200;
  bool blink = true;
  int divider = 0;

  SerialCommunicator comm;
  EncodedState state;
  GameManager::GameInfo info {
    comm,
    state,
  };
}

void animate() {
  delay(10);
  if (divider == wait/10) {
    divider = 0;
    blink = !blink;
    digitalWrite(led, blink);
  } else {
    divider++;
  }
}

void setup() {
  pinMode(led, OUTPUT);

  comm.write("24hc17\n", 7);

  byte mac[6];
  WiFi.softAPmacAddress(mac);
  EncodedState::ourid = mac[0] | mac[1] << 8;
  state.id() = EncodedState::ourid;
}

void loop() {
  if (!GameManager::play(info))
    return;

  comm.write("\nToken: ", 8);
  char token[22];
  int len = comm.read(token, sizeof(token));

  EncodedState newstate;
  if (newstate.fromString(token) && newstate.id() == EncodedState::ourid) {
    comm.write("\n", 1);
    comm.write(token, len);
    comm.write("\n", 1);
    state = newstate;
    state.print(comm);
    GameManager::set(state.riddle());
  } else {
    comm.write("Unknown token\n", 14);
  }
}
