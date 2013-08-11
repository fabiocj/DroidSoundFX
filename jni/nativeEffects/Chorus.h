/*
 * Chorus.h
 *
 *  Created on: 21/06/2013
 *      Author: Leonardo
 */

#ifndef CHORUS_H_
#define CHORUS_H_

#include "effects/NativeAudioProcessor.h"

#define CHORUS_BUFFER_SIZE 100000
#define WAVE_TRIANGLE 1
#define WAVE_SINE 2

namespace DroidSoundFX {

class Chorus : public NativeAudioProcessor {
private:
	float mBuffer[CHORUS_BUFFER_SIZE];
	int inputPointer;
	int echo_ratio;
	int invertFeedback; // -1 or 1
	int invertMixing; // -1 or 1
	int feedback ; // 0-100%
	int dry; // 0-100%
	int wet; // 0-100%
	int delayMS; // ms
	int depthMS; // ms
	int delay ;
	int depth;
	float rate;
	int waveform; // WAVE_TRIANGULE or WAVE_SINE
	int samplingRate ;
	int delay_offset ;
	int middle_offset ;
	int samples_per_cycle ;
	int cycle_position ;

public:
	Chorus();
	virtual ~Chorus();

	void process(float * buffer, int bufferSize);
	void onParameterChange();
	void setParameter( int parametedId, jvalue value );
	int getIntParameter( int parametedId );
};

} /* namespace DroidSoundFX */
#endif /* CHORUS_H_ */
