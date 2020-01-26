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
	diffTime = startTime;
}

double MyTimer::getDt()
{
	struct timeval thisTime;
	gettimeofday(&thisTime, 0);

	double dt = (thisTime.tv_sec-lastTime.tv_sec)+(thisTime.tv_usec-lastTime.tv_usec)/1000000.0;
	lastTime = thisTime;
	return dt;
}

double MyTimer::getTotalTime()
{
	struct timeval thisTime;
		gettimeofday(&thisTime, 0);
		return (thisTime.tv_sec-startTime.tv_sec)+(thisTime.tv_usec-startTime.tv_usec)/1000000.0;
}

void MyTimer::reset()
{
	gettimeofday(&startTime, 0);
	lastTime = startTime;
}

void MyTimer::diffBegin()
{
	gettimeofday(&diffTime, 0);
}

double MyTimer::getDiff()
{
	struct timeval thisTime;
	gettimeofday(&thisTime, 0);
	return (thisTime.tv_sec-diffTime.tv_sec)+(thisTime.tv_usec-diffTime.tv_usec)/1000000.0;
}
