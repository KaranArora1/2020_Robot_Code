/*
 * Logger.cpp
 *
 *  Created on: Jan 21, 2016
 *      Author: feds
 */

#include "Logger.h"

Logger *Logger::singlton = 0;

Logger::Logger() {
	gettimeofday(&startTime, 0);

	char timeString[64];
	time_t rawTime;
	struct tm * timeInfo;

	time(&rawTime);
	timeInfo = localtime (&rawTime);
	strftime(timeString, sizeof(timeString), "%g%m%e_%H%M", timeInfo);

	logFile.open("/home/lvuser/logFile" + (std::string)timeString + ".txt");
	csvFile.open("/home/lvuser/logFile" + (std::string)timeString + ".csv");

	std::cout << "INFO: THE LOGFILE FOR THIS SESSION IS NAMED " << (std::string)timeString << std::endl; 

	csvFile
		/*General Data*/
			<< "time" << ','
			<< "voltage" << ','
			<< "totalCurrent" << ','
			/*<< "backLeftPosition" << ','
			<< "frontLeftPosition" << ','
			<< "backRightPosition" << ','
			<< "frontRightPosition" << ','
			<< "backLeftVelocity" << ','
			<< "frontLeftVelocity" << ','
			<< "backRightVelocity" << ','
			<< "frontRightVelocity" << ','
			<< "backLeftRPM" << ','
			<< "frontLeftRPM" << ','
			<< "backRightRPM" << ','
			<< "frontRightRPM" << ','*/
			<< "backLeftCurrent" << ','
			<< "frontLeftCurrent" << ','
			<< "backRightCurrent" << ','
			<< "frontRightCurrent" << ','
			<< "shooterRPM" << ','
			<< "slaveShooterRPM" << ','
			/*<< "wristPosition" << ','
			<< "winchPosition" << ','
			<< "spinnerPosition" << ','
			<< "spinnerVelocity" << ','
			<< "spinnerRPM" << ','
			<< "confidence"*/
			<< std::endl;
}

void Logger::logInfo(const char *msg, ... ) {
	va_list args;
	va_start(args,msg);

	char buffer[256];
	vsnprintf(buffer, sizeof(buffer), msg, args);

	logFile << timer.getTotalTime() << " - [INFO] " << buffer << std::endl;
	std::cout << timer.getTotalTime() << " - [INFO] " << buffer << std::endl;
	Save();
}

void Logger::logError(const char *msg, ... ) {
	va_list args;
	va_start(args,msg);

	char buffer[256];
	vsnprintf(buffer, sizeof(buffer), msg, args);

	logFile << "[ERROR] " << buffer << std::endl;
	std::cerr << "[ERROR] " << buffer << std::endl;
	Save();
}

void Logger::logCSV(struct CSVVals *data) {
	
	double time = timer.getTotalTime();

	csvFile
		/*General Data*/
			<< time << ','
			<< data-> voltage << ','
			<< data-> totalCurrent << ','

			/*<< data-> backLeftPosition << ','
			<< data-> frontLeftPosition << ','
			<< data-> backRightPosition << ','
			<< data-> frontRightPosition << ','

			<< data-> backLeftVelocity << ','
			<< data-> frontLeftVelocity << ','
			<< data-> backRightVelocity << ','
			<< data-> frontRightVelocity << ',' 

			<< data-> backLeftRPM << ','
			<< data-> frontLeftRPM << ','
			<< data-> backRightRPM << ','
			<< data-> frontRightRPM << ','*/

			<< data-> backLeftCurrent << ','
			<< data-> frontLeftCurrent << ','
			<< data-> backRightCurrent << ','
			<< data-> frontRightCurrent << ','
			
			<< data-> shooterRPM << ','
			<< data-> slaveShooterRPM << ','
			/*<< data-> wristPosition << ','

			<< data-> winchPosition << ','

			<< data-> spinnerPosition << ','
			<< data-> spinnerVelocity << ','
			<< data-> spinnerRPM << ','
			<< data-> confidence << */ <<
			std::endl;
	Save();
}

void Logger::Save() {
	logFile.flush();
	csvFile.flush();
}

void Logger::Run(int * drivePositions, int * driveVelocities, double * driveRPMs, double * driveCurrents, double * shooterRPMs, 
				 int wristPosition, int spinnerPosition, int spinnerVelocity, double spinnerRPM, double confidence, int winchPos) {
	
	struct Logger::CSVVals csvData;

	//General
	csvData.totalCurrent = 0;
	csvData.voltage = 0;

	//Drive 
	/*csvData.backLeftPosition = drivePositions[0];
	csvData.frontLeftPosition = drivePositions[1];
	csvData.backRightPosition = drivePositions[2];
	csvData.frontRightPosition = drivePositions[3];

	csvData.backLeftVelocity = driveVelocities[0];
	csvData.frontLeftVelocity = driveVelocities[1];
	csvData.backRightVelocity = driveVelocities[2];
	csvData.frontRightVelocity = driveVelocities[3];

	csvData.backLeftRPM = driveRPMs[0];
	csvData.frontLeftRPM = driveRPMs[1];
	csvData.backRightRPM = driveRPMs[2];
	csvData.frontRightRPM = driveRPMs[3];*/

	csvData.backLeftCurrent = driveCurrents[0];
	csvData.frontLeftCurrent = driveCurrents[1];
	csvData.backRightCurrent = driveCurrents[2];
	csvData.frontRightCurrent = driveCurrents[3];

	//Climber
	//csvData.winchPosition = winchPos; Not wired

	//Shooter
	csvData.shooterRPM = shooterRPMs[0];
	csvData.slaveShooterRPM = shooterRPMs[1];

	//csvData.wristPosition = wristPosition; Not wired

	//Panel Spinner
	/*csvData.spinnerPosition = spinnerPosition;
	csvData.spinnerVelocity = spinnerVelocity;
	csvData.spinnerRPM = spinnerRPM;
	csvData.confidence = confidence; Not wired */
		
	logCSV(&csvData);
}

Logger::~Logger() {
	// TODO Auto-generated destructor stub
}
