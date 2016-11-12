#include "SerialCommunicator.h"

#ifdef ESP8266
#include <HardwareSerial.h>
#else
#include <iostream>
#include <cstdio>
#include <cstring>
#endif

SerialCommunicator::SerialCommunicator() {
#ifdef ESP8266
  Serial.begin(115200);
#endif
}

uint32_t SerialCommunicator::read(char * data, uint32_t max) {
#ifdef ESP8266
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
#else
  std::string str;
  std::cin >> str;
  uint32_t len = max;
  if (str.size() < len) len = str.size();
  memcpy(data, str.data(), len);
#endif
  return len;
}

void SerialCommunicator::write(char const * const data, uint32_t len) {
#ifdef ESP8266
  Serial.write(data, len);
#else
  printf("%.*s", len, data);
#endif
}

void SerialCommunicator::write(int data, IntFormat fmt) {
#ifdef ESP8266
  Serial.print(data, (fmt == IntFormat::FMTDEC) ? DEC : HEX);
#else
  if (fmt == FMTDEC)
    printf("%i", data);
  else if (fmt == FMTHEX)
    printf("%x", data);
#endif
}
