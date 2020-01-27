/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "RobotMap.h"

class PanelSpinner {
 public:
  PanelSpinner();
  std::string DetectColor();
  void SpinRevolutions(double);
  void SpinToColor(double);

 private:
  rev::ColorSensorV3 m_colorSensor{i2cPort}; // The color sensor is on the 12cPort
  rev::ColorMatch colorSensor; 

  frc::Color detectedColor;
  frc::Color matchedColor;
  
  std::string colorString;

  double confidence;

  WPI_TalonSRX spinner{spinnerID};
};
