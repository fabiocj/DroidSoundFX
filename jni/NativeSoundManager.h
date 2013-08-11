/*
 * SoundManager.h
 *
 *  Created on: 24/04/2013
 *      Author: Leonardo
 */

#ifndef SOUNDMANAGER_H_
#define SOUNDMANAGER_H_

#include "NativeSoundSettings.h"
#include "SoundCore.h"
#include "effects/NativeAudioProcessor.h"
#include "effects/JavaAudioProcessor.h"

#include <jni.h>
#include <map>
#include <string>

namespace DroidSoundFX {

class NativeSoundManager {

private:

	static NativeSoundManager * instance;

	SoundCore * soundCore; // only one soundCore
	std::map<int, NativeAudioProcessor *> * audioProcessorsMap;
	std::map<int, JavaAudioProcessor *> * javaEffectsMap;

	int nextEffectId;

	int getNextEffectId() {
		return nextEffectId++;
	}

	NativeSoundManager();
	virtual ~NativeSoundManager();

public:

	static NativeSoundManager * getInstance();

	void createEngine(JNIEnv * env, NativeSoundSettings * inputConfig, NativeSoundSettings * outputConfig);
	void destroyEngine();

	bool startAudioProcessing(JNIEnv * env);
	void stopAudioProcessing();

	int registerEffect( int nativeEffectID );
	int registerEffect( NativeAudioProcessor * effect );
	int registerEffect( JavaAudioProcessor * effect );
	void unregisterEffect( int effectId );

	bool addToSoundCore( JNIEnv * jniEnv, int effectId );
	void removeFromSoundCore( JNIEnv * jniEnv, int effectId );

	// TODO methods to reorder effects

	NativeAudioProcessor * getBaseEffect( int effectId );
	JavaAudioProcessor * getJavaEffect( int effectId );
};

} /* namespace DroidSoundFX */
#endif /* SOUNDMANAGER_H_ */
