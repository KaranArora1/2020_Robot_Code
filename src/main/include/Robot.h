/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "RobotMap.h"

#include "Climber.h"
#include "Drivetrain.h"
#include "Intake.h"
#include "Lights.h"
#include "Logger.h"
#include "PanelSpinner.h"
#include "Shooter.h"
#include "Vision.h"

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

  private:

    //WPI_TalonSRX motor1{2};
    //WPI_TalonSRX motor{3};

    frc::Joystick joy{0};

    Drivetrain Drive{};

    frc::SendableChooser<std::string> m_chooser;
    const std::string kAutoNameDefault = "Default";
    const std::string kAutoNameCustom = "My Auto";
    std::string m_autoSelected;
};
