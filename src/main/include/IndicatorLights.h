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
	enum struct CMD {
		NONE = 0x0,
		GREEN_SOLID,
		GREEN_UP,
		GREEN_DOWN,
		RED_SOLID,
		RED_UP,
		RED_DOWN
	};

	IndicatorLights(const wpi::Twine&, const wpi::Twine&, frc::SerialPort::Port);
	~IndicatorLights();
	void setCommand(CMD);
	void setColor(int, int, int);

 private:
	enum struct CMD_INTERNAL {
		NOOP = 0x0,
		CUSTOM = 0x1,
		GREEN_SOLID = 0x2,
		GREEN_UP = 0x3,
		GREEN_DOWN = 0x4,
		RED_SOLID = 0x5,
		RED_UP = 0x6,
		RED_DOWN = 0x7
	};
	
	// Baud is the speed of data transfer in bits/second.
	static constexpr int BAUD = 9600;
	frc::SerialPort* serial;
	
	void sendCommand(CMD_INTERNAL, int, int, int);
};