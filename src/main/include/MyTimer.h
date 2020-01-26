/*
 * timer.h
 *
 *  Created on: Feb 20, 2016
 *      Author: feds
 */

#pragma once

#include "RobotMap.h"

class MyTimer{
public:
	MyTimer();
	double getTotalTime();
	void reset();
	double getDt();

	void diffBegin();
	double getDiff();
private:
		struct timeval startTime;
		struct timeval lastTime;
		struct timeval diffTime;
		double dt = 0;
};
