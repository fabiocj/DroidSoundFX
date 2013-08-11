/*
 * LogTimer.h
 *
 *  Created on: 26/06/2013
 *      Author: Leonardo
 */

#ifndef LOGTIMER_H_
#define LOGTIMER_H_

#include <fstream>
#include <ctime>
#include <queue>

namespace DroidSoundFX {

class LogTimer {
private:
	std::queue<double> queueTimeBefore;
	std::queue<double> queueTimeAfter;

	std::ofstream logfile;

	double getTime();

public:
	LogTimer();
	virtual ~LogTimer();

	void openFile();
	void writeInLog();
	void closeFile();

	void addTimeBefore();
	void addTimeAfter();
};

} /* namespace DroidSoundFX */
#endif /* LOGTIMER_H_ */
