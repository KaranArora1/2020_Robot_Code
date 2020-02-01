/*
 * timer.cpp
 *
 *  Created on: Feb 20, 2016
 *      Author: feds
 */
#include "MyTimer.h"

MyTimer::MyTimer()
{
	gettimeofday(&startTime, 0);
	lastTime = startTime;
}

// Get difference in time
double MyTimer::getDt()
{
	timeval thisTime;
	gettimeofday(&thisTime, 0);

	double timeDiff = (thisTime.tv_sec-lastTime.tv_sec) + (thisTime.tv_usec-lastTime.tv_usec) / 1000000.0;
	lastTime = thisTime;
	return timeDiff;
}

// Get total time since robot was started or reset()
double MyTimer::getTotalTime()
{
	timeval thisTime;
	gettimeofday(&thisTime, 0);
	return (thisTime.tv_sec-startTime.tv_sec) + (thisTime.tv_usec-startTime.tv_usec) / 1000000.0;
}

// Resets start time
void MyTimer::reset()
{
	gettimeofday(&startTime, 0);
	lastTime = startTime;
}
