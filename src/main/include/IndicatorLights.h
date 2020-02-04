/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "RobotMap.h"

// Formerly STSLSHost
class IndicatorLights {

public:
	enum COLOR {NONE = 0, RED, GREEN, BLUE, YELLOW};

	IndicatorLights(const wpi::Twine&, const wpi::Twine&, frc::SerialPort::Port);
	~IndicatorLights();
	void setColor(COLOR);
	void setColor(int, int, int);

private:
	// Baud is the speed of data transfer in bits/second.
	static constexpr int BAUD = 9600;
	frc::SerialPort* serial;
};