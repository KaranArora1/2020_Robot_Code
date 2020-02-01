/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Climber.h"

Climber::Climber() {
    
}

void Climber::Climb(double speed) {
    winch.Set(ControlMode::PercentOutput, speed);
}

void Climber::Printer() {

}

void Climber::DashboardPrinter() {}