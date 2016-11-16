#include "AnimManager.h"

#include "anim__TicTac.h"

namespace {
  union {
    anim::TicTac::Data a00;
  } anim_data;
}

CRGB AnimManager::leds[nb_leds];

void (*AnimManager::play_ptr)(void*) = &anim::TicTac::play;

void AnimManager::setup() {
  FastLED.addLeds<NEOPIXEL, neopixel_datapin>(leds, nb_leds);
}

void AnimManager::set(int anim) {
  void (*init_data)(void *);
  switch (anim) {
  default:
    init_data = &anim::TicTac::init_data;
    play_ptr = &anim::TicTac::play;
  }
  init_data(&anim_data);
}

void AnimManager::play() {
  (*play_ptr)(&anim_data);
}

void AnimManager::setLed(int pos, CRGB color) {
  if (pos >= 0 && pos < nb_leds)
    leds[pos] = color;
}

void AnimManager::animate() {
  delay(10);
  play();
  FastLED.show();
}
