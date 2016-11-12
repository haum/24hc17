#include "SerialCommunicator.h"

#include <HardwareSerial.h>

SerialCommunicator::SerialCommunicator() {
  Serial.begin(115200);
}

uint32_t SerialCommunicator::read(char * data, uint32_t max) {
  uint32_t len = 0;
  bool run = true;
  while (run) {
    if (Serial.available()) {
      char r = Serial.read();
      if (len < max && r != '\n') {
        data[len] = r;
        ++len;
      } else {
        run = false;
      }
    }
    animate();
  }
  return len;
}

void SerialCommunicator::write(char const * const data, uint32_t len) {
  Serial.write(data, len);
}

void SerialCommunicator::write(int data, IntFormat fmt) {
  Serial.print(data, (fmt == IntFormat::FMTDEC) ? DEC : HEX);
}
