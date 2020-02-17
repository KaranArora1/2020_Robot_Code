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
//#include "IndicatorLights.h"

class Vision {
 public:
  Vision();
  void Run(double, double);
  void Shoot(Drivetrain, Shooter, Indexer);
  double calculateDistance();
  void switchPipeline();
  void Printer();
  void dashboardPrinter();
 
 private:
  float tv, tx, ty;
  float shooterAngle, distance;
};
