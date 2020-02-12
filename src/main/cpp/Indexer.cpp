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

	feeder.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, 10);
	feeder.SetSelectedSensorPosition(0);
}

void Indexer::Spin(double triggerForward, double triggerReverse) {
	if (triggerForward > 0 && triggerReverse > 0)
    	index.Set(ControlMode::PercentOutput, 0);
	else
		index.Set(ControlMode::PercentOutput, triggerForward - triggerReverse);
}

void Indexer::pushBall() {
    if (pneumaticPusher.Get() == frc::DoubleSolenoid::Value::kForward) {
		pneumaticPusher.Set(frc::DoubleSolenoid::Value::kReverse);
	}
    else {
		pneumaticPusher.Set(frc::DoubleSolenoid::Value::kForward);
	}
}

void Indexer::feedBall(double speed) {
	feeder.Set(ControlMode::PercentOutput, speed);
}

int Indexer::getIndexerPosition() {
	return index.GetSelectedSensorPosition(0);
}

double Indexer::getFeederRPM() {
	return feeder.GetSelectedSensorVelocity(0) * velToRPM_SRX;
}

void Indexer::Printer() {
	std::cout << "Indexer Position " << getIndexerPosition() << " counts" << std::endl; //Not logged yet
	std::cout << "Feeder Velocity " << getFeederRPM() << " rpm" << std::endl; //Not logged yet
	
	std::cout << "Ball Pusher State: " << ((pneumaticPusher.Get() == frc::DoubleSolenoid::Value::kForward) ? "kForward (Up)" : "kReverse (Down)") << std::endl; //Not logged yet
}

void Indexer::dashboardPrinter() {
	frc::SmartDashboard::PutNumber("Indexer Position (counts)", getIndexerPosition());
	frc::SmartDashboard::PutNumber("Feeder Velocity (rpm)", getFeederRPM());

	frc::SmartDashboard::PutString("Ball Pusher State",
		 (pneumaticPusher.Get() == frc::DoubleSolenoid::Value::kForward) ? "kForward (Up)" : "kReverse (Down)");
}