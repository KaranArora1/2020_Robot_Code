#pragma once

#include <iostream>
#include <string>
#include <stdarg.h> //Logger & Timer
#include <fstream> //Logger & Timer
#include <time.h> //Logger & Timer
#include <sys/time.h> //Logger & Timer

//#include "frc/WPILib.h"
#include "frc/Joystick.h"
#include "frc/DoubleSolenoid.h"
#include "frc/SerialPort.h" //Lights
//#include "frc/PowerDistributionPanel.h"
#include "frc/AnalogInput.h" //Pressure
#include "frc/DigitalInput.h" //Limit Switches
#include "frc/TimedRobot.h" 
#include "frc/DriverStation.h" //Panel Spinner
#include "frc/smartdashboard/SendableChooser.h"
#include "frc/smartdashboard/SmartDashboard.h"
#include "networktables/NetworkTable.h" //Vision
#include "networktables/NetworkTableInstance.h" //Vision
#include "Math.h"
#include "cameraserver/CameraServer.h"
#include "rev/ColorSensorV3.h" //Color Sensor
#include "rev/ColorMatch.h" //Color Sensor
#include "rev/CIEColor.h" //Color Sensor
#include "ctre/Phoenix.h"
#include "rev/CANSparkMax.h" //Sparks

/* CONTROLS (Non-Sequencing)
   Driver: 
   Drive Forward - Left Joystick Y Axis
   Turn - Right Joystick X Axis
   Shift Gears - A Button
   Winch Climb - Right Trigger
   Toggle Scissor Climb Status - Menu Button
   Scissor Climb - X Button
   Ball Pickup Move Arm - Left Trigger 
   Ball Pickup Move Arm Reverse Button - Y Button
   Wrist - Right Trigger 
   Switch Pipeline - View Button

   Operator: 
   Shoot - Left Joystick Y Axis - TEMPORARILY INCORRECT
   Shoot - A Button
   Increment Shooter RPM's - Right Bumper
   Move Shooter Up One Position - Right Bumper (Temporary)
   Move Shooter Down One Position - Left Bumper (Temporary)
   Ball Pickup - Right Joystick Y Axis
   Index Forward - Right Trigger
   Index Reverse - Left Trigger
   Index Feeder Wheel - Left Joystick Y Axis
   Indexer Push Ball (Pneumatic) - B Button
*/

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------

/* CONTROLS (Sequencing)
   Driver:
   Drive Forward - Left Joystick Y Axis
   Turn - Right Joystick X Axis
   Shift Gears - A Button
   Switch Pipeline - X Button
   Move Wrist Down - Left Bumper
   Move Wrist Up - Right Bumper
   Toggle Wrist Override - View Button 
   Move Wrist Down in Override - Right Trigger
   Toggle Scissor Lift Can Be Deployed - Menu Button
   Activate Scissor Lift - B Button
   Activate Winch - Left Trigger

   FREE BUTTONS: Y BUTTON

   Operator:
   Reverse Ball Pickup Belts - Left Joystick Y Axis
   Extend Pickup Arm, Move Pickup Belts, Rotate Indexer Sequence - Y Button
   Override Dither - Right Joystick X Axis
   Shoot Ball - A Button
   Decrement Shooter RPMs - Left Bumper
   Increment Shooter RPMs - Right Bumper
   Vision High Shoot - X Button 
   Cancel Vision High Shoot - Menu Button

   FREE BUTTONS: B Button, Right Trigger, Left Trigger, View Button. X and Menu if we remove vision
*/

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------

/* There are 7 Mechanisms total (BallPickup, Climber, Drivetrain, Indexer, PanelSpinner, Indicator Lights, and Shooter). 
   There are 4 Helper Programs (Logger, MyTimer, Vision, and YourTimer). 
   We are logging data from Climber(1 field), Drivetrain(4 fields x 4 motors), PanelSpinner(1 x 3), and Shooter(3 x 3)*/

//Next year just assign all the buttons on the controller to variables - "AButton = 4"

