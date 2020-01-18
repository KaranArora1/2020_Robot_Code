/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <string>
#include "rev/ColorSensorV3.h"
#include "rev/ColorMatch.h"
#include "ctre/Phoenix.h"
#include "frc/WPILib.h"
#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <iostream>
#include <frc/smartdashboard/SmartDashboard.h>

class Robot : public frc::TimedRobot {
  //rev::ColorSensorV3 m_colorSensor{i2cPort};
  //rev::ColorMatch m_colorMatcher;

  //static constexpr frc::Color kBlueTarget = frc::Color(
    
   public:
  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TestPeriodic() override;
  double Deadzone(double);

  WPI_TalonFX front_left{12};
  WPI_TalonFX front_right{9};
  WPI_TalonFX back_left{11};
  WPI_TalonFX back_right{10};

  //WPI_TalonSRX motor1{2};
  //WPI_TalonSRX motor{3};

  double turn, fwd, leftThrot, rightThrot;

  frc::Joystick joy{0};

 private:
  frc::SendableChooser<std::string> m_chooser;
  const std::string kAutoNameDefault = "Default";
  const std::string kAutoNameCustom = "My Auto";
  std::string m_autoSelected;
};
