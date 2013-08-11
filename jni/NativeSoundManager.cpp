/*
 * NativeSoundManager.cpp
 *
 *  Created on: 24/04/2013
 *      Author: Leonardo
 */

#include "NativeSoundManager.h"

#include "utils/exception.h"
#include "nativeEffects/Chorus.h"
#include "nativeEffects/Distortion.h"
#include "nativeEffects/SimpleDelayEffect.h"
#include "nativeEffects/SimpleReverb.h"

#include "utils/myutils.h"

#define RETURN_ERROR -1;

namespace DroidSoundFX {

NativeSoundManager * NativeSoundManager::instance = NULL;

NativeSoundManager::NativeSoundManager() {
	soundCore = new SoundCore();
	audioProcessorsMap = NULL;
	javaEffectsMap = NULL;

	nextEffectId = 1;
}

NativeSoundManager::~NativeSoundManager() {
}

NativeSoundManager * NativeSoundManager::getInstance() {
	if ( instance == NULL ) {
		instance = new NativeSoundManager();
	}

	return instance;
}

void NativeSoundManager::createEngine(JNIEnv * env, NativeSoundSettings * inputConfig, NativeSoundSettings * outputConfig ) {

	soundCore->setInputSettings( inputConfig );
	soundCore->setOutputSettings( outputConfig );

	SLresult result = soundCore->createEngine();
	if ( SL_RESULT_SUCCESS != result ) {
		DroidSoundFX::Exception::throwException(env, "SoundCore.createEngine failed!");
		return;
	}

	result = soundCore->createPlayer();
	if ( SL_RESULT_SUCCESS != result ) {
		DroidSoundFX::Exception::throwException(env, "SoundCore.createPlayer failed!");
		return;
	}

	result = soundCore->createRecorder();
	if ( SL_RESULT_SUCCESS != result ) {
		DroidSoundFX::Exception::throwException(env, "SoundCore.createRecorder failed!");
		return;
	}
}

void NativeSoundManager::destroyEngine() {
	LOGI( "SoundManager::destroyEngine" );
	if ( soundCore ) {
		if ( soundCore->isAudioProcessing() ) {
			soundCore->stopProcessThreads();
		}

		soundCore->destroyBuffers();
		soundCore->destroyRecorder();
		soundCore->destroyPlayer();
		soundCore->destroyEngine();
	}
	LOGI( "SoundManager::destroyEngine OK" );
}

bool NativeSoundManager::startAudioProcessing(JNIEnv * env) {
	if ( soundCore ) {
		return soundCore->startProcessThreads( env );
	}

	return false;
}

void NativeSoundManager::stopAudioProcessing() {
	if ( soundCore ) {
		soundCore->stopProcessThreads();
	}
}

int NativeSoundManager::registerEffect( int nativeEffectID ) {
	LOGI( "SoundManager::registerEffect, nativeEffectID = %d", nativeEffectID );
	NativeAudioProcessor * baseEffect;

	switch ( nativeEffectID ) {
		case 0:
			baseEffect = new DroidSoundFX::SimpleDelayEffect();
			break;
		case 1:
			baseEffect = new DroidSoundFX::SimpleReverb();
			break;
		case 2:
			baseEffect = new DroidSoundFX::Chorus();
			break;
		case 3:
		default:
			baseEffect = new DroidSoundFX::Distortion();
	}


	return this->registerEffect( baseEffect );
}

int NativeSoundManager::registerEffect( NativeAudioProcessor * effect ) {
	LOGD("SoundManager::addEffect, NativeAudioProcessor, audioProcessorsMap = %d", audioProcessorsMap);

	if ( audioProcessorsMap == NULL ) {
		audioProcessorsMap = new std::map<int, NativeAudioProcessor *>();
	}

	int effectId = this->getNextEffectId();
	effect->setId( effectId );

	LOGD("effectId = %d", effectId);

	audioProcessorsMap->insert( std::pair<int, NativeAudioProcessor *>( effectId, effect ) );

	LOGD("effectId = %d, insert!", effectId);

	return effectId;
}

int NativeSoundManager::registerEffect( JavaAudioProcessor * effect ) {
	int effectId = this->registerEffect( (NativeAudioProcessor *) effect );

	if ( javaEffectsMap == NULL ) {
		javaEffectsMap = new std::map<int, JavaAudioProcessor *>();
	}

	javaEffectsMap->insert( std::pair<int, JavaAudioProcessor *>( effectId, effect ) );

	return effectId;
}

void NativeSoundManager::unregisterEffect( int effectId ) {
	int removed;

	if ( audioProcessorsMap ) {
		removed = audioProcessorsMap->erase( effectId );
		if ( ! removed ) {
			return;
		}
	}

	if ( audioProcessorsMap ) {
		removed = audioProcessorsMap->erase( effectId );
		if ( removed ) {
			return;
		}
	}

	if ( javaEffectsMap ) {
		javaEffectsMap->erase( effectId );
	}
}

void NativeSoundManager::removeFromSoundCore( JNIEnv * jniEnv, int effectId ) {
	if ( soundCore ) {
		if ( soundCore->isAudioProcessing() ) {
			Exception::throwException( jniEnv, "Can't remove an effect while audio is been processed." );
			return;
		}
	}

	soundCore->removeEffect( effectId );
}

NativeAudioProcessor * NativeSoundManager::getBaseEffect( int effectId ) {
	std::map<int, NativeAudioProcessor *>::iterator it = audioProcessorsMap->find( effectId );
	if ( it != audioProcessorsMap->end() ) {
		return it->second;
	}

	return NULL;
}

JavaAudioProcessor * NativeSoundManager::getJavaEffect( int effectId ) {
	std::map<int, JavaAudioProcessor *>::iterator it = javaEffectsMap->find( effectId );
	if ( it != javaEffectsMap->end() ) {
		return it->second;
	}

	return NULL;
}

bool NativeSoundManager::addToSoundCore( JNIEnv * jniEnv, int effectId ) {
	if ( soundCore->isAudioProcessing() ) {
		Exception::throwException( jniEnv, "Can't add an effect while audio is been processed." );
		return false;
	}

	LOGD("soundCore = %d", soundCore);
	LOGD("audioProcessorsMap = %d", audioProcessorsMap);

	if ( audioProcessorsMap ) {

		std::map<int, NativeAudioProcessor *>::iterator it = audioProcessorsMap->find( effectId );
		if ( it != audioProcessorsMap->end() ) {
			// is it a BaseEffect?
			std::map<int, NativeAudioProcessor *>::iterator baseIt = audioProcessorsMap->find( effectId );
			if ( baseIt != audioProcessorsMap->end() ) {
				soundCore->addEffect( (NativeAudioProcessor *)  it->second );
			} else {// NO! it's a JavaEffect!!
				soundCore->addEffect( (JavaAudioProcessor *)  it->second );
			}

			return true;
		}

		LOGD("effectsId = %d, nor found!", effectId);

	}



	return false;
}

} /* namespace DroidSoundFX */
