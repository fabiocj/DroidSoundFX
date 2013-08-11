/*
 * SimpleDelayEffect.h
 *
 *  Created on: 17/04/2013
 *      Author: Leonardo
 */

#ifndef SIMPLEDELAYEFFECT_H_
#define SIMPLEDELAYEFFECT_H_

#include "effects/NativeAudioProcessor.h"

#include "SoundCore.h"

#define DELAY_BUFFER_SIZE 100000

namespace DroidSoundFX {

class SimpleDelayEffect: public NativeAudioProcessor {
private:
	float mBuffer[DELAY_BUFFER_SIZE];
	int indexRead;
	int indexWrite;

	int delay; // ms
	float ratio; // % 0-100
	int samplingRate; // Hz

public:
	SimpleDelayEffect();
	virtual ~SimpleDelayEffect();

	void process(float * buffer, int bufferSize);
	void onParameterChange();
	void setParameter( int parametedId, jvalue value );
	int getIntParameter( int parametedId );

};

} /* namespace DroidSoundFX */
#endif /* SIMPLEDELAYEFFECT_H_ */
