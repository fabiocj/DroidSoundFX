/*
 * NativeAudioProcessor.h
 *
 *  Created on: 25/04/2013
 *      Author: Leonardo
 */

#ifndef NATIVEAUDIOPROCESSOR_H_
#define NATIVEAUDIOPROCESSOR_H_

#include <jni.h>

namespace DroidSoundFX {

class NativeAudioProcessor {

private:
	int id;
	bool enabled;

public:
	NativeAudioProcessor();
	virtual ~NativeAudioProcessor();

	int getId();
	void setId( int id );
	bool isEnabled();
	void setEnabled( bool enabled );

	virtual void process( float * buffer, int bufferSize ) = 0;

	void changeParameter( int parametedId, jvalue value );

	virtual void setParameter( int parametedId, jvalue value ) {};
	virtual void onParameterChange() {}

	virtual char getByteParameter( int parameterId ) {};
	virtual char getCharParameter( int parameterId ) {};
	virtual double getDoubleParameter( int parameterId ) {};
	virtual float getFloatParameter( int parameterId ) {};
	virtual int getIntParameter( int parameterId ) {};
	virtual long getLongParameter( int parameterId ) {};
	virtual short getShortParameter( int parameterId ) {};
	virtual bool getBoolParameter( int parameterId ) {};

};

} /* namespace DroidSoundFX */
#endif /* NATIVEAUDIOPROCESSOR_H_ */
