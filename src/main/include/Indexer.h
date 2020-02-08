/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "RobotMap.h"

class Indexer {
 public:
  Indexer();
  void Spin(double, double);
  void pushBall();
  void feedBall(double);
  int getIndexerPosition();
  double getFeederRPM();
  void Printer();
  void dashboardPrinter();

 private:
  WPI_TalonSRX index{indexerMotorID};
  WPI_TalonSRX feeder{feederMotorID};
  frc::DoubleSolenoid pneumaticPusher{PCMID, pusherKReverse, pusherKForward};

  frc::DoubleSolenoid::Value pusherState = frc::DoubleSolenoid::Value::kOff;
};