//Misc
constexpr double velToRPM_SRX = (1000 * 60) / 4096; /* Conversion factor from counts/100ms to RPM = 14.6484375
                                                       X counts/100ms * 1000ms/1s * 60s/1min * 1rev/4096 counts */

constexpr double velToRPM_FX = (1000 * 60) / 2048; /* Conversion factor from counts/100ms to RPM = 29.296875
                                                      X counts/100ms * 1000ms/1s * 60s/1min * 1rev/2048 counts */

constexpr double maxFalconVelocity = ((5000 * 2048) / 60) / 10; /* Maximum speed of Falcons under no load (counts/100ms) = 17066
                                                                   5000rev/min * 2048counts/rev * 1min/60sec * 1000ms/1s * 100 */

constexpr int pdpID = 0;
constexpr int pressureTransducerID = 0; //FIX
constexpr int PCMID = 0; 

enum enableStatus {ENABLED, DISABLED};
enum positionStatus {RETRACTED, EXTENDED};
enum direction {UP, DOWN};

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------

//Joystick General
constexpr int driverJoyUSBPort = 0; //Can be changed in Driver Station
constexpr int operatorJoyUSBPort = 1;

constexpr int fwdJoyChl = 1; //Y Axis on Left Joystick (Driver)
constexpr int trnJoyChl = 4; //X Axis on Right Joystick (Driver)

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------

//Joystick - Non Sequencing
constexpr int shifterBtn = 1; //A Button (Driver)

constexpr int shootBtn = 1; //A Button (Operator, Temporary)
constexpr int shootSpeedIncBtn = 6; //Right Bumper (Operator, Temporary)
constexpr int shootJoyChl = 1;  //Y Axis on Left Joystick (Operator)
//constexpr int shootChangeLevelUpBtn = 6; //Right Bumper (Operator)
constexpr int shootChangeLevelDownBtn = 5; //Left Bumper (Operator)
constexpr int moveWristChl = 3; //Right Trigger (Driver)

constexpr int climbStatusBtn = 8; //Menu Button (Operator)
constexpr int climbJoyChl = 3; //Right Trigger (Driver)
constexpr int climbScissorJoyBtn = 3; //X Button (Driver)

constexpr int ballPickupJoyChl = 5; //Y Axis on Right Joystick (Operator)
constexpr int ballPickupMoveArmJoyChl = 2; //Left Trigger (Driver)
constexpr int ballPickupMoveArmReverseJoyBtn = 3; //Y Button (Driver)

constexpr int indexFwdJoyChl = 3; //Right Trigger (Operator) 
constexpr int indexJoyFeederChl = 1; //Y Axis on Left Joystick (Operator)
constexpr int indexReverseJoyChl = 2; //Left Trigger (Operator) 
constexpr int indexPusherBtn = 2; //B Button (Operator)

constexpr int switchVisionPipelineBtn = 7; //View Button (Driver)

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------

//Joystick - Sequencing
constexpr int ballPickupmMoveArmBtnSequence = 4; //Y button (Operator)
constexpr int reverseBallPickupOverrideChl = 1; //Y Axis on Left Joystick (Operator)

constexpr int shifterBtnSequence = 1; //A Button (Driver)

constexpr int climbStatusBtnSequence = 8; //Menu Button (Driver)
constexpr int climbScissorJoyBtnSequence = 2; //B Button (Driver)
constexpr int winchChlSequence = 2; //Left Trigger (Driver)

constexpr int overrideShooterDirectionBtnSequence = 3; //X Button (Operator)
constexpr int cancelVisionShootHighBtnSequence = 8; //Menu Button (Operator)
constexpr int switchPipelineBtnSequence = 3; //X Button (Driver)

constexpr int ditherOverrideChlSequence = 4; //X Axis on Right Joystick (Operator)

