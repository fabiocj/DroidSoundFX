/*
 * Chorus.cpp
 *
 *  Created on: 21/06/2013
 *      Author: Leonardo
 */

#include "Chorus.h"
#include <math.h>

#define DOUBLE_PI 6.28318530718
#define FLOAT_CONST ((float) 0x00FFFFFF)

namespace DroidSoundFX {

Chorus::Chorus() {
	for (int i = 0; i < CHORUS_BUFFER_SIZE; i++) {
		mBuffer[i] = 0;
	}

	inputPointer = 0;
	samplingRate = 44100;

	delayMS = 10;

	depthMS = 60;
	rate = 0.80; // 0.80 Hz
	waveform = WAVE_TRIANGLE;

	dry = 75;
	wet = 80;
	invertMixing = -1;

	feedback = 0;
	invertFeedback = 1;

	this->onParameterChange();
}

Chorus::~Chorus() {

}

void Chorus::process(float * buffer, int bufferSize) {
	int x2, x3, offset, modAux;
	int offset1, offset2, k;

	for( int i = 0; i < bufferSize; i++ ) {
		x2 = buffer[i] * FLOAT_CONST;

		if ( waveform == WAVE_TRIANGLE ) {
			if (cycle_position < samples_per_cycle / 2) {
				k = cycle_position;
			} else {
				k = samples_per_cycle - cycle_position;
			}
			offset = inputPointer - delay_offset - depth * 2 * k / samples_per_cycle;
			//offset = input_pointer - delay_offset - depth * 2 * ( samples_per_cycle - cycle_position ) / samples_per_cycle;
		} else { // waveform=WAVE_SINE
			modAux = (inputPointer-depth * sin( cycle_position / samples_per_cycle * DOUBLE_PI ) - middle_offset + CHORUS_BUFFER_SIZE);
			//offset = fmod( modAux, CHORUS_BUFFER_SIZE );
			offset = modAux % CHORUS_BUFFER_SIZE;
		}

		// get a second offset to do linear interpolation
		offset1 = (int) offset;
		offset2 = (offset + 1) % CHORUS_BUFFER_SIZE;

		// mix the dry part of the signal
		x2 *= dry / 100; // determine delay unit output
		x3 = mBuffer[offset1] * ( 1 - offset + offset1 ) + mBuffer[offset2] * ( offset - offset1 );

		// add wet signal to dry signal for final output
		x2 += invertMixing * x3 * wet / 100;

		// add feedback to original signal and store in delay buffer
		mBuffer[inputPointer] = buffer[i] + invertFeedback * x3 * feedback / 100;

		// bump up counters
		inputPointer = ( inputPointer + 1 ) % CHORUS_BUFFER_SIZE;
		cycle_position = ( cycle_position + 1 ) % samples_per_cycle;

		buffer[i] = x2 / FLOAT_CONST;
	}
}

void Chorus::onParameterChange() {
	delay = delayMS * samplingRate / 1000;
	depth = depthMS * samplingRate / 1000;

	delay_offset = samplingRate * delayMS / 1000;
	middle_offset = samplingRate * ( delayMS + depthMS / 2 ) / 1000;
	// middle_offset is = delay_offset + 1/2 depth offset
	// needed for sine LFO calculation,
	// because the sine function
	// varies between -1 and +1, not 0 and 1
	samples_per_cycle = samplingRate / rate;
	cycle_position = 0;
}

void Chorus::setParameter( int parametedId, jvalue value ) {
	// TODO
}

int Chorus::getIntParameter( int parametedId ) {
	// TODO
}

} /* namespace DroidSoundFX */
