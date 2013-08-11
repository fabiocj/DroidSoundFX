/*
 * NativeEffectManager.h
 *
 *  Created on: 19/05/2013
 *      Author: Leonardo
 */

#ifndef NATIVEEFFECTMANAGER_H_
#define NATIVEEFFECTMANAGER_H_

#include <jni.h>

#include "effects/NativeAudioProcessor.h"

namespace DroidSoundFX {
	class NativeEffectManager {

	private:

		static NativeEffectManager * instance;

		NativeEffectManager();
		virtual ~NativeEffectManager();

	public:

		static NativeEffectManager * getInstance();

		void registerEffect( NativeAudioProcessor * nap );
		void unregisterEffect( NativeAudioProcessor * nap );

	};
}

#endif /* NATIVEEFFECTMANAGER_H_ */
