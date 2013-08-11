/*
 * Distortion.h
 *
 *  Created on: 22/06/2013
 *      Author: Leonardo
 */

#ifndef DISTORTION_H_
#define DISTORTION_H_

#include "effects/NativeAudioProcessor.h"

namespace DroidSoundFX {

class Distortion : public NativeAudioProcessor {
private:
	bool gate;// noise gate on or off
	float dryOut; // %
	float distortedOut; // %
	float threshold; // 0 - MAX, MAX == sample max value (32767 for 16bit)
	float clamp; // 0 - MAX, MAX == sample max value (32767 for 16bit)

public:
	Distortion();
	virtual ~Distortion();

	void process(float * buffer, int bufferSize);
	void onParameterChange();
	void setParameter( int parametedId, jvalue value );
	int getIntParameter( int parametedId );
	bool getBoolParameter( int parameterId );
};

} /* namespace DroidSoundFX */
#endif /* DISTORTION_H_ */
