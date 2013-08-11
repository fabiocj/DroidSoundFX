/*
 * SimpleDelayEffect.cpp
 *
 *  Created on: 17/04/2013
 *      Author: Leonardo
 */

#include "nativeEffects/SimpleDelayEffect.h"

namespace DroidSoundFX {

SimpleDelayEffect::SimpleDelayEffect() {
	int i;
	for (i = 0; i < DELAY_BUFFER_SIZE; i++) {
		mBuffer[i] = 0;
	}

	// setting parameters:
	delay = 300; // in milliseconds
	ratio = 0.8; // %
	samplingRate = 44100;

	this->onParameterChange();
}

SimpleDelayEffect::~SimpleDelayEffect() {
}

void SimpleDelayEffect::process(float * buffer, int bufferSize) {
	for (int i = 0; i < bufferSize; i++) {
		mBuffer[indexWrite] = buffer[i];
		buffer[i] = buffer[i] + mBuffer[indexRead] * ratio;

		indexWrite = (indexWrite + 1) % DELAY_BUFFER_SIZE;
		indexRead = (indexRead + 1) % DELAY_BUFFER_SIZE;
	}
}

void SimpleDelayEffect::setParameter( int parametedId, jvalue value ) {
	switch ( parametedId ) {
		case 0:
			delay = value.i;
			break;
		case 1:
			ratio = value.i / (float) 100;
			break;
		case 2:
			samplingRate = value.i;
			break;
	}
}

int SimpleDelayEffect::getIntParameter( int parametedId ) {
	switch ( parametedId ) {
		case 0:
			return delay;
			break;
		case 1:
			return ratio * 100;
			break;
		case 2:
			return samplingRate;
			break;
	}
}

void SimpleDelayEffect::onParameterChange() {
	indexWrite = 0;
	indexRead = ( indexWrite - delay * (samplingRate / 1000) + DELAY_BUFFER_SIZE ) % DELAY_BUFFER_SIZE;
}


} /* namespace DroidSoundFX */
