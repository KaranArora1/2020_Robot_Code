/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "RobotMap.h"
#include "Drivetrain.h"
#include "Shooter.h"
#include "Indexer.h"
#include "BallPickup.h"

class Auton {
 public:
  Auton();
  void lowGoal(double, double, double, Drivetrain&, Shooter&, Indexer&);
  void highGoal(double, double, double, Drivetrain&, Shooter&, Indexer&);
  void highGoalPickup(double, double, double, Drivetrain&, Shooter&, Indexer&, BallPickup&);
  void Printer();
  void dashboardPrinter();

  double backLeftAutonInitialPosition;
  double loopTime;

  private:
    double realTime = 0;
};

