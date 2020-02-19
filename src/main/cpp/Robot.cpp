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
  if (fabs(input) < .05) {
    input = 0.0;
    }
  else {
    if (input > 0) {
      input = (input - .05) / (1 - .05);
      }
      else {
        input = (input + .05) / (1 - .05);
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

  if (sequencingConfig == ENABLED) {

    leftJoyY = driverJoy.GetRawAxis(fwdJoyChl);
    rightJoyX = driverJoy.GetRawAxis(trnJoyChl);

    Drive.Drive(Deadzone(leftJoyY), Deadzone(rightJoyX) * 0.35);
    
  // ------------------------------------------------------------------ SEQUENCING BUTTONS ----------------------------------------------------------------------------

    /* 3- after carousel full, stop carousel
        3- turn on ball carousel CCW  (& set LED feedback)
    Carousel - clear a jam
    Shoot low (visual only)

    */

    //Picking up balls off the ground
    if (operatorJoy.GetRawButtonPressed(ballPickupmMoveArmBtnSequence)) { 
      Pickup.moveArm(); 

      if (Pickup.getState() == EXTENDED) { 
        Pickup.Pickup(.75);
        Index.Spin(.13, 0); 
      }
      else {
        Pickup.Pickup(0);
        Index.Spin(0, 0);
        Index.setDivetTime(0); //Is this line needed really?
      }
    }

    if (Pickup.getState() == EXTENDED) {
      Index.Divet();
    }

    //Shooting without Vision
    if (driverJoy.GetRawButtonPressed(moveWristUpBtnSequence)) {
      Shoot.moveWristFixedPositions(true);
    }

    if (driverJoy.GetRawButtonPressed(moveWristDownBtnSequence)) {
      Shoot.moveWristFixedPositions(false);
    }

    if (operatorJoy.GetRawButtonPressed(shootSpeedIncBtnSequence)) {
      Shoot.incSpeed();
    }

    if (operatorJoy.GetRawButton(shootSpeedBtnSequence)) { //Button has to STAY pressed to shoot
      Shoot.ShootRPMs();
    }

    //Vision Shoot High
    if (operatorJoy.GetRawButtonPressed(activateVisionShootHighBtnSequence)) {
      Limelight.toggleShootHighStatus();
      Limelight.setupShootHigh(Drive, Shoot); //Add indicator lights
    }

    if (Limelight.getShootHighStatus() == ENABLED) {
      if (operatorJoy.GetRawButtonPressed(cancelVisionShootHighBtnSequence)) {
        Limelight.toggleShootHighStatus();
      }
      else if (operatorJoy.GetRawButtonPressed(activateVisionShootHighBtnSequence)) {
        Limelight.shootHigh(Shoot, Index); //Add indicator lights
        Index.Spin(0, .13); //Is this needed
      }
    }

    //Drivetrain (Shifter)
    if (driverJoy.GetRawButtonPressed(shifterBtnSequence) && Climb.getScissorLiftStatus() == RETRACTED) {
      Drive.Shift();
    }
    
  // ----------------------------------------------------------------- SEQUENCING CLIMBING ----------------------------------------------------------------------------
    //Change Climb Status
    if (driverJoy.GetRawButtonPressed(climbStatusBtnSequence) && Climb.getScissorLiftStatus() == RETRACTED) {
      Climb.toggleScissorCanBeDeployedStatus();
    }

    //Climbing
    if (Climb.getScissorCanBeDeployedStatus() == ENABLED) {
      if (driverJoy.GetRawButton(climbScissorJoyBtnSequence)) { 
        Climb.scissorLift(Drive);
      }
    }

    if (Climb.getScissorLiftStatus() == EXTENDED) {
      if (operatorJoy.GetRawButtonPressed(winchBtnSequence)) {
        Climb.Climb(10000); //Change to position
      }
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

    Shoot.moveWrist(operatorJoy.GetRawAxis(moveWristChl));

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

    //Drivetrain (Shifter)
    if (driverJoy.GetRawButtonPressed(shifterBtn) && Climb.getScissorLiftStatus() == RETRACTED) {
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
    if (driverJoy.GetRawButtonPressed(climbStatusBtn) && Climb.getScissorLiftStatus() == RETRACTED) {
      Climb.toggleScissorCanBeDeployedStatus();
    }

    //Climbing
    if (Climb.getScissorCanBeDeployedStatus() == ENABLED) {
      if (driverJoy.GetRawButton(climbScissorJoyBtn)) { 
        Climb.scissorLift(Drive);
      }
    }

    if (Climb.getScissorLiftStatus() == EXTENDED) {
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
  Shoot.Printer(); 
  Limelight.Printer();*/

  //Logging
  if (logThisTime) {
    logThisTime = false;
    logTicker = 0;

    Logger::instance()->Run(Drive.getPositions(), Drive.getVelocities(), Drive.getRPMs(), Drive.getCurrents(), Shoot.getRPMs(), 
                            Shoot.getWristPosition(), Spinner.getPosition(), Spinner.getVelocity(), Spinner.getRPM(), 
                            Spinner.getConfidence(), Climb.getWinchPosition(), leftJoyY, rightJoyX, pdp.GetTotalCurrent(), pdp.GetVoltage());
    }
}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
