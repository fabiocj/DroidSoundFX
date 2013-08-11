/*
 * SimpleReverb.h
 *
 *  Created on: 03/06/2013
 *      Author: leonardo.goncalves
 */

#ifndef SIMPLEREVERB_H_
#define SIMPLEREVERB_H_

#include "effects/NativeAudioProcessor.h"

#include <jni.h>

#define DELAY_BUFFER_SIZE 100000

namespace DroidSoundFX {

class SimpleReverb: public DroidSoundFX::NativeAudioProcessor {

private:
	float mBuffer[DELAY_BUFFER_SIZE];
	int indexRead;
	int indexWrite;

	float ratio; // % 0-100
	int delay; // ms
	int samplingRate; // Hz

public:
	SimpleReverb();
	virtual ~SimpleReverb();

	void process(float * buffer, int bufferSize);
	void onParameterChange();
	void setParameter( int parametedId, jvalue value );
	int getIntParameter( int parametedId );

};

} /* namespace DroidSoundFX */
#endif /* SIMPLEREVERB_H_ */
