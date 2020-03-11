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

		//General
		double voltage;
		double totalCurrent;

		//Joystick Values
		double leftJoyY;
		double rightJoyX;
		
		//Drivetrain
		int backLeftPosition, frontLeftPosition, backRightPosition, frontRightPosition;
		int backLeftVelocity, frontLeftVelocity, backRightVelocity, frontRightVelocity;
		double backLeftRPM, frontLeftRPM, backRightRPM, frontRightRPM;
		double backLeftCurrent, frontLeftCurrent, backRightCurrent, frontRightCurrent;

		//Shooter
		int shooterRPM, slaveShooterRPM;
		int wristPosition;

		//Ball Pickup

		//Climber
		int winchPosition;

		//Indexer

		//Panel Spinner
		int spinnerPosition;
		int spinnerVelocity;
		double spinnerRPM;
		double confidence;
	};

	virtual ~Logger();

	void logError(const char *msg, ... );
	void logInfo(const char *msg, ... );
	void logCSV(struct CSVVals *data);
	void Run(int *, int *, double *, double *, double*, int, int, int, double, double, int, double, double, double, double);
	void Run(int *, int *, double, double, int, int);
	void Run(int, int);
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