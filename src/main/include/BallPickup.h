/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "RobotMap.h"
#include "Indexer.h"

class BallPickup {
 public:
  BallPickup();
  void Pickup(double);
  void moveArm();
  void moveArm(double);
  void checkLimitSwitch();
  int getPickupArmPosition();
  void Printer();
  void dashboardPrinter();

  positionStatus armState = RETRACTED;
 
 private:
  WPI_TalonSRX pickup{pickupMotorID};
  WPI_TalonSRX arm{armMotorID};

  frc::DigitalInput armSwitch{armSwitchID}; //9
};
