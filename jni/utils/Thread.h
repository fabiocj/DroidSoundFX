/*
 * Thread.h
 *
 *  Created on: 11/04/2013
 *      Author: Leonardo
 */

#ifndef THREAD_H_
#define THREAD_H_

#include <pthread.h>

namespace DroidSoundFX {

class Thread {
private:
	pthread_t mThread;
	pthread_cond_t mCond;
	pthread_mutex_t mMutex;

	void *(*mRunnable)(void *);
	void *mObject;
	bool mKeepRunning;

public:
	Thread(void *(*runnable)(void *), void *object);
	virtual ~Thread();

	bool start();
	void stop();
	void wait();
	void wait( unsigned int milis );
	void notify();

	bool isRunning() {
		return mKeepRunning;
	}

};

} /* namespace DroidSoundFX */
#endif /* THREAD_H_ */
