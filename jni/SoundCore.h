/*
 * SoundCore.h
 *
 *  Created on: 11/04/2013
 *      Author: Leonardo
 */

#ifndef SOUNDCORE_H_
#define SOUNDCORE_H_

#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>

#include <stdlib.h>
#include <pthread.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <jni.h>

#include "NativeSoundSettings.h"
#include "utils/Thread.h"
#include "effects/NativeAudioProcessor.h"
#include "effects/JavaAudioProcessor.h"

//#define BUFFER_SIZE 2048 * 2 // minimo parece ser 2048 para 44KHz com 16bits
#define BUFFER_SIZE 1024

namespace DroidSoundFX {

#define BUFFER_ARRAY_SIZE 6
#define FLOAT_CONST ((float) 0x00FFFFFF)

class SoundCore {
	private:

		// engine interfaces
		SLObjectItf engineObject;
		SLEngineItf engine;

		// output mix interfaces
		SLObjectItf outputMixObject;

		// buffer queue player interfaces
		SLObjectItf playerObject;
		SLPlayItf player;
		SLAndroidSimpleBufferQueueItf playerBufferQueue;

		// recorder interfaces
		SLObjectItf recorderObject;
		SLRecordItf recorder;
		SLAndroidSimpleBufferQueueItf recorderBufferQueue;

		// buffers:
		short * inputBuffer[BUFFER_ARRAY_SIZE];
		short * outputBuffer[BUFFER_ARRAY_SIZE];
		float * processBuffer[BUFFER_ARRAY_SIZE];
		int indexCurrentRec;
		int indexFinishedRec;
		int indexCurrentPlay;
		unsigned int outputBufferSize;
		unsigned int inputBufferSize;

		// samples configuration
		NativeSoundSettings * outputSettings;
		NativeSoundSettings * inputSettings;

		// threads:
		DroidSoundFX::Thread * playerThread;
		DroidSoundFX::Thread * recorderThread;

		bool audioProcessing;

		// effects:
		std::vector<NativeAudioProcessor *> * audioProcessorsVector;
		std::vector<JavaAudioProcessor *> * javaEffectsVector;

		// JVM calls:
		JavaVM * javaVM;
		JNIEnv * jniEnv;

	public:
		SoundCore();
		virtual ~SoundCore();

		SLresult createEngine();
		SLresult createPlayer();
		SLresult createRecorder();

		SLresult prepareRecorder();
		SLresult stopRecorder();

		void destroyEngine();
		void destroyPlayer();
		void destroyRecorder();

		// buffers:
		void initBuffers();
		void destroyBuffers();

		void onFinishRecBuffer();
		void goToNextRecBuffer();
		void goToNextPlayBuffer();

		void processEffects();

		// threads:
		bool startProcessThreads(JNIEnv * env);
		void stopProcessThreads();

		// in/out requests
		SLresult requestRecord();
		SLresult requestPlayback();

		// effects:
		void initJavaEffects();
		void addEffect(NativeAudioProcessor * nap);
		void addEffect(JavaAudioProcessor * je);
		void removeEffect( int effectId );

		void initJNIEnv() {
			javaVM->AttachCurrentThread( &jniEnv, NULL );
		}

		void destroyJNIEnv() {
			javaVM->DetachCurrentThread();
		}

		DroidSoundFX::Thread* getThreadPlayer() {
			return playerThread;
		}

		DroidSoundFX::Thread* getThreadRecorder() {
			return recorderThread;
		}

		// TODO mudar para o manager:
		void setEnableAllEffects(bool enabled) {
			if ( audioProcessorsVector ) {
				NativeAudioProcessor *nap;
				for ( int i = 0; i < audioProcessorsVector->size(); i++ ) {
					nap = (* audioProcessorsVector)[i];
					nap->setEnabled( enabled );
				}
			}
		}

		const NativeSoundSettings* getInputSettings() {
			return this->inputSettings;
		}

		void setInputSettings( NativeSoundSettings* inputSettings) {
			this->inputSettings = inputSettings;
		}

		const NativeSoundSettings* getOutputSettings() {
			return this->outputSettings;
		}

		void setOutputSettings( NativeSoundSettings* outputSettings) {
			this->outputSettings = outputSettings;
		}

		bool isAudioProcessing() {
			return this->audioProcessing;
		}

};

} /* namespace DroidSoundFX */
#endif /* SOUNDCORE_H_ */
