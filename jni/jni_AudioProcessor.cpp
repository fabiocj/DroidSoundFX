/*
 * jni_NativeEffect.cpp
 *
 *  Created on: 25/04/2013
 *      Author: Leonardo
 */

#include <jni.h>

#include "NativeSoundSettings.h"
#include "NativeSoundManager.h"
#include "effects/NativeAudioProcessor.h"
#include "effects/JavaAudioProcessor.h"
#include "utils/myutils.h"

namespace jni_AudioProcessor {
	DroidSoundFX::NativeAudioProcessor * getBaseEffect( int effectId ) {
		DroidSoundFX::NativeSoundManager * soundManager = DroidSoundFX::NativeSoundManager::getInstance();
		return soundManager->getBaseEffect( effectId );
	}

	DroidSoundFX::JavaAudioProcessor * getJavaEffect( int effectId ) {
		DroidSoundFX::NativeSoundManager * soundManager = DroidSoundFX::NativeSoundManager::getInstance();
		return soundManager->getJavaEffect( effectId );
	}
}

#ifdef __cplusplus
extern "C" {

void Java_com_droidsoundfx_effect_AudioProcessor_setNativeEnabled(JNIEnv* env, jobject thiz,
		int effectId, bool enabled ) {
	DroidSoundFX::NativeAudioProcessor * baseEffect = jni_AudioProcessor::getBaseEffect( effectId );
	LOGD("id = %d, baseEffect = %d", effectId, baseEffect);
	baseEffect->setEnabled( enabled );
}

void Java_com_droidsoundfx_effect_NativeAudioProcessor_setEffectParameter(JNIEnv* env, jobject thiz,
		int effectId, int parameterId, jvalue value ) {
	DroidSoundFX::NativeAudioProcessor * baseEffect = jni_AudioProcessor::getBaseEffect( effectId );
	baseEffect->changeParameter( parameterId, value );
}

// gets:
jobject Java_com_droidsoundfx_effect_NativeAudioProcessor_getObjectParameter(JNIEnv* env, jobject thiz,
		int effectId, int parameterId ) {
	DroidSoundFX::NativeAudioProcessor * baseEffect = jni_AudioProcessor::getBaseEffect( effectId );

	// TODO como fazer para gerenciar memoria do jobject?
	// usar o newglobalref e o deleteglobalref sempre?
	jobject fake;
	return fake;
}

char Java_com_droidsoundfx_effect_NativeAudioProcessor_getByteParameter(JNIEnv* env, jobject thiz,
		int effectId, int parameterId ) {
	// TODO  retornar char no lugar de byte? ou criar um array de 1 posicao?
	return 'f';
}

char Java_com_droidsoundfx_effect_NativeAudioProcessor_getCharParameter(JNIEnv* env, jobject thiz,
		int effectId, int parameterId ) {
	DroidSoundFX::NativeAudioProcessor * baseEffect = jni_AudioProcessor::getBaseEffect( effectId );
	return baseEffect->getCharParameter( parameterId );
}

double Java_com_droidsoundfx_effect_NativeAudioProcessor_getDoubleParameter(JNIEnv* env, jobject thiz,
		int effectId, int parameterId ) {
	DroidSoundFX::NativeAudioProcessor * baseEffect = jni_AudioProcessor::getBaseEffect( effectId );
	return baseEffect->getDoubleParameter( parameterId );
}

float Java_com_droidsoundfx_effect_NativeAudioProcessor_getFloatParameter(JNIEnv* env, jobject thiz,
		int effectId, int parameterId ) {
	DroidSoundFX::NativeAudioProcessor * baseEffect = jni_AudioProcessor::getBaseEffect( effectId );
	return baseEffect->getFloatParameter( parameterId );
}

int Java_com_droidsoundfx_effect_NativeAudioProcessor_getIntParameter(JNIEnv* env, jobject thiz,
		int effectId, int parameterId ) {
	DroidSoundFX::NativeAudioProcessor * baseEffect = jni_AudioProcessor::getBaseEffect( effectId );
	return baseEffect->getIntParameter( parameterId );
}

long Java_com_droidsoundfx_effect_NativeAudioProcessor_getLongParameter(JNIEnv* env, jobject thiz,
		int effectId, int parameterId ) {
	DroidSoundFX::NativeAudioProcessor * baseEffect = jni_AudioProcessor::getBaseEffect( effectId );
	return baseEffect->getLongParameter( parameterId );
}

short Java_com_droidsoundfx_effect_NativeAudioProcessor_getShortParameter(JNIEnv* env, jobject thiz,
		int effectId, int parameterId ) {
	DroidSoundFX::NativeAudioProcessor * baseEffect = jni_AudioProcessor::getBaseEffect( effectId );
	return baseEffect->getShortParameter( parameterId );
}

bool Java_com_droidsoundfx_effect_NativeAudioProcessor_getBooleanParameter(JNIEnv* env, jobject thiz,
		int effectId, int parameterId ) {
	DroidSoundFX::NativeAudioProcessor * baseEffect = jni_AudioProcessor::getBaseEffect( effectId );
	return baseEffect->getBoolParameter( parameterId );
}

}
#endif
