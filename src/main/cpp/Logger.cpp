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
			<< "motor1Position" << ','
			<< "motor2Position" << ','
			<< "motor3Position" << ','
			<< "motor4Position" << ','
			<< "motor1Velocity" << ','
			<< "motor2Velocity" << ','
			<< "motor3Velocity" << ','
			<< "motor4Velocity" << std::endl;
}

void Logger::logInfo(const char *msg, ... )
{
	va_list args;
	va_start(args,msg);

	char buffer[256];
	vsnprintf(buffer, sizeof(buffer), msg, args);

	logFile << timer.getTotalTime() << " - [INFO] " << buffer << std::endl;
	std::cout << timer.getTotalTime() << " - [INFO] " << buffer << std::endl;
	save();
}

void Logger::logError(const char *msg, ... )
{
	va_list args;
	va_start(args,msg);

	char buffer[256];
	vsnprintf(buffer, sizeof(buffer), msg, args);

	logFile << "[ERROR] " << buffer << std::endl;
	std::cerr << "[ERROR] " << buffer << std::endl;
	save();
}

void Logger::logCSV(struct CSVVals *data)
{
	double time = timer.getTotalTime();

	csvFile
		/*General Data*/
			<< time << ','
			<< data->voltage << ','
			<< data->totalCurrent << ','
			<< data-> motor1Position << ','
			<< data-> motor2Position << ','
			<< data-> motor3Position << ','
			<< data-> motor4Position << ','
			<< data-> motor1Velocity << ','
			<< data-> motor2Velocity << ','
			<< data-> motor3Velocity << ','
			<< data-> motor4Velocity << std::endl;
	save();
}

void Logger::save()
{
	logFile.flush();
	csvFile.flush();
}

void Logger::Run() {

}

Logger::~Logger() {
	// TODO Auto-generated destructor stub
}
