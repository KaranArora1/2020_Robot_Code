/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Indexer.h"

Indexer::Indexer() {
	index.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Absolute, 0, 10); //Relative or Absolute? 
    index.SetSelectedSensorPosition(0); 
}

void Indexer::Spin(double speed) {
    index.Set(ControlMode::PercentOutput, speed);
	//Printer();
	dashboardPrinter();
}

void Indexer::feedBall() {
    if (feeder.Get() == frc::DoubleSolenoid::Value::kForward) {
		feeder.Set(frc::DoubleSolenoid::Value::kReverse);
		feederState = "kReverse";
	}
    else {
		feeder.Set(frc::DoubleSolenoid::Value::kForward);
		feederState = "kForward";
	}
}

int Indexer::getPosition() {
	return index.GetSelectedSensorPosition(0);
}

void Indexer::Printer() {
	std::cout << "Indexer Position " << getPosition() << " counts" << std::endl; //Not logged yet
	
	std::cout << "Ball Pusher State: " << feederState << std::endl; //Not logged yet
}

void Indexer::dashboardPrinter() {
	frc::SmartDashboard::PutNumber("Indexer Position (counts)", getPosition());

	frc::SmartDashboard::PutString("Ball Pusher State", feederState);
}