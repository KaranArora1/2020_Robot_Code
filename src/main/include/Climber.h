/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "RobotMap.h"

class Climber {
 public:
  Climber();
  void Climb(double);
  void scissorLift();
  void changeScissorClimbStatus();
  void changeWinchClimbStatus();
  enableStatus getScissorClimbStatus();
  enableStatus getWinchClimbStatus();
  int getWinchPosition();
  void Printer();
  void dashboardPrinter();
 
 private:
  WPI_TalonSRX winch{winchMotorID};
  double encoderPosTarget = 1000000; //Unknown
  //Constant velocity to a fixed number of encoder countd TBD

  frc::DoubleSolenoid scissor{PCMID, 1, 6};
  
  enableStatus scissorClimbStatus = DISABLED;
  enableStatus winchClimbStatus = DISABLED;
};
