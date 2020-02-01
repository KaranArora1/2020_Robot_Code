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
		
		//Drivetrain
		int backLeftPosition, frontLeftPosition, backRightPosition, frontRightPosition;
		int backLeftVelocity, frontLeftVelocity, backRightVelocity, frontRightVelocity;
		double backLeftRPM, frontLeftRPM, backRightRPM, frontRightRPM;

		//Shooter
		int shooterRPM, slaveShooterRPM;

		//Ball Pickup

		//Climber

		//Indexer

		//Panel Spinner
		int spinneerPosition;
		int spinnerVelocity;
		double spinnerRPM;
	};

	virtual ~Logger();

	void logError(const char *msg, ... );
	void logInfo(const char *msg, ... );
	void logCSV(struct CSVVals *data);
	void Run(int *, int *, double *, double *);
	void Save();

    static Logger *instance() {
        if (!singlton)
        	singlton = new Logger();
        return singlton;
    }

private:

    MyTimer timer;

    struct timeval startTime;

    std::ofstream logFile;
    std::ofstream csvFile;

	Logger();
	static Logger *singlton;
};