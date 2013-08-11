/*
 * JavaAudioProcessor.h
 *
 *  Created on: 25/04/2013
 *      Author: Leonardo
 */

#ifndef JAVAAUDIOPROCESSOR_H_
#define JAVAAUDIOPROCESSOR_H_

#include <jni.h>
#include "NativeAudioProcessor.h"

namespace DroidSoundFX {

class JavaAudioProcessor : public NativeAudioProcessor {

private:
	jobject jEffect;
	jmethodID processMethodId;
	JNIEnv * jniEnv;

public:
	JavaAudioProcessor( jobject jEffect );
	virtual ~JavaAudioProcessor();

	void init( JNIEnv * jniEnv );

	void process(float * buffer, int bufferSize);

};

} /* namespace DroidSoundFX */
#endif /* JAVAEFFECT_H_ */
