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
  switch (anim) {
  default:
    anim::TicTac::init_data(&anim_data);
    play_ptr = &anim::TicTac::play;
  }
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
