/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

//https://www.ctr-electronics.com/downloads/api/cpp/html/index.html
//https://www.revrobotics.com/content/sw/max/sdk/REVRobotics.json

void Robot::RobotInit() {
  //m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  //m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);
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

double Robot::Deadzone(double input) { //Maybe make Deadzone value to hit a parameter? Have two arguments different for each function 
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

void Robot::TeleopPeriodic() {

  frc::SmartDashboard::PutNumber("Pressure (PSI?)", ((pressure.GetValue() - 404)/3418) * 120); //Don't know what this conversion is, PSI? //Not logged yet
  frc::SmartDashboard::PutNumber("Total Current Draw (Amps)", pdp.GetTotalCurrent());

  logThisTime = false;
	logTicker++;
	
  if(logTicker == logInterval) {
		logTicker = 0;
		logThisTime = true;
	}

  //Drive
  Drive.Drive(Deadzone(driverJoy.GetRawAxis(fwdJoyChl)), Deadzone(driverJoy.GetRawAxis(trnJoyChl)) * 0.35);

  //Shooter
  if (Deadzone(operatorJoy.GetRawAxis(shootJoyChl)) > 0 && operatorJoy.GetRawButtonPressed(shootJoyBtn)) {
    Shoot.Shoot(0);
  }
  else if (operatorJoy.GetRawButtonPressed(shootJoyBtn)) {
    Shoot.ShootRPMs();
  }
  /*else { //If button is not pressed, go to Joystick, and Joystick will be 0 probably so the result is no movement
    Shoot.Shoot(Deadzone(operatorJoy.GetRawAxis(shootJoyChl)));
  }*/

  //Pickup
  if (driverJoy.GetRawButtonPressed(ballPickupMoveArmReverseJoyBtn)) {
    Pickup.moveArm(Deadzone(driverJoy.GetRawAxis(ballPickupMoveArmJoyChl)) * -0.3); //Make it go reverse if button is being pressed b/c of lack of channels available
  }
  else {
    Pickup.moveArm(Deadzone(driverJoy.GetRawAxis(ballPickupMoveArmJoyChl)) * 0.3);
  }

  Pickup.Pickup(Deadzone(-1*(operatorJoy.GetRawAxis(ballPickupJoyChl))));

  //Index
  Index.Spin(Deadzone(operatorJoy.GetRawAxis(indexFwdJoyChl)) * 0.175, Deadzone(operatorJoy.GetRawAxis(indexReverseJoyChl)) * 0.175); //Maybe take out Deadzone? 
  Index.feedBall(-1 * operatorJoy.GetRawAxis(indexJoyFeederChl));

  //Add deployArm? assign them to buttons

  //Shooter (RPM Version)
  if (operatorJoy.GetRawButtonPressed(shootSpeedIncBtn)) {
    Shoot.incSpeed();
  }

  /*if (operatorJoy.GetRawAxis(climbJoyChl)) { //FIX //FIX INDEXER SPEED
    Shoot.moveWrist();
  }*/

  /*if (driverJoy.GetRawButtonPressed(7)) {
    //Limelight.switchPipeline();
    //nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber
  }*/

  Shoot.moveWrist(operatorJoy.GetRawAxis(climbJoyChl));

  //Drivetrain (Shifter)
  if (driverJoy.GetRawButtonPressed(shifterBtn)) {
    Drive.Shift();
  }

  //Pneumatic on Indexer
  if (operatorJoy.GetRawButtonPressed(indexPusherBtn)) {
    Index.pushBall();
  }

  //Change Climb Status
  if (driverJoy.GetRawButtonPressed(climbStatusBtn)) {
    Climb.changeScissorClimbStatus();
  }

  if (driverJoy.GetRawButton(climbScissorJoyBtn)) {
    Climb.scissorLift();
  }

  //Climb
  /*if (Climb.getScissorClimbStatus()) { //The winch can only be activated once the scissor lift has been deployed
    if (driverJoy.GetRawButton(climbScissorJoyBtn)) { //The scissor lift can only be deployed when an operator button is pressed
      Climb.scissorLift();
      Climb.changeWinchClimbStatus();
    }
  }*/

  /*if (Climb.getWinchClimbStatus()) {
    Climb.Climb(Deadzone(driverJoy.GetRawAxis(climbJoyChl)));
  }*/

  //Logging
  if (logThisTime) {
    Logger::instance()->Run(Drive.getPositions(), Drive.getVelocities(), Drive.getRPMs(), Drive.getCurrents(), Shoot.getRPMs(), 
                            Shoot.getWristPosition(), Spinner.getPosition(), Spinner.getVelocity(), Spinner.getRPM(), 
                            Spinner.getConfidence(), Climb.getWinchPosition());
  }
}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
