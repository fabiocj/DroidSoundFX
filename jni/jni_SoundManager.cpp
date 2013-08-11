/*
 * jni_SoundManager.cpp
 *
 *  Created on: 28/04/2013
 *      Author: Leonardo
 */

#include <jni.h>

#include "NativeSoundSettings.h"
#include "NativeSoundManager.h"
#include "utils/myutils.h"

#define CHANNEL_MONO 1
#define CHANNEL_STEREO 2

namespace jni_SoundManager {
	SLuint16 convertBitsPerSample(int bitsPerSample);
	SLuint32 convertChannels( int channels );
	SLuint32 convertSamplingRate( int samplingRate );
}

#ifdef __cplusplus
extern "C" {

void Java_com_droidsoundfx_engine_SoundManager_createNativeEngine(JNIEnv * env, jobject thiz,
		jobject inputSettings, jobject outputSettings) {

	DroidSoundFX::NativeSoundManager * soundManager = DroidSoundFX::NativeSoundManager::getInstance();

	DroidSoundFX::NativeSoundSettings * inputConfig = new DroidSoundFX::NativeSoundSettings;
	DroidSoundFX::NativeSoundSettings * outputConfig = new DroidSoundFX::NativeSoundSettings;

	// TODO handle errors?

	jclass classObj = env->GetObjectClass( inputSettings );
	jmethodID getNativeBitsPerSample = env->GetMethodID( classObj, "getNativeBitsPerSample", "()I" );
	jmethodID getNativeChannels = env->GetMethodID( classObj, "getNativeChannels", "()I" );
	jmethodID getNativeSamplingRate = env->GetMethodID( classObj, "getNativeSamplingRate", "()I" );

	int bitsPerSample;
	int channels;
	int samplingRate;

	// input:
	bitsPerSample = env->CallIntMethod( inputSettings, getNativeBitsPerSample );
	channels = env->CallIntMethod( inputSettings, getNativeChannels );
	samplingRate = env->CallIntMethod( inputSettings, getNativeSamplingRate );

	inputConfig->setBitsPerSample( jni_SoundManager::convertBitsPerSample( bitsPerSample ) );
	inputConfig->setChannels( jni_SoundManager::convertChannels( channels ) );
	inputConfig->setSamplingRate( jni_SoundManager::convertSamplingRate( samplingRate ) );

	// output:
	bitsPerSample = env->CallIntMethod( outputSettings, getNativeBitsPerSample );
	channels = env->CallIntMethod( outputSettings, getNativeChannels );
	samplingRate = env->CallIntMethod( outputSettings, getNativeSamplingRate );

	outputConfig->setBitsPerSample( jni_SoundManager::convertBitsPerSample( bitsPerSample ) );
	outputConfig->setChannels( jni_SoundManager::convertChannels( channels ) );
	outputConfig->setSamplingRate( jni_SoundManager::convertSamplingRate( samplingRate ) );

	// create engine:
	soundManager->createEngine( env, inputConfig, outputConfig );

}

void Java_com_droidsoundfx_engine_SoundManager_destroyNativeEngine(JNIEnv * env, jobject thiz ) {
	DroidSoundFX::NativeSoundManager * soundManager = DroidSoundFX::NativeSoundManager::getInstance();
	soundManager->destroyEngine();
}

bool Java_com_droidsoundfx_engine_SoundManager_startNativeProcessing(JNIEnv * env, jobject thiz ) {
	DroidSoundFX::NativeSoundManager * soundManager = DroidSoundFX::NativeSoundManager::getInstance();
	return soundManager->startAudioProcessing( env );
}

void Java_com_droidsoundfx_engine_SoundManager_stopNativeProcessing(JNIEnv * env, jobject thiz ) {
	DroidSoundFX::NativeSoundManager * soundManager = DroidSoundFX::NativeSoundManager::getInstance();
	soundManager->stopAudioProcessing();
}

int Java_com_droidsoundfx_engine_SoundManager_registerNativeEffect(JNIEnv * env, jobject thiz,
		int nativeEffectID ) {
	LOGD( "Java_com_droidsoundfx_engine_SoundManager_registerNativeEffect" );
	return DroidSoundFX::NativeSoundManager::getInstance()->registerEffect( nativeEffectID );
}

bool Java_com_droidsoundfx_engine_SoundManager_addEffect(JNIEnv * env, jobject thiz,
		int effectId ) {
	LOGD( "Java_com_droidsoundfx_engine_SoundManager_affEffect" );
	return DroidSoundFX::NativeSoundManager::getInstance()->addToSoundCore( env, effectId );
}

void Java_com_droidsoundfx_engine_SoundManager_removeEffect(JNIEnv * env, jobject thiz,
		int effectId ) {
	DroidSoundFX::NativeSoundManager::getInstance()->removeFromSoundCore( env, effectId );
}

}
#endif

namespace jni_SoundManager {
	SLuint16 convertBitsPerSample(int bitsPerSample) {
		switch( bitsPerSample ) {
			case 8:
				return SL_PCMSAMPLEFORMAT_FIXED_8;
			case 16:
			default:
				return SL_PCMSAMPLEFORMAT_FIXED_16;
			// TODO adicionar outros formatos
		}
	}

	SLuint32 convertChannels( int channels ) {
		if ( channels == CHANNEL_MONO ) {
			return 1;
		} else { // CHANNEL_STEREO
			return 2; // TODO como seria com varios canais?
		}
	}

	SLuint32 convertSamplingRate( int samplingRate ) {
		switch( samplingRate ) {
			case 8000:
				return SL_SAMPLINGRATE_8;
			case 11025:
				return SL_SAMPLINGRATE_11_025;
			case 12000:
				return SL_SAMPLINGRATE_12;
			case 16000:
				return SL_SAMPLINGRATE_16;
			case 22050:
				return SL_SAMPLINGRATE_22_05;
			case 24000:
				return SL_SAMPLINGRATE_24;
			case 32000:
				return SL_SAMPLINGRATE_32;
			case 44100:
				return SL_SAMPLINGRATE_44_1;
			case 48000:
			default:
				return SL_SAMPLINGRATE_48;
				// TODO outros valores
		}
	}
}

