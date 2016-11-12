#!/bin/sh
g++ -std=c++11 -o increment_token increment_token.cpp ../embedded24hc17/EncodedState.cpp ../embedded24hc17/SerialCommunicator.cpp -I ../embedded24hc17/
./increment_token $@
