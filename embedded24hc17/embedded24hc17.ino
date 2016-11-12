#include "SerialCommunicator.h"

namespace {
  const constexpr int led = 2;
  const constexpr int wait = 200;
  bool blink = true;
  int divider = 0;

  SerialCommunicator comm;
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
}

void loop() {
  char data[255];
  int len = comm.read(data, sizeof(data));
  comm.write(data, len);
  comm.write("\n", 1);
}
