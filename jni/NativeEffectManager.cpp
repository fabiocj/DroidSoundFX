/*
 * NativeEffectManager.cpp
 *
 *  Created on: 19/05/2013
 *      Author: Leonardo
 */

#include "NativeEffectManager.h"

#include "NativeSoundManager.h"
#include "NativeSoundSettings.h"

namespace DroidSoundFX {

NativeEffectManager * NativeEffectManager::instance = NULL;

NativeEffectManager::NativeEffectManager() {
}

NativeEffectManager::~NativeEffectManager() {
}

NativeEffectManager * NativeEffectManager::getInstance() {
	if ( instance == NULL ) {
		instance = new NativeEffectManager();
	}

	return instance;
}

void NativeEffectManager::registerEffect( NativeAudioProcessor *  nap ) {
	NativeSoundManager::getInstance()->registerEffect( nap);
}

void NativeEffectManager::unregisterEffect( NativeAudioProcessor *  nap ) {
	NativeSoundManager::getInstance()->unregisterEffect( nap->getId() );
}

}


