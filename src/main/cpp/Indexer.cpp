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

void Indexer::Spin(double triggerForward, double triggerReverse) { //Maybe make overloaded method for this? Only one argument is needed when operator is not controlling Indexer
	if (triggerForward > 0 && triggerReverse > 0) {
    	index.Set(ControlMode::PercentOutput, 0);
	}
	else {
		index.Set(ControlMode::PercentOutput, triggerForward - triggerReverse);
	}	
}

void Indexer::Spin(double speed) {
	index.Set(ControlMode::PercentOutput, speed);
}

void Indexer::switchPushBall() {
    if (pneumaticPusher.Get() == frc::DoubleSolenoid::Value::kForward) {
		pneumaticPusher.Set(frc::DoubleSolenoid::Value::kReverse);
	}
    else {
		pneumaticPusher.Set(frc::DoubleSolenoid::Value::kForward);
	}
}

void Indexer::setPushBall(positionStatus position) { //FIX LATER
	if (position == EXTENDED) {
		pneumaticPusher.Set(frc::DoubleSolenoid::Value::kReverse); //UP
	}
	else {
		pneumaticPusher.Set(frc::DoubleSolenoid::Value::kForward); //DOWN
	}
}

void Indexer::feedBall(double speed) {
	feeder.Set(ControlMode::PercentOutput, speed);
} 

void Indexer::Divet() {

	divetTime += 1;
	realTime = (divetTime * 20) / 1000;

	if ((realTime > 3) && (realTime < 3.5)) {
		Spin(-.10);
	}

	else if (realTime > 3.5) {
		Spin(.10);
		divetTime = 0;
	}
}

void Indexer::setDivetTime(int time) {
	divetTime = time;
}

void Indexer::checkLimitSwitch() { //Is there a better way to update encoder counts?
    if (indexSwitch.Get()) {
        index.SetSelectedSensorPosition(0);
    }
}

int Indexer::getIndexerPosition() {
	return index.GetSelectedSensorPosition(0);
}

double Indexer::getFeederRPM() {
	return feeder.GetSelectedSensorVelocity(0) * velToRPM_SRX;
}

double Indexer::getCurrent() {
	return index.GetOutputCurrent();
}

void Indexer::Printer() {
	std::cout << "Indexer Position " << getIndexerPosition() << " counts" << std::endl; //Not logged yet
	std::cout << "Feeder RPM " << getFeederRPM() << std::endl; //Not logged yet
	
	std::cout << "Ball Pusher State: " << ((pneumaticPusher.Get() == frc::DoubleSolenoid::Value::kForward) ? "kForward (Up)" : "kReverse (Down)") << std::endl; //Not logged yet

	std::cout << "Current: " << getCurrent() << " Amps" << std::endl;
}

void Indexer::dashboardPrinter() {
	frc::SmartDashboard::PutNumber("Indexer Position (counts)", getIndexerPosition());
	frc::SmartDashboard::PutNumber("Feeder RPM", getFeederRPM());
	frc::SmartDashboard::PutNumber("Indexer Current (amps)", getCurrent());

	frc::SmartDashboard::PutString("Ball Pusher State",
		 (pneumaticPusher.Get() == frc::DoubleSolenoid::Value::kForward) ? "kForward (Up)" : "kReverse (Down)");

	frc::SmartDashboard::PutNumber("Real Time", realTime);
}