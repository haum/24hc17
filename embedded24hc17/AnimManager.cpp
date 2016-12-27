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
		anim::Alea::Data a08;
		anim::RandomTicking::Data a09;
		anim::Morse::Data a10;
	} anim_data;
}

CRGB AnimManager::leds[nb_leds];

void (*AnimManager::play_ptr)(void*) = &anim::Breathing::play;

void AnimManager::setup() {
	FastLED.addLeds<NEOPIXEL, neopixel_datapin>(leds, nb_leds);
}

void AnimManager::set(int anim) {
	switch (anim) {
		case 1:
			anim::Morse::init_data(&anim_data, "SOS");
			play_ptr = &anim::Morse::play;
			break;
		case 41:
			anim::RandomTicking::init_data(&anim_data, 34);
			play_ptr = &anim::RandomTicking::play;
			break;
		case 43:
			anim::Alea::init_data(&anim_data);
			play_ptr = &anim::Alea::play;
			break;
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
