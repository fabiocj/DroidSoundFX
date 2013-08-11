/*
 * Distortion.cpp
 *
 *  Created on: 22/06/2013
 *      Author: Leonardo
 */

#include "Distortion.h"
#include "jni.h"
#include <climits>

#define FLOAT_CONST ((float) 0x00FFFFFF)

namespace DroidSoundFX {

Distortion::Distortion() {
	dryOut = 0.5;
	distortedOut = 0.8;
	threshold = SHRT_MAX * 0.1;
	clamp = SHRT_MAX * 0.2;
	gate = true;
}

Distortion::~Distortion() {
}

void Distortion::process(float * buffer, int bufferSize) {
	float sample;
	double dist;

	for( int i = 0; i < bufferSize; i++ ) {
		sample = buffer[i] * dryOut;

		dist = (double) sample;

		// perform distortion if threshold is exceeded
		if ( gate ) {
			if ( dist <= threshold &&
					dist >= -threshold ) {
				dist = clamp;
				if ( sample < 0 ) {
					dist = -dist;
				}
			}
		} else {
			if (dist >= threshold) {
				dist = clamp;
			} else if ( dist <= -threshold ) {
				dist = -clamp;
			}
		}

		// mix dry signal with distorted signal
		buffer[i] = sample + distortedOut * dist;
/*
		if (dist >= threshold_level && !gate ) {
			dist = clamp_level;
		} else if ( dist <= -threshold_level && !gate) {
			dist = -clamp_level;
		} else if ( dist <= threshold_level &&
				dist >= -threshold_level && gate ) {
			dist = clamp_level;
			if ( x2 < 0 ) dist = -dist;
		}
*/



		//dry_out = 1 - distorted_out;
		//buffer[i] = sample * dry_out + distorted_out * dist;
	}
}

void Distortion::onParameterChange() {

}

void Distortion::setParameter( int parameterId, jvalue value ) {
	switch( parameterId ) {
		case 1:
			dryOut = value.i / (float) 100;
			break;
		case 2:
			distortedOut = value.i / (float) 100;
			break;
		case 3:
			threshold = value.i / FLOAT_CONST;
			break;
		case 4:
			clamp = value.i / FLOAT_CONST;
			break;
		case 5:
			gate = value.b;
			break;
	}
}

int Distortion::getIntParameter( int parameterId ) {
	switch( parameterId ) {
		case 1:
			return dryOut * 100;
		case 2:
			return distortedOut * 100;
		case 3:
			return threshold * FLOAT_CONST;
		case 4:
		default:
			return clamp * FLOAT_CONST;
	}
}

bool Distortion::getBoolParameter( int parameterId ) {
	return gate;
}

} /* namespace DroidSoundFX */
