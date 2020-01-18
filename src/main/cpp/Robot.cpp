/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

void Robot::RobotInit() {
  //m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  //m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

  //Use Phoenix Tuner to test encoders, maybe use IntegratedSensor or Encoder Class
  back_left.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, 10);
  back_right.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, 10);
  front_left.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, 10);
  front_right.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, 10);
  
  front_right.SetSelectedSensorPosition(0);
  back_right.SetSelectedSensorPosition(0);
  front_left.SetSelectedSensorPosition(0);
  back_left.SetSelectedSensorPosition(0);
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {}

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString line to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional comparisons to the
 * if-else structure below with additional strings. If using the SendableChooser
 * make sure to add them to the chooser code above as well.
 */
void Robot::AutonomousInit() {
  m_autoSelected = m_chooser.GetSelected();
  // m_autoSelected = SmartDashboard::GetString("Auto Selector",
  //     kAutoNameDefault);
  std::cout << "Auto selected: " << m_autoSelected << std::endl;

  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}

void Robot::AutonomousPeriodic() {
  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}

void Robot::TeleopInit() {}

double Robot::Deadzone(double input) {
  if (fabs(input) < .15) {
    input = 0.0;
    }
  else {
    if (input > 0) {
      input = (input - .15) / (1 - .15);
      }
      else {
        input = (input + .15) / (1 - .15);
        }
      }
    return input;
   }

//11 12
void Robot::TeleopPeriodic() {

  fwd = Deadzone(joy.GetRawAxis(1));
  turn = Deadzone(joy.GetRawAxis(4));

  leftThrot = turn - fwd;
  rightThrot = turn + fwd;

  //motor1.Set(ControlMode::PercentOutput, Deadzone(joy.GetRawAxis(1)));
  //motor2.Set(ControlMode::PercentOutput, Deadzone(joy.GetRawAxis(1)));

  back_left.Set(ControlMode::PercentOutput, leftThrot);
  front_left.Set(ControlMode::PercentOutput, leftThrot);
  back_right.Set(ControlMode::PercentOutput, rightThrot);
  front_right.Set(ControlMode::PercentOutput, rightThrot);

  std::cout << "Back left:";
  std::cout << back_left.GetSelectedSensorPosition(0) << std::endl;

  std::cout << "Front left:";
  std::cout << front_left.GetSelectedSensorPosition(0) << std::endl;

  std::cout << "Back right:";
  std::cout << back_right.GetSelectedSensorPosition(0) << std::endl;

  std::cout << "Front right:";
  std::cout << front_right.GetSelectedSensorPosition(0) << std::endl;
}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
