/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "RobotMap.h"
#include <frc/DriverStation.h>

class PanelSpinner {
 public:
  PanelSpinner();
  void deployArm();
  std::string detectColor();
  void spinRevolutions(double);
  void spinToColor(double);
  int getPosition();
  int getVelocity();
  double getConfidence();
  double getRPM();
  void Printer();
  void dashboardPrinter();

 private:
  double confidence;

  rev::ColorSensorV3 m_colorSensor{i2cPort}; // The color sensor is on the 12cPort
  rev::ColorMatch colorSensor; 

  frc::Color detectedColor;
  frc::Color matchedColor;
  
  std::string colorString;
  std::string gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();

  std::string targetColor;

  bool spinStatus = false;
  WPI_TalonSRX spinner{spinnerMotorID};
};