constexpr int moveWristDownBtnSequence = 5; //Left Bumper (Driver)
constexpr int moveWristUpBtnSequence = 6; //Right Bumper (Driver)
constexpr int wristOverrideStatusBtnSequence = 7; //View Button (Driver)
constexpr int moveWristDownOverrideChlSequence = 3; //Right Trigger (Driver)
constexpr int shootSpeedIncBtnSequence = 6; //Right Bumper (Operator)
constexpr int shootSpeedDecBtnSequence = 5; //Left Bumper (Operator)
constexpr int shootSpeedBtnSequence = 1; //A Button (Operator)

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------

//Drivetrain
constexpr int frontLeftMotorID = 12; //FX
constexpr int frontRightMotorID = 9; //FX
constexpr int backLeftMotorID = 11; //FX
constexpr int backRightMotorID = 10; //FX

constexpr double drive_P = 0.025;
constexpr double drive_I = 0.005;
constexpr double drive_D = 0; 
constexpr double drive_F = 0.05;

constexpr double auton_P = 0;
constexpr double auton_I = 0;
constexpr double auton_D = 0;
constexpr double auton_F = 0;

constexpr int drive_allowableClosedLoopError = 500;
constexpr int drive_maxIntegralAccum = 10000;

constexpr int shiferFirstGear = 3; 
constexpr int shifterSecondGear = 4; 

//Climber
constexpr int winchMotorID = 4; //SRX

constexpr double winch_P = 0.75;
constexpr double winch_I = 0;
constexpr double winch_D = 0;

constexpr int winchPos = 30000; 

constexpr int scissorKForward = 1;
constexpr int scissorKReverse= 6;

//Ball Pickup
constexpr int pickupMotorID = 0; //SRX
constexpr int armMotorID = 8; //SRX Changed from  3

constexpr double pickup_P = 1; 
constexpr double pickup_I = 0;
constexpr double pickup_D = 0; 
constexpr double pickup_F = 0;

constexpr int posRetract = 0;
constexpr int posOut = 450;

constexpr double BALLPICKUP_ARM_SPEED = 1;

//PanelSpinner
constexpr int spinnerMotorID = 100; //SRX? Fix

static constexpr auto i2cPort = frc::I2C::Port::kOnboard;

static constexpr frc::Color kBlueTarget = frc::Color(0.121, 0.430, 0.447);
static constexpr frc::Color kGreenTarget = frc::Color(0.165, 0.587, 0.249);
static constexpr frc::Color kRedTarget = frc::Color(0.520, 0.356, 0.125);
static constexpr frc::Color kYellowTarget = frc::Color(0.320, 0.563, 0.114);

//Shooter
constexpr int shooterMotorID = 21; //Spark
constexpr int slaveShoooterMotorID = 20; //Spark
constexpr int wristMotorID = 3; //SRX Changed from 8

//constexpr double shooter_P = 0.00006;
constexpr double shooter_P = 0.00007;
constexpr double shooter_I = 0.000001;
constexpr double shooter_D = 0;
constexpr double shooter_IZone = 0;
constexpr double shooter_F = 0.000015;

constexpr int wristSwitchID = 0;

constexpr int SHOOTER_MAX_RPM = 5600;

constexpr double wrist_P = 1;
constexpr double wrist_I = 0.2;
constexpr double wrist_D = 0;
constexpr double wrist_maxIntegralAccum = 10;

//Indexer 
constexpr int indexerMotorID = 7; //SRX 
constexpr int feederMotorID = 1; //SRX

constexpr int pusherKReverse = 0;
constexpr int pusherKForward = 7;

constexpr int indexSwitchID = 1000;

constexpr double INDEXER_SPEED_DEMO_BOT = 0.175;
constexpr double INDEXER_SPEED_FINAL_BOT = 0.20;
constexpr double INDEXER_MANUAL_DITHER_SPEED = 0.225;

constexpr double FEEDER_WHEEL_SPEED = 1;

//Auton
constexpr int autonOption = 2;
constexpr int autonTime = 3;

//Vision 
constexpr int driverPipeline = 1;
constexpr int visionPipeline = 0;

constexpr int LED_OFF = 1;
constexpr int LED_ON = 3;