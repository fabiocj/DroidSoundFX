/*
 * LogTimer.cpp
 *
 *  Created on: 26/06/2013
 *      Author: Leonardo
 */

#include "LogTimer.h"

#include "myutils.h"

namespace DroidSoundFX {

LogTimer::LogTimer() {
}

LogTimer::~LogTimer() {
}

void LogTimer::openFile() {
	logfile.open( "/storage/sdcard0/playLogFile.csv" );

	if ( logfile.is_open() ) {
		LOGI("file opened!!!");
	} else {
		LOGE("file open ERROR");
	}
}

double LogTimer::getTime() {
	struct timeval time;
	gettimeofday( &time, NULL );
	return time.tv_sec * 1000 + time.tv_usec / 1000 ;
}

void LogTimer::closeFile() {
	LOGI("LogTimer::closeFile()");
	logfile.close();
}

void LogTimer::addTimeBefore() {
	queueTimeBefore.push( this->getTime() );
}

void LogTimer::addTimeAfter() {
	queueTimeAfter.push( this->getTime() );
}

void LogTimer::writeInLog() {
	double millisBefore = queueTimeBefore.front();
	queueTimeBefore.pop();
	double millisAfter = queueTimeAfter.front();
	queueTimeAfter.pop();

	//LOGI("write = %f", (millisAfter - millisBefore) );
	logfile << (millisAfter - millisBefore) << "\n";
}

} /* namespace DroidSoundFX */
