/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Indexer.h"

Indexer::Indexer() {}

void Indexer::Spin(double speed) {
    index.Set(ControlMode::PercentOutput, speed);
}

void Indexer::PushBall() {
    if (pusher.Get() == frc::DoubleSolenoid::Value::kForward) {
		pusher.Set(frc::DoubleSolenoid::Value::kReverse);
	}
    else {
		pusher.Set(frc::DoubleSolenoid::Value::kForward);
	}
}

void Indexer::Printer() {

}

void Indexer::DashboardPrinter() {

}