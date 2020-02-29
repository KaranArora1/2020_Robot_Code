/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "IndicatorLights.h"

IndicatorLights::IndicatorLights(const wpi::Twine& device, const wpi::Twine& deviceAlternate, frc::SerialPort::Port port = frc::SerialPort::Port::kUSB) {
	//Try to connect to first device ID.
	try {
		//Create SerialPort instance with specified settings.
		//We will use this to interface with the USB connection to the arduino.
		serial = new frc::SerialPort(BAUD, device, port);
	} catch(...) {
		//Failed, try the second device ID
		try {
			serial = new frc::SerialPort(BAUD, deviceAlternate, port);
		} catch (...) {
			//Oh well.
			return;
		}
	}
	
	//We set the buffer size to 3, for each of the 3 color channel bytes.
	//We set the buffer to auto flush when it is full.
	serial->SetWriteBufferSize(3);
	serial->SetWriteBufferMode(frc::SerialPort::WriteBufferMode::kFlushOnAccess);
}

//Destructor, likely never called.
IndicatorLights::~IndicatorLights() {
	//As serial is a pointer it is good practice to release the memory.
	//In practice this will usually have no effect.
	delete serial;
}

//Sets the arduino to execute a predefined command.
//If resend if false, it will only send data if the arduino is not currently executing the same command.
void IndicatorLights::setCommand(CMD command, bool resend) {
	switch (command) {
	case CMD::NONE:
		sendCommand(CMD_INTERNAL::NOOP, 0, 0, 0, resend);
		break;
	case CMD::GREEN_SOLID:
		sendCommand(CMD_INTERNAL::GREEN_SOLID, 0, 0, 0, resend);
		break;
	case CMD::GREEN_UP:
		sendCommand(CMD_INTERNAL::GREEN_UP, 0, 0, 0, resend);
		break;
	case CMD::GREEN_DOWN:
		sendCommand(CMD_INTERNAL::GREEN_DOWN, 0, 0, 0, resend);
		break;
	case CMD::RED_SOLID:
		sendCommand(CMD_INTERNAL::RED_SOLID, 0, 0, 0, resend);
		break;
	case CMD::RED_UP:
		sendCommand(CMD_INTERNAL::RED_UP, 0, 0, 0, resend);
		break;
	case CMD::RED_DOWN:
		sendCommand(CMD_INTERNAL::RED_DOWN, 0, 0, 0, resend);
		break;
	default:
		//Invalid command?
		break;
	}
}

//Sets the LEDs to a custom RGB color.
//Only the lower 8 bits are used.
//Basically only use numbers 0-255.
//If resend if false, it will only send data if the arduino is not currently set to the same color.
void IndicatorLights::setColor(int r, int g, int b, bool resend) {
	sendCommand(CMD_INTERNAL::CUSTOM, r, g, b, resend);
}

//Send command to the arduino for processing.
void IndicatorLights::sendCommand(CMD_INTERNAL command, int r, int g, int b, bool resend) {
	//Check if executing command is same as sending command.
	//If so, and resend is false, don't send new command.
	if (resend || (current != command) || (operands[0] != r) || (operands[1] != g) || (operands[2] != b)) {
		//Create array to house the opcode and each operand.
		//We cast to char as SerialPort::Write() takes a char pointer.
		const char buffer[4] = { (char) ((int) command), (char) r, (char) g, (char) b };
		//Send the bytes to the function.
		serial->Write(buffer, 4);
		//Flush to ensure nothing lingered. This should do nothing but I like to be sure.
		serial->Flush();
		
		//Update current command and operands
		current = command;
		operands[0] = r;
		operands[1] = g;
		operands[2] = b;
	}
}