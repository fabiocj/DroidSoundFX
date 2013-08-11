/*
 * SoundCore.cpp
 *
 *  Created on: 11/04/2013
 *      Author: Leonardo
 */

#include "SoundCore.h"

#include "utils/Thread.h"
#include "effects/JavaAudioProcessor.h"
#include "nativeEffects/SimpleDelayEffect.h"
#include "utils/myutils.h"
#include "utils/exception.h"
#include "utils/LogTimer.h"

#include <iostream>
#include <ctime>

#ifdef __cplusplus
extern "C" {

	DroidSoundFX::LogTimer logtimer;

	// this callback handler is called every time a buffer finishes playing
	void playerCallback(SLAndroidSimpleBufferQueueItf bq, void *context) {

		logtimer.addTimeAfter();
		logtimer.writeInLog();
	}


	// this callback handler is called every time a buffer finishes recording
	void recorderCallback(SLAndroidSimpleBufferQueueItf bq, void *context) {
		//logtimer.addTimeAfter();
		//logtimer.writeInLog();


		DroidSoundFX::SoundCore * s = (DroidSoundFX::SoundCore *) context;

		s->onFinishRecBuffer();

		s->getThreadPlayer()->notify();
		s->getThreadRecorder()->notify();

	}

}
#endif

namespace DroidSoundFX {

SoundCore::SoundCore() {
	outputSettings = NULL;
	inputSettings = NULL;

	playerThread = NULL;
	recorderThread = NULL;

	javaEffectsVector = NULL;
	audioProcessorsVector = NULL;

	javaVM = NULL;
	jniEnv = NULL;

	audioProcessing = false;

	for( int i = 0; i < BUFFER_ARRAY_SIZE; i++ ) {
		inputBuffer[i] = NULL;
		outputBuffer[i] = NULL;
		processBuffer[i] = NULL;
	}
}

SoundCore::~SoundCore() {
	LOGI("SoundCore::~SoundCore");

	delete outputSettings;
	delete inputSettings;
	delete javaVM;
	delete jniEnv;

	if ( audioProcessorsVector ) {
		LOGI("SoundCore::~SoundCore, delete effectsVector elements");
		for( int i = 0; i < audioProcessorsVector->size(); i++ ) {
			delete ((* audioProcessorsVector)[i]);
		}

		LOGI("SoundCore::~SoundCore, delete effectsVector!");

		delete audioProcessorsVector;
		delete javaEffectsVector;
		delete audioProcessorsVector;
	}

	LOGI("SoundCore::~SoundCore OK!");

}

SLresult SoundCore::createEngine() {
	// create engine
	SLresult result = slCreateEngine(&engineObject , 0, NULL, 0, NULL, NULL);
	if(result != SL_RESULT_SUCCESS) return result;

	// realize the engine
	result = (*engineObject)->Realize(engineObject, SL_BOOLEAN_FALSE);
	if(result != SL_RESULT_SUCCESS) return result;

	// get the engine interface, which is needed in order to create other objects
	result = (*engineObject)->GetInterface(engineObject, SL_IID_ENGINE, &engine);
	if(result != SL_RESULT_SUCCESS) return result;

	return result;
}

SLresult SoundCore::createPlayer() {
	SLuint32 samplesPerSec = outputSettings->getSamplingRate();
	SLuint32 channels = outputSettings->getChannels();
	SLuint16 bitsPerSample = outputSettings->getBitsPerSample();

	initBuffers();

	if ( ! channels ) {
		return SL_RESULT_PARAMETER_INVALID;
	}

	SLresult result;
	// configure audio source
	SLDataLocator_AndroidSimpleBufferQueue loc_bufq;// = { SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE, 2 };
	loc_bufq.locatorType = SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE;
	loc_bufq.numBuffers = 2;

	const SLInterfaceID ids[] = { SL_IID_VOLUME };
	const SLboolean req[] = { SL_BOOLEAN_FALSE };
	result = (*engine)->CreateOutputMix(engine, &outputMixObject, 1, ids, req);
	if (result != SL_RESULT_SUCCESS) return result;

	// realize outputMixObject
	result = (*outputMixObject)->Realize(outputMixObject, SL_BOOLEAN_FALSE);
	if (result != SL_RESULT_SUCCESS) return result;

	int speakers;
	if ( channels > 1 ) {
		speakers = SL_SPEAKER_FRONT_LEFT | SL_SPEAKER_FRONT_RIGHT;
	} else {
		speakers = SL_SPEAKER_FRONT_CENTER;
	}

	SLDataFormat_PCM format_pcm;// = {SL_DATAFORMAT_PCM,channels, sr, SL_PCMSAMPLEFORMAT_FIXED_16, SL_PCMSAMPLEFORMAT_FIXED_16, speakers, SL_BYTEORDER_LITTLEENDIAN};
	format_pcm.formatType = SL_DATAFORMAT_PCM;
	format_pcm.numChannels = channels;
	format_pcm.samplesPerSec = samplesPerSec;
	format_pcm.bitsPerSample = bitsPerSample;
	format_pcm.containerSize = bitsPerSample;
	format_pcm.channelMask = speakers;
	format_pcm.endianness = SL_BYTEORDER_LITTLEENDIAN;

	SLDataSource audioSrc;// = {&loc_bufq, &format_pcm};
	audioSrc.pLocator = &loc_bufq;
	audioSrc.pFormat = &format_pcm;

	// configure audioSnk
	SLDataLocator_OutputMix loc_outmix;// = {SL_DATALOCATOR_OUTPUTMIX, p->outputMixObject};
	loc_outmix.locatorType = SL_DATALOCATOR_OUTPUTMIX;
	loc_outmix.outputMix = outputMixObject;

	SLDataSink audioSnk;// = {&loc_outmix, NULL};
	audioSnk.pLocator = &loc_outmix;
	audioSnk.pFormat = NULL;

	// create playerObject
	const SLInterfaceID ids1[] = { SL_IID_ANDROIDSIMPLEBUFFERQUEUE };
	const SLboolean req1[] = { SL_BOOLEAN_TRUE };

	result = (*engine)->CreateAudioPlayer(engine, &playerObject, &audioSrc, &audioSnk, 1, ids1, req1);
	if(result != SL_RESULT_SUCCESS) return result;

	// realize playerObject
	result = (*playerObject)->Realize(playerObject, SL_BOOLEAN_FALSE);
	if(result != SL_RESULT_SUCCESS) return result;

	// get the player interface
	result = (*playerObject)->GetInterface(playerObject, SL_IID_PLAY, &player);
	if(result != SL_RESULT_SUCCESS) return result;

	// get the playerBufferQueue interface
	result = (*playerObject)->GetInterface(playerObject, SL_IID_ANDROIDSIMPLEBUFFERQUEUE, &playerBufferQueue);
	if(result != SL_RESULT_SUCCESS) return result;

	// TODO vou precisar? alem de testes de desempenho
	// register playerBufferQueue's callback
	result = (*playerBufferQueue)->RegisterCallback(playerBufferQueue, playerCallback, this);
	if(result != SL_RESULT_SUCCESS) return result;

	// playing
	return (*player)->SetPlayState(player, SL_PLAYSTATE_PLAYING);

}

SLresult SoundCore::createRecorder() {
	SLuint32 samplesPerSec = inputSettings->getSamplingRate();
	SLuint32 channels = inputSettings->getChannels();
	SLuint16 bitsPerSample = inputSettings->getBitsPerSample();

	if ( ! channels ) {
		return SL_RESULT_PARAMETER_INVALID;
	}

	SLresult result;

	SLDataLocator_IODevice loc_dev;// = {SL_DATALOCATOR_IODEVICE, SL_IODEVICE_AUDIOINPUT, SL_DEFAULTDEVICEID_AUDIOINPUT, NULL};
	loc_dev.locatorType = SL_DATALOCATOR_IODEVICE;
	loc_dev.deviceType = SL_IODEVICE_AUDIOINPUT;
	loc_dev.deviceID = SL_DEFAULTDEVICEID_AUDIOINPUT;
	loc_dev.device = NULL;

	SLDataSource audioSrc;// = {&loc_dev, NULL};
	audioSrc.pLocator = &loc_dev;
	audioSrc.pFormat = NULL;

	int speakers;
	if (channels > 1) {
		speakers = SL_SPEAKER_FRONT_LEFT | SL_SPEAKER_FRONT_RIGHT;
	} else {
		speakers = SL_SPEAKER_FRONT_CENTER;
	}

	SLDataLocator_AndroidSimpleBufferQueue loc_bq;// = { SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE, 2 };
	loc_bq.locatorType = SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE;
	loc_bq.numBuffers = 2;

	SLDataFormat_PCM format_pcm;// = {SL_DATAFORMAT_PCM, channels, sr, SL_PCMSAMPLEFORMAT_FIXED_16, SL_PCMSAMPLEFORMAT_FIXED_16, speakers, SL_BYTEORDER_LITTLEENDIAN};
	format_pcm.formatType = SL_DATAFORMAT_PCM;
	format_pcm.numChannels = channels;
	format_pcm.samplesPerSec = samplesPerSec;
	format_pcm.bitsPerSample = bitsPerSample;
	format_pcm.containerSize = bitsPerSample;
	format_pcm.channelMask = speakers;
	format_pcm.endianness = SL_BYTEORDER_LITTLEENDIAN;

	SLDataSink audioSnk;// = {&loc_bq, &format_pcm};
	audioSnk.pLocator = &loc_bq;
	audioSnk.pFormat = &format_pcm;

	// creating recorderObject, requires android.permission.RECORD_AUDIO
	const SLInterfaceID id[1] = { SL_IID_ANDROIDSIMPLEBUFFERQUEUE };
	const SLboolean req[1] = { SL_BOOLEAN_TRUE };
	result = (*engine)->CreateAudioRecorder(engine, &recorderObject, &audioSrc, &audioSnk, 1, id, req);
	if (SL_RESULT_SUCCESS != result) return result;

	result = (*recorderObject)->Realize( recorderObject, SL_BOOLEAN_FALSE );
	if (SL_RESULT_SUCCESS != result) return result;

	result = (*recorderObject)->GetInterface(recorderObject, SL_IID_RECORD, &recorder);
	if (SL_RESULT_SUCCESS != result) return result;

	result = (*recorderObject)->GetInterface(recorderObject, SL_IID_ANDROIDSIMPLEBUFFERQUEUE, &recorderBufferQueue);
	if (SL_RESULT_SUCCESS != result) return result;

	result = (*recorderBufferQueue)->RegisterCallback(recorderBufferQueue, recorderCallback, this);
	return result;
}

SLresult SoundCore::prepareRecorder() {
	return (*recorder)->SetRecordState( recorder, SL_RECORDSTATE_RECORDING );
}

SLresult SoundCore::stopRecorder() {
	return (*recorder)->SetRecordState( recorder, SL_RECORDSTATE_STOPPED );
}

void SoundCore::destroyEngine() {
	LOGI("SoundCore::destroyEngine");

	if ( engineObject != NULL ) {
		(*engineObject)->Destroy( engineObject );
		engineObject = NULL;
		engine = NULL;
	}

	LOGI("SoundCore::destroyEngine OK");
}

void SoundCore::destroyPlayer() {
	LOGI("SoundCore::destroyPlayer");

	if ( playerObject != NULL ) {
		(*playerObject)->Destroy( playerObject );
		playerObject = NULL;
		player = NULL;
		playerBufferQueue = NULL;
	}

	if ( outputMixObject != NULL ) {
		(*outputMixObject)->Destroy( outputMixObject );
		outputMixObject = NULL;
	}

	LOGI("SoundCore::destroyPlayer OK!");

}

void SoundCore::destroyRecorder() {
	LOGI("SoundCore::destroyRecorder");

	if (recorderObject != NULL) {
		(*recorderObject)->Destroy( recorderObject );
		recorderObject = NULL;
		recorder = NULL;
		recorderBufferQueue = NULL;
	}

	LOGI("SoundCore::destroyRecorder OK!");
}

// threads:
void *playerThreadFunction( void *instance ) {
	LOGI( "playerThreadFunction started" );

	DroidSoundFX::SoundCore * soundCore = (SoundCore *) instance;

	DroidSoundFX::Thread * thiz = soundCore->getThreadPlayer();

	soundCore->initJNIEnv();

	soundCore->initJavaEffects();

	while ( thiz->isRunning() ) {

		thiz->wait();

		if ( thiz->isRunning() ) {

			soundCore->processEffects();

			soundCore->requestPlayback();

		}

	}

	soundCore->destroyJNIEnv();

	LOGI( "playerThreadFunction finished!" );

}

void *recorderThreadFunction( void *instance ) {
	DroidSoundFX::SoundCore * soundCore = (SoundCore *) instance;
	DroidSoundFX::Thread * thiz = soundCore->getThreadRecorder();

	soundCore->prepareRecorder();

	logtimer.openFile();

	while ( thiz->isRunning() ) {
		soundCore->requestRecord();

		thiz->wait();

		if ( ! thiz->isRunning() ) {
			break;
		}

		soundCore->goToNextRecBuffer();
	}

	soundCore->stopRecorder();

	LOGI( "recorderThreadFunction finished!" );

	logtimer.closeFile();
}

bool SoundCore::startProcessThreads(JNIEnv * env) {
	jint rs = env->GetJavaVM( &javaVM  );
	if ( rs != JNI_OK ) {
		DroidSoundFX::Exception::throwException(env, "GetJavaVM failed!");
		return false;
	}

	audioProcessing = true;

	if ( playerThread ) {
		delete playerThread;
	}
	playerThread = new Thread( playerThreadFunction, this );
	playerThread->start();

	if ( recorderThread ) {
		delete recorderThread;
	}
	recorderThread = new Thread( recorderThreadFunction, this );
	recorderThread->start();

	return true;
}

void SoundCore::stopProcessThreads() {
	playerThread->stop();
	recorderThread->stop();

	recorderThread->notify();
	playerThread->notify();

	audioProcessing = false;
}

SLresult SoundCore::requestRecord() {

	return (*recorderBufferQueue)->Enqueue(recorderBufferQueue, inputBuffer[ indexCurrentRec ], inputBufferSize);
}

SLresult SoundCore::requestPlayback() {
	logtimer.addTimeBefore();
	return (*playerBufferQueue)->Enqueue(playerBufferQueue, outputBuffer[ indexCurrentPlay ], outputBufferSize );
}


// buffers handlers:
void SoundCore::goToNextRecBuffer() {
	if ( indexCurrentRec == BUFFER_ARRAY_SIZE - 1 ) {
		indexCurrentRec = 0;
	} else {
		indexCurrentRec++;
	}
}

void SoundCore::onFinishRecBuffer() {
	if ( indexFinishedRec == BUFFER_ARRAY_SIZE - 1 ) {
		indexFinishedRec = 0;
	} else {
		indexFinishedRec++;
	}
}

void SoundCore::goToNextPlayBuffer() {
	if ( indexCurrentPlay == BUFFER_ARRAY_SIZE - 1 ) {
		indexCurrentPlay = 0;
	} else {
		indexCurrentPlay++;
	}
}

void SoundCore::processEffects() {
	int i, j;

	short * outBuffer = outputBuffer[indexCurrentPlay];
	float * pBuffer = processBuffer[indexCurrentPlay];
	short * inBuffer = inputBuffer[indexFinishedRec];

	// efeito de "lentidao", prolongando o sample e deixando o som mais grave
	// j = 0, j += 2
	//outBuffer[j] = outBuffer[j + 1] = inBuffer[i];

	for (i = 0; i < BUFFER_SIZE; i++) {
		pBuffer[i] = inBuffer[i] / FLOAT_CONST;
	}

	if ( audioProcessorsVector ) {
		NativeAudioProcessor *nap;
		for ( i = 0; i < audioProcessorsVector->size(); i++ ) {
			nap = (* audioProcessorsVector)[i];
			if ( nap->isEnabled() ) {
				nap->process( pBuffer, BUFFER_SIZE );
			}
		}
	}

	if ( outputSettings->getChannels() > 1 )  {
		for ( i = 0, j = 0; i < BUFFER_SIZE; i++, j += 2 ) {
			outBuffer[j] = outBuffer[j+1] = pBuffer[i] * FLOAT_CONST;
		}
	} else {
		for ( i = 0; i < BUFFER_SIZE; i++) {
			outBuffer[i] = pBuffer[i] * FLOAT_CONST;
		}
	}

}

void SoundCore::initBuffers() {
	indexCurrentPlay = indexCurrentRec = 0;
	indexFinishedRec = -1;

	for (int i = 0; i < BUFFER_ARRAY_SIZE; i++) {
		inputBuffer[i] = (short *) calloc( BUFFER_SIZE * inputSettings->getChannels(), sizeof( short ) );
		outputBuffer[i] = (short *) calloc( BUFFER_SIZE * outputSettings->getChannels(), sizeof( short ) );
		processBuffer[i] = (float *) calloc( BUFFER_SIZE, sizeof( float ) );
	}

	inputBufferSize = BUFFER_SIZE * sizeof( short ) * inputSettings->getChannels();
	outputBufferSize = BUFFER_SIZE * sizeof( short ) * outputSettings->getChannels();
}

void SoundCore::destroyBuffers() {
	LOGI("SoundCore::destroyBuffers");

	for (int i = 0; i < BUFFER_ARRAY_SIZE; i++) {
		free( inputBuffer[i] );
		free( outputBuffer[i] );
		free( processBuffer[i] );
	}

	LOGI("SoundCore::destroyBuffers OK");
}

void SoundCore::initJavaEffects() {
	if ( javaEffectsVector ) {
		JavaAudioProcessor * je;

		for (int i = 0; i < javaEffectsVector->size(); i++) {
			je = (* javaEffectsVector)[i];
			je->init( jniEnv );
		}
	}

}

void SoundCore::addEffect(NativeAudioProcessor * nap) {
	LOGD("SoundCore.addEffect, nap.id = %d", nap->getId() );

	if ( audioProcessorsVector == NULL ) {
		audioProcessorsVector = new std::vector<NativeAudioProcessor *>( 0 );
	}

	audioProcessorsVector->insert( audioProcessorsVector->end(), nap );
}

void SoundCore::addEffect(JavaAudioProcessor * je) {
	if ( javaEffectsVector == NULL ) {
		javaEffectsVector = new std::vector<JavaAudioProcessor *>( 0 );
	}

	javaEffectsVector->insert( javaEffectsVector->end(), je );

	this->addEffect( (NativeAudioProcessor *) je );
}

void SoundCore::removeEffect( int effectId ) {
	if ( audioProcessorsVector == NULL ) {
		return;
	}

	NativeAudioProcessor * toRemove = NULL;
	NativeAudioProcessor * nap;

	std::vector<NativeAudioProcessor *>::iterator it;

	for ( it = audioProcessorsVector->begin(); it < audioProcessorsVector->end(); it++ ) {
		nap = (* it);
		if ( nap->getId() == effectId ) {
			audioProcessorsVector->erase( it );
			toRemove = nap;
			break;
		}
	}

	if ( toRemove == NULL ) {
		return;
	}

	if ( javaEffectsVector ) {
		std::vector<JavaAudioProcessor *>::iterator javaIt;
		for ( javaIt = javaEffectsVector->begin(); javaIt < javaEffectsVector->end(); javaIt++ ) {
			nap = (* javaIt);
			if ( nap->getId() == effectId ) {
				javaEffectsVector->erase( javaIt );
			}
		}
	}

}

} /* namespace DroidSoundFX */
