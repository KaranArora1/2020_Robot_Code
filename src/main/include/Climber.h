/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "RobotMap.h"
#include "Drivetrain.h"

class Climber {
 public:
  Climber();
  void Climb(double);
  void climbToPos();
  void scissorLift(Drivetrain&);
  void toggleScissorCanBeDeployedStatus();
  int getWinchPosition();
  void Printer();
  void dashboardPrinter();

  enableStatus scissorCanBeDeployedStatus = DISABLED;
  positionStatus scissorLiftStatus = RETRACTED;

  bool hookIsOn = false;
 
 private:
  WPI_TalonSRX winch{winchMotorID};
  double encoderPosTarget = 1000000; //Unknown

  frc::DoubleSolenoid scissor{PCMID, scissorKForward, scissorKReverse};
};
