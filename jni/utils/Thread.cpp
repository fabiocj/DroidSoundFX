/*
 * Thread.cpp
 *
 *  Created on: 11/04/2013
 *      Author: Leonardo
 */

#include "utils/Thread.h"
#include <stdlib.h>
#include <pthread.h>

namespace DroidSoundFX {

Thread::Thread( void *(*runnable)(void *), void *object) :
		mRunnable( runnable ),
		mObject( object ),
		mCond( PTHREAD_COND_INITIALIZER ),
		mMutex( PTHREAD_MUTEX_INITIALIZER )
{}

Thread::~Thread() {
}

bool Thread::start() {
	mKeepRunning = true;
	int error = pthread_create( &mThread, NULL, mRunnable, mObject );
	if ( error != 0 ) {
		return false;
	}

	return true;
}

void Thread::stop() {
	mKeepRunning = false;
}

void Thread::wait( unsigned int milis ) {
	pthread_mutex_lock( &mMutex );
	pthread_cond_timeout_np( &mCond, &mMutex, milis );
	pthread_mutex_unlock( &mMutex );
}

void Thread::wait() {
	pthread_mutex_lock( &mMutex );
	pthread_cond_wait( &mCond, &mMutex );
	pthread_mutex_unlock( &mMutex );
}

void Thread::notify() {
	pthread_mutex_lock( &mMutex );
	pthread_cond_signal( &mCond );
	pthread_mutex_unlock(&mMutex );
}

} /* namespace DroidSoundFX */
