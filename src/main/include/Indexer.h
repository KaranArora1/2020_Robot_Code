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
  void Divet();
  void setDivetTime(int);
  int getIndexerPosition();
  double getFeederRPM();
  double getCurrent();
  void Printer();
  void dashboardPrinter();

 private:
  WPI_TalonSRX index{indexerMotorID};
  WPI_TalonSRX feeder{feederMotorID};

  frc::DoubleSolenoid pneumaticPusher{PCMID, pusherKForward, pusherKReverse};

  double divetTime = 0;
  double realTime = 0;

  int posList[3] = {1000, 1000, 1000}; //will eventually be populated with the encoder values needed to rotate indexer to proper positions
};
