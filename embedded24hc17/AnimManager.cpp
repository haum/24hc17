#include "AnimManager.h"

#include "anim__TicTac.h"
#include "anim__Circles.h"
#include "anim__FillAll.h"
#include "anim__FillSpiral.h"
#include "anim__RotBeacon.h"
#include "anim__Breathing.h"
#include "anim__HuePan.h"
#include "anim__HeartBeat.h"
#include "anim__Alea.h"
#include "anim__Morse.h"
#include "anim__RandomTicking.h"
#include "anim__Fiesta.h"
#include "anim__DeathStar.h"
#include "anim__Rings.h"
//#include "anim__TestsLVA.h"
#include "anim__Hangman.h"
#include "anim__Storm.h"
#include "anim__LightStorm.h"
#include "anim__HorizontalChase.h"
#include "anim__VerticalChase.h"
#include "anim__LockChase.h"
#include "anim__ScrollUp.h"
#include "anim__ScrollDown.h"


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
		anim::Fiesta::Data a11;
//		anim::DeathStar::Data a12;
//		anim::TestsLVA::Data a13;
		anim::Rings::Data a14;
		anim::Hangman::Data a15;
		anim::Storm::Data a16;
		anim::LightStorm::Data a17;
		anim::HorizontalChase::Data a18;
		anim::VerticalChase::Data a19;
		anim::LockChase::Data a20;
	} anim_data;
}

CRGB AnimManager::leds[nb_leds];

void (*AnimManager::play_ptr)(void*) = &anim::Breathing::play;

void AnimManager::setup() {
	FastLED.addLeds<NEOPIXEL, neopixel_datapin>(leds, nb_leds);
}

void AnimManager::set(int anim) {
	switch (anim) {
		case 0:
			anim::TicTac::init_data(&anim_data);
			play_ptr = &anim::TicTac::play;
			break;
		case 1:
			anim::Morse::init_data(&anim_data, "SOS");
			play_ptr = &anim::Morse::play;
			break;
		case 2:
			anim::Morse::init_data(&anim_data, "WE ARE HACKERS", 8, 20, CRGB::Green);
			play_ptr = &anim::Morse::play;
			break;
		case 3:
			anim::Morse::init_data(&anim_data, "004032 LAIRES BSU");
			play_ptr = &anim::Morse::play;
			break;
		case 41:
			anim::RandomTicking::init_data(&anim_data, 34);
			play_ptr = &anim::RandomTicking::play;
			break;
		case 42:
			anim::Fiesta::init_data(&anim_data, 1, 3);
			play_ptr = &anim::Fiesta::play;
			break;
		case 43:
			anim::Alea::init_data(&anim_data);
			play_ptr = &anim::Alea::play;
			break;
		case 44:
			anim::DeathStar::init_data(&anim_data, "PERDU");
			play_ptr = &anim::DeathStar::play;
			break;
		case 45:
			anim::Rings::init_data(&anim_data);
			play_ptr = &anim::Rings::play;
			break;
		case 46:
			anim::Hangman::init_data(&anim_data, 8);
			play_ptr = &anim::Hangman::play;
			break;
		case 47:
			anim::Storm::init_data(&anim_data);
			play_ptr = &anim::Storm::play;
			break;
		case 48:
			anim::LightStorm::init_data(&anim_data);
			play_ptr = &anim::LightStorm::play;
			break;
		case 49:
			anim::HorizontalChase::init_data(&anim_data, 1);
			play_ptr = &anim::HorizontalChase::play;
			break;
		case 50:
			anim::VerticalChase::init_data(&anim_data, 1);
			play_ptr = &anim::VerticalChase::play;
			break;
		case 51:
			anim::Fiesta::init_data(&anim_data, 4, 1);
			play_ptr = &anim::Fiesta::play;
			break;
		case 52:
			anim::LockChase::init_data(&anim_data, 10, 0, 5, 0, 5, 1);
			play_ptr = &anim::LockChase::play;
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

void AnimManager::setAllLeds(CRGB color) {
	for(int i = 0; i<nb_leds; i++)
	{
		leds[i] = color;
	}	
}

void AnimManager::setLedScalp(CRGB color) {
	leds[2] = color;
	leds[3] = color;
	leds[8] = color;
	leds[9] = color;
	leds[10] = color;
}

void AnimManager::setTopRing(CRGB color) {
	leds[2] = color;
	leds[3] = color;
	leds[8] = color;
	leds[10] = color;
}

void AnimManager::setMiddleRing(CRGB color) {
	leds[1] = color;
	leds[4] = color;
	leds[7] = color;
	leds[11] = color;
}

void AnimManager::setBottomRing(CRGB color) {
	leds[0] = color;
	leds[5] = color;
	leds[6] = color;
	leds[12] = color;
}			
			
void AnimManager::clear() {
	for (auto & led : leds)
		led = CRGB::Black;
}

void AnimManager::animate() {
	delay(10);
	play();
	FastLED.show();
}
