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

double Robot::Deadzone(double input, double target) { //Maybe make Deadzone value to hit a parameter? Have two arguments different for each function 
  if (fabs(input) < target) {
    input = 0.0;
    }
  else {
    if (input > 0) {
      input = (input - target) / (1 - target);
      }
      else {
        input = (input + target) / (1 - target);
        }
      }
    return input;
   }

void Robot::TeleopPeriodic() {

  frc::SmartDashboard::PutNumber("Pressure (PSI?)", ((pressure.GetValue() - 404)/3418) * 120); //Don't know what this conversion is, PSI? //Not logged yet
  frc::SmartDashboard::PutNumber("Total Current Draw (Amps)", pdp.GetTotalCurrent());

	logTicker++;
	
  if (logTicker == logInterval) {
		logThisTime = true;
	}  
  
  // ------------------------------------------------------------------ SEQUENCING CHANNELS ---------------------------------------------------------------------------

  if (sequencingConfig) {
    Drive.Drive(Deadzone(driverJoy.GetRawAxis(fwdJoyChl), .075), Deadzone(driverJoy.GetRawAxis(trnJoyChl), .075) * 0.35);
    
  // ------------------------------------------------------------------ SEQUENCING BUTTONS ----------------------------------------------------------------------------

    /* 3- after carousel full, stop carousel
        3- turn on ball carousel CCW  (& set LED feedback)
    Carousel - clear a jam
    Shoot low (visual only)

    */

    if (operatorJoy.GetRawButtonPressed(ballPickupmMoveArmBtnSequence)) { //Changes state of arm boolean
      Pickup.moveArm(); 

      if (Pickup.getState()) { //Acts if arm is extended
        //Pickup.Pickup(.75);
        Index.Spin(.13, 0); 
      }
      else {
        Pickup.Pickup(0);
        Index.Spin(0, 0);
        Index.setDivetTime(0);
      }
    }

    if (Pickup.getState()) {
      Index.Divet();
    }

    if (operatorJoy.GetRawButtonPressed(activateVisionShootingBtnSequence)) {
      //Limelight.Shoot(Drive, Shoot, Index, Lights);
      Index.Spin(0, .13);
      Limelight.switchPipeline();
    }

    //Drivetrain (Shifter)
    if (driverJoy.GetRawButtonPressed(shifterBtn)) {
      Drive.Shift();
    }
    
  // ----------------------------------------------------------------- SEQUENCING CLIMBING ----------------------------------------------------------------------------
    //Change Climb Status
      if (driverJoy.GetRawButtonPressed(climbStatusBtn)) {
        Climb.changeScissorClimbStatus();
      }

      //Climbing
      if (Climb.getScissorClimbStatus()) {
        if (driverJoy.GetRawButton(climbScissorJoyBtn)) { 
          Climb.scissorLift();
          Climb.changeWinchClimbStatus();  //The winch can only be activated once the scissor lift has been deployed
        }
      }

      if (Climb.getWinchClimbStatus()) {
        Climb.Climb(Deadzone(driverJoy.GetRawAxis(climbJoyChl)));
      }
  }

  // ---------------------------------------------------------------------- END ---------------------------------------------------------------------------------------




  
  // ---------------------------------------------------------------- NON-SEQUENCING CHANNELS -------------------------------------------------------------------------
  
  else {
    //Drive
    Drive.Drive(Deadzone(driverJoy.GetRawAxis(fwdJoyChl)), Deadzone(driverJoy.GetRawAxis(trnJoyChl)) * 0.35);

    //Shooter
    if (fabs(Deadzone(operatorJoy.GetRawAxis(shootJoyChl))) > 0 && operatorJoy.GetRawButtonPressed(shootBtn)) {
      Shoot.Shoot(0);
    }
    else if (operatorJoy.GetRawButton(shootBtn)) {
      Shoot.ShootRPMs();
    }
    else { //If button is not pressed, go to Joystick, and Joystick will be 0 probably so the result is no movement but it will move if the Joystick is tilted
      Shoot.Shoot(Deadzone(operatorJoy.GetRawAxis(shootJoyChl)));
    }

    //Pickup
    if (driverJoy.GetRawButtonPressed(ballPickupMoveArmReverseJoyBtn)) {
      Pickup.moveArm(Deadzone(driverJoy.GetRawAxis(ballPickupMoveArmJoyChl)) * 0.3); //Make it go reverse if button is being pressed b/c of lack of channels available
    }
    else {
      Pickup.moveArm(Deadzone(driverJoy.GetRawAxis(ballPickupMoveArmJoyChl)) * -0.3);
    }

    Pickup.Pickup(Deadzone(-1*(operatorJoy.GetRawAxis(ballPickupJoyChl))));

    //Index
    Index.Spin(Deadzone(operatorJoy.GetRawAxis(indexFwdJoyChl)) * 0.13, Deadzone(operatorJoy.GetRawAxis(indexReverseJoyChl)) * 0.13); //Maybe take out Deadzone? 
    Index.feedBall(-1 * operatorJoy.GetRawAxis(indexJoyFeederChl));

    //Add deployArm from PanelSpinner? assign them to buttons

  // --------------------------------------------------------------- NON-SEQUENCING BUTTONS ----------------------------------------------------------------------------

    if (driverJoy.GetRawButtonPressed(switchVisionPipelineBtn)) {
      Limelight.switchPipeline();
    }

    Shoot.moveWrist(operatorJoy.GetRawAxis(moveWristChl));

    //Drivetrain (Shifter)
    if (driverJoy.GetRawButtonPressed(shifterBtn)) {
      Drive.Shift();
    }

    //Pneumatic on Indexer
    if (operatorJoy.GetRawButtonPressed(indexPusherBtn)) {
      Index.pushBall();
    }

    //Shooter (RPM Version)
    if (operatorJoy.GetRawButtonPressed(shootSpeedIncBtn)) {
      Shoot.incSpeed();
    }

  // -------------------------------------------------------------- NON-SEQUENCING CLIMBING -----------------------------------------------------------------------------

    //Change Climb Status
    if (driverJoy.GetRawButtonPressed(climbStatusBtn)) {
      Climb.changeScissorClimbStatus();
    }

    //Climbing
    if (Climb.getScissorClimbStatus()) {
      if (driverJoy.GetRawButton(climbScissorJoyBtn)) { 
        Climb.scissorLift();
        Climb.changeWinchClimbStatus();  //The winch can only be activated once the scissor lift has been deployed
      }
    }

    if (Climb.getWinchClimbStatus()) {
      Climb.Climb(Deadzone(driverJoy.GetRawAxis(climbJoyChl)));
    }
  }

  // ----------------------------------------------------------------------- END ----------------------------------------------------------------------------------------



  //Dashboard and Printing
  Pickup.dashboardPrinter();
  Climb.dashboardPrinter();
  Drive.dashboardPrinter();
  Index.dashboardPrinter();
  Spinner.dashboardPrinter();
  Shoot.dashboardPrinter();
  Limelight.dashboardPrinter();

  /* Pickup.Printer();
  Climb.Printer();
  Drive.Printer();
  Index.Printer();
  Spinner.Printer();
  Shoot.Printer(); */

  //Logging
  if (logThisTime) {
    logThisTime = false;
    logTicker = 0;

    Logger::instance()->Run(Drive.getPositions(), Drive.getVelocities(), Drive.getRPMs(), Drive.getCurrents(), Shoot.getRPMs(), 
                            Shoot.getWristPosition(), Spinner.getPosition(), Spinner.getVelocity(), Spinner.getRPM(), 
                            Spinner.getConfidence(), Climb.getWinchPosition());
  }
}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
