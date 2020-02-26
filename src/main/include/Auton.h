/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "RobotMap.h"
#include "Drivetrain.h"

class Auton {
 public:
  Auton();
  void resetEncoderCounts(Drivetrain&);
  void crossBaseLine(double, double, double, Drivetrain&);

  private:
    double backLeftAutonInitialPosition;
};

