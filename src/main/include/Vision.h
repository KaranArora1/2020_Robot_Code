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
  void Run(double, double, Drivetrain&);
  void setupShootHigh(Drivetrain&, Shooter&);
  void shootHigh(Shooter&, Indexer&);
  void shootLow(Drivetrain&, Shooter&, Indexer&);
  double calculateDistance();
  void switchPipeline();
  void toggleShootHighStatus();
  void Printer();
  void dashboardPrinter();

  enableStatus shootHighStatus = DISABLED;
 
 private:

  //std::shared_ptr<NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");

  float tv, tx, ty;
  float shooterAngle, distance;
};
