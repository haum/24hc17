24HC17 - Codes
==============

This repository regroups codes used for the subject we submitted to 24HC17 event.

embedded24hc17
--------------

This is code for embedded device.

It's tested Arduino "IDE" v1.6.11 with esp8266 package (http://arduino.esp8266.com/stable/package_esp8266com_index.json)
but the use of Arduino.mk is recommended.

Remember to update your submodules using :

	git submodule init
	git sumbodule update

increment_token
---------------

This code allows to increment riddle inside a token.
It decodes a token, increment riddle number and encode it again.
It is a little bit hacky though.
