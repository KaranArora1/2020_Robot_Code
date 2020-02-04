/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Climber.h"

Climber::Climber() {
    /* winch.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Absolute, 0, 10); //Relative or Absolute? 
    winch.SetSelectedSensorPosition(0); */
}

void Climber::Climb(double speed) { //Eventually will be a follower with no parameters to the encoder pos target
    winch.Set(ControlMode::PercentOutput, speed);
    //Printer();
    dashboardPrinter();
}

int Climber::getWinchPosition() {
    return winch.GetSelectedSensorPosition(0);
}

void Climber::Printer() {
    std::cout << "Winch Position " << getWinchPosition() << " counts" << std::endl;
}

void Climber::dashboardPrinter() {
    frc::SmartDashboard::PutNumber("Winch Position (counts)", getWinchPosition());
}

void Climber::scissorLift() { //Fix
    if (scissor.Get() == frc::DoubleSolenoid::Value::kForward) {
		scissor.Set(frc::DoubleSolenoid::Value::kReverse);
	}
    else {
		scissor.Set(frc::DoubleSolenoid::Value::kForward);
	}
}