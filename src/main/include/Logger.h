/*
 * Logger.h
 *
 *  Created on: Jan 21, 2016
 *      Author: feds
 */

#pragma once

#include "MyTimer.h"
#include "RobotMap.h"

class Logger {
public:
	struct CSVVals {
		double voltage;
		double totalCurrent;

		int motor1Position, motor2Position, motor3Position, motor4Position;
		int motor1Velocity, motor2Velocity, motor3Velocity, motor4Velocity;
	};

	virtual ~Logger();

	void logError(const char *msg, ... );
	void logInfo(const char *msg, ... );
	void logCSV(struct CSVVals *data);
	void Run();

    static Logger *instance()
    {
        if (!singlton)
        	singlton = new Logger();
        return singlton;
    }
private:

    MyTimer timer;

    struct timeval startTime;

    std::ofstream logFile;
    std::ofstream csvFile;

    void save();

	Logger();
	static Logger *singlton;
};