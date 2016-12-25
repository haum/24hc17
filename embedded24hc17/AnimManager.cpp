#include "AnimManager.h"

#include "anim__TicTac.h"
#include "anim__Circles.h"
#include "anim__FillAll.h"
#include "anim__FillSpiral.h"
#include "anim__RotBeacon.h"
#include "anim__Breathing.h"
#include "anim__HuePan.h"
#include "anim__HeartBeat.h"

namespace {
	union {
		anim::TicTac::Data a00;
		anim::Circles::Data a01;
		anim::FillAll::Data a02;
		anim::FillSpiral::Data a03;
		anim::RotBeacon::Data a04;
		anim::Breathing::Data a05;
		anim::HuePan::Data a06;
		anim::HeartBeat::Data a07;
	} anim_data;
}

CRGB AnimManager::leds[nb_leds];

void (*AnimManager::play_ptr)(void*) = &anim::Breathing::play;

void AnimManager::setup() {
	FastLED.addLeds<NEOPIXEL, neopixel_datapin>(leds, nb_leds);
}

void AnimManager::set(int anim) {
	switch (anim) {
		default:
			anim::Breathing::init_data(&anim_data);
			play_ptr = &anim::Breathing::play;
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
