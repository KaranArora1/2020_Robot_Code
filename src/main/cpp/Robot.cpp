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
// -----------------------------------------------------------------------
  Drive.resetEncoderCounts();
  Drive.setBrakeMode(ENABLED);
}

void Robot::AutonomousPeriodic() {
  Autonomous.crossBaseLine(31504, 1, 0, Drive);
  Drive.dashboardPrinter();

  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}  


void Robot::TeleopInit() {
  Drive.setBrakeMode(DISABLED);
}

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

  Index.checkLimitSwitch(); //Reset encoder counts at the beginning of each loop
  Shoot.checkLimitSwitch();
  Pickup.checkLimitSwitch();

	logTicker++;
	
  if (logTicker == logInterval) {
		logThisTime = true;
	}  
  
  // ------------------------------------------------------------------ SEQUENCING CHANNELS ---------------------------------------------------------------------------

  if (sequencingConfig == ENABLED) {

    leftJoyY = driverJoy.GetRawAxis(fwdJoyChl);
    rightJoyX = driverJoy.GetRawAxis(trnJoyChl);

    if (fabs(leftJoyY) <= 0.2 || velocityControl == DISABLED) {
      velocityControl = DISABLED;
      Drive.drivePercent(Deadzone(leftJoyY), Deadzone(rightJoyX) * 0.35); //Latch for Drivetrain - switch between PercentOutput and Velocity
    }

    else if (fabs(leftJoyY) > 0.25 || velocityControl == ENABLED) {
      velocityControl = ENABLED;
      Drive.driveVelocity(Deadzone(leftJoyY), Deadzone(rightJoyX) * 0.35);
    }

    //Drive.drivePercent(Deadzone(leftJoyY), Deadzone(rightJoyX) * 0.35); Use in case latch doesn't work
    
  // ------------------------------------------------------------------ SEQUENCING BUTTONS ----------------------------------------------------------------------------

    //Picking up balls off the ground sequence
    if (operatorJoy.GetRawButtonPressed(ballPickupmMoveArmBtnSequence)) { 
      Pickup.moveArm(); 

      if (Pickup.armState == EXTENDED) { //Stuff that initially happens when button is pressed
        Pickup.Pickup(BALLPICKUP_ARM_SPEED);
        Index.Spin(-INDEXER_SPEED_FINAL_BOT); 
      }
      else {
        Pickup.Pickup(0); //Turn off sequence
        Index.Spin(0);
        Index.divetTime = 0; 
      }
    }

    if (Pickup.armState == EXTENDED) { //Stuff that should be constantly checked for when the arm is out and the sequence is happening
      Index.Divet();

      //Allows for operator to override Pickup belts in case they get jammed
      if (Deadzone(operatorJoy.GetRawAxis(reverseBallPickupOverrideChl) > 0)) { //Might cause some issues with change of direction, test and fix
        Pickup.Pickup(-BALLPICKUP_ARM_SPEED);
      }
      else {
        Pickup.Pickup(BALLPICKUP_ARM_SPEED);
      }
   }

    //Planned speed of Shooter can be incremented or decremented regardless of if the Pickup arm is out
    if (operatorJoy.GetRawButtonPressed(shootSpeedIncBtnSequence)) {
        Shoot.incSpeed(UP);
    }

    if (operatorJoy.GetRawButtonPressed(shootSpeedDecBtnSequence)) {
      Shoot.incSpeed(DOWN);
    }

    //Shooting without Vision - only runs when Pickup Arm is not extended (so as to not interfere with Indexer direction)
    if (Pickup.armState == RETRACTED) {

      if (driverJoy.GetRawButtonPressed(wristOverrideStatusBtnSequence)) {
        Shoot.toggleWristOverride();
      }

      //If the Wrist can be overridden, check if the right trigger is being pressed past 20% and move the wrist down
      if (Shoot.wristOverride == ENABLED) {
        if (Deadzone(driverJoy.GetRawAxis(moveWristDownOverrideChlSequence)) > .2) {
          if (!(Shoot.checkLimitSwitch())) { //Only do this when the switch is not being pressed
            Shoot.moveWristDownOverride();
          }
          else {
            //When the switch is finally pressed and the wrist is home, make the override status back to disabled
            Shoot.toggleWristOverride(); 
          }
        }
      }

      //Moving the wrist, shooting, and the sequence should only run when override is disabled
      if (Shoot.wristOverride == DISABLED) { 
        if (driverJoy.GetRawButtonPressed(moveWristUpBtnSequence)) {
          Shoot.moveWristFixedPositions(UP);
        }

        //THIS SHOULD ONLY WORK WHEN THE PICKUP ARM IS NOT EXTENDED Does is though?? Fix maybe
        if (driverJoy.GetRawButtonPressed(moveWristDownBtnSequence)) {
          Shoot.moveWristFixedPositions(DOWN);
        }

        if (operatorJoy.GetRawButtonPressed(shootSpeedBtnSequence)) { 
            Shoot.ShootRPMs();
        }

        //If the shooter wheels are rotating activate the sequence
        if (Shoot.currentRPM > 900) { 
          Index.feedBall(FEEDER_WHEEL_SPEED);
          Index.setPushBall(EXTENDED);
          Index.Spin(INDEXER_SPEED_FINAL_BOT);
        }

        else {
          Index.feedBall(0);
          Index.setPushBall(RETRACTED);
          Index.Spin(0);
        }
      }
    }

    //Vision Shoot High
    if (operatorJoy.GetRawButtonPressed(activateVisionShootHighBtnSequence)) {
      //Limelight.Run(0, .15, Drive);
      //Limelight.toggleShootHighStatus();
      //Limelight.setupShootHigh(Drive, Shoot); //Add indicator lights
    }

    /*if (Limelight.shootHighStatus == ENABLED) {
      if (operatorJoy.GetRawButtonPressed(cancelVisionShootHighBtnSequence)) {
        Limelight.toggleShootHighStatus();
      }
      else if (operatorJoy.GetRawButtonPressed(activateVisionShootHighBtnSequence)) {
        Limelight.shootHigh(Shoot, Index); //Add indicator lights
        Index.Spin(-INDEXER_SPEED_FINAL_BOT); //Is this needed
      }
    }*/

    //Drivetrain shifter
    if (driverJoy.GetRawButtonPressed(shifterBtnSequence) && Climb.scissorLiftStatus == RETRACTED) {
      Drive.Shift();
    }
    
  // ----------------------------------------------------------------- SEQUENCING CLIMBING ----------------------------------------------------------------------------
    //Change Climb Status
    if (driverJoy.GetRawButtonPressed(climbStatusBtnSequence) && Climb.scissorLiftStatus == RETRACTED) {
      Climb.toggleScissorCanBeDeployedStatus();
    }

    //Climbing
    if (Climb.scissorCanBeDeployedStatus == ENABLED) {
      if (driverJoy.GetRawButtonPressed(climbScissorJoyBtnSequence)) { 
        Climb.scissorLift(Drive);
      }
    }

    //Only turn on winch if scissor lift is extended
    if (Climb.scissorLiftStatus == EXTENDED) {
      if (operatorJoy.GetRawButtonPressed(winchBtnSequence)) {
        Climb.Climb(10000); 
      }
    }
  }

  // ---------------------------------------------------------------------- END ---------------------------------------------------------------------------------------




  
  // ---------------------------------------------------------------- NON-SEQUENCING CHANNELS -------------------------------------------------------------------------
  
  else {
    //Drive
    Drive.drivePercent(Deadzone(driverJoy.GetRawAxis(fwdJoyChl)), Deadzone(driverJoy.GetRawAxis(trnJoyChl)) * 0.35);

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
    if (driverJoy.GetRawButtonPressed(shifterBtn) && Climb.scissorLiftStatus == RETRACTED) {
      Drive.Shift();
    }

    //Pneumatic on Indexer
    if (operatorJoy.GetRawButtonPressed(indexPusherBtn)) {
      Index.switchPushBall();
    }

    //Shooter (RPM Version)
    if (operatorJoy.GetRawButtonPressed(shootSpeedIncBtn)) {
      Shoot.incSpeed(1000);
    }

  // -------------------------------------------------------------- NON-SEQUENCING CLIMBING -----------------------------------------------------------------------------

    //Change Climb Status
    if (driverJoy.GetRawButtonPressed(climbStatusBtn) && Climb.scissorLiftStatus == RETRACTED) {
      Climb.toggleScissorCanBeDeployedStatus();
    }

    //Climbing
    if (Climb.scissorCanBeDeployedStatus == ENABLED) {
      if (driverJoy.GetRawButton(climbScissorJoyBtn)) { 
        Climb.scissorLift(Drive);
      }
    }

    if (Climb.scissorLiftStatus == EXTENDED) {
      Climb.Climb(Deadzone(driverJoy.GetRawAxis(climbJoyChl)));
    }
  }

  // ----------------------------------------------------------------------- END ----------------------------------------------------------------------------------------

  // TODO: Get Limelight feedback to get range of high target.
  if (Pickup.armState == EXTENDED) {
    Lights.setCommand(IndicatorLights::CMD::GREEN_DOWN);
  } 
  else if (Shoot.getRPMs()[0] > 0) {
    Lights.setCommand(IndicatorLights::CMD::GREEN_UP);
  } 
  else {
    Lights.setCommand(IndicatorLights::CMD::GREEN_SOLID);
  }

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

  //Logging - if the log is run, reset the time 
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
