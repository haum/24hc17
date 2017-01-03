#ifndef ANIMMANAGER_H
#define ANIMMANAGER_H

#include <FastLED.h>

/** Animation manager **/
class AnimManager {
	public:
		/** Setup **/
		static void setup();

		/** Set next animation
		* @param anim Animation number
		*/
		static void set(int anim);

		/** Play the animation **/
		static void play();

		/** Play current animation **/
		static void animate();

		/** Clear leds **/
		static void clear();

		/** Set led color **/
		static void setLed(int pos, CRGB color);

		/** Set full color **/
		static void setAllLeds(CRGB color);

		/** Set scalp color **/
		static void setLedScalp(CRGB color);

	private:
		/** Data pin for neopixel **/
		static const constexpr int neopixel_datapin = D3;

		/** Number of leds in strip **/
		static const constexpr int nb_leds = 13;

		/** Pointer to current game **/
		static void (*play_ptr)(void*);

		/** Leds **/
		static CRGB leds[nb_leds];
};

#endif // ANIMMANAGER_H
