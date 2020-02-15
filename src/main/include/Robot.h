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
#include "BallPickup.h"
#include "Indexer.h"
#include "IndicatorLights.h"
#include "Logger.h"
#include "PanelSpinner.h"
#include "Shooter.h"
#include "Vision.h"

class Robot : public frc::TimedRobot {
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
    frc::Joystick driverJoy{driverJoyUSBPort};
    frc::Joystick operatorJoy{operatorJoyUSBPort};

    frc::PowerDistributionPanel pdp{pdpID};
    frc::AnalogInput pressure{pressureID};

    Drivetrain Drive{};
    Shooter Shoot{};
    Climber Climb{};
    BallPickup Pickup{};
    PanelSpinner Spinner{};
    Indexer Index{};
    IndicatorLights Lights{"ttyUSB0", "ttyUSB1", frc::SerialPort::Port::kUSB};
    Vision Limelight{};

    bool sequencingConfig = false;
    bool logThisTime = false;
    int logTicker = 0;
    int logInterval = 20;

    frc::SendableChooser<std::string> m_chooser;
    const std::string kAutoNameDefault = "Default";
    const std::string kAutoNameCustom = "My Auto";
    std::string m_autoSelected;
};
