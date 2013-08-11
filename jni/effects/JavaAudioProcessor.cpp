/*
 * JavaEffect.cpp
 *
 *  Created on: 25/04/2013
 *      Author: Leonardo
 */

#include "JavaAudioProcessor.h"

#include "utils/myutils.h"

namespace DroidSoundFX {

JavaAudioProcessor::JavaAudioProcessor(jobject effect ) {
	jEffect = effect;
}

JavaAudioProcessor::~JavaAudioProcessor() {
	// TODO Auto-generated destructor stub
}

void JavaAudioProcessor::init(JNIEnv * env) {
	jniEnv = env;

	if ( jEffect == NULL ) {
		LOGE("jEffect == NULL");
	}

	if ( jniEnv == NULL ) {
		LOGE("jniEnv == NULL");
	}

	jclass classObj = jniEnv->GetObjectClass( jEffect );
	if ( classObj == NULL ) {
		LOGE("classObj failed");
	}

	processMethodId = jniEnv->GetMethodID( classObj, "process", "([F)V");
	if ( processMethodId == NULL ) {
		LOGE("processMethodId failed");
	}

}

void JavaAudioProcessor::process( float * buffer, int bufferSize ) {
	jfloatArray array = jniEnv->NewFloatArray( bufferSize );
	jniEnv->SetFloatArrayRegion(array, 0, bufferSize, buffer);

	jniEnv->CallVoidMethod( jEffect, processMethodId, array );

	jniEnv->GetFloatArrayRegion(array, 0, bufferSize, buffer);

	jniEnv->DeleteLocalRef( array );
}

} /* namespace DroidSoundFX */
