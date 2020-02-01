/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "YourTimer.h"

YourTimer::YourTimer() {
	SetStart();
}

void YourTimer::SetStart() {
	gettimeofday(&start, 0);
	gettimeofday(&last, 0);
}

double YourTimer::Total() {
	timeval current;
	gettimeofday(&current, 0);
	
	return (current.tv_sec - start.tv_sec) + (current.tv_usec - start.tv_usec) / 1000000.0;
}

void YourTimer::SetDiffStart() {
	gettimeofday(&last, 0);
}

double YourTimer::Diff(bool resetLast = true) {
	timeval current;
	gettimeofday(&current, 0);
	
	double diff = (current.tv_sec - last.tv_sec) + (current.tv_usec - last.tv_usec) / 1000000.0;

	if (resetLast)
		last = current;
	return diff;
}
