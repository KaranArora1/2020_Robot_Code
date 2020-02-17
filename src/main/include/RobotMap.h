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
#include "frc/PowerDistributionPanel.h"
#include "frc/AnalogInput.h" //Pressure
#include "frc/TimedRobot.h" 
#include "frc/smartdashboard/SendableChooser.h"
#include "frc/smartdashboard/SmartDashboard.h"
#include "networktables/NetworkTable.h" //Vision
#include "networktables/NetworkTableInstance.h" //Vision
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

   Operator:
   Extend Pickup Arm, Move Pickup Belts, Rotate Indexer - Y Button
   X Button is Vision Shoot

*/

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------

/* There are 7 Mechanisms total (BallPickup, Climber, Drivetrain, Indexer, PanelSpinner, Indicator Lights, and Shooter). 
   There are 4 Helper Programs (Logger, MyTimer, Vision, and YourTimer). 
   We are logging data from Climber(1 field), Drivetrain(4 fields x 4 motors), PanelSpinner(1 x 3), and Shooter(3 x 3)*/

//Misc
constexpr double velToRPM_SRX = (1000 * 60) / 4096; /* Conversion factor from counts/100ms to RPM = 14.6484375
                                                       X counts/100ms * 1000ms/1s * 60s/1min * 1rev/4096 counts */

constexpr double velToRPM_FX = (1000 * 60) / 2048; /* Conversion factor from counts/100ms to RPM = 29.296875
                                                      X counts/100ms * 1000ms/1s * 60s/1min * 1rev/2048 counts */

constexpr int pdpID = 0;
constexpr int pressureTransducerID = 0; //FIX
constexpr int PCMID = 0; 

enum enableStatus {ENABLED, DISABLED};
enum positionStatus {RETRACTED, EXTENDED};

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------

//Joystick - Non Sequencing
constexpr int driverJoyUSBPort = 0; //Can be changed in Driver Station
constexpr int operatorJoyUSBPort = 1;

constexpr int fwdJoyChl = 1; //Y Axis on Left Joystick (Driver)
constexpr int trnJoyChl = 4; //X Axis on Right Joystick (Driver)
constexpr int shifterBtn = 1; //A Button (Driver)

constexpr int shootBtn = 1; //A Button (Operator, Temporary)
constexpr int shootSpeedIncBtn = 6; //Right Bumper (Operator, Temporary)
constexpr int shootJoyChl = 1;  //Y Axis on Left Joystick (Operator)
//constexpr int shootChangeLevelUpBtn = 6; //Right Bumper (Operator)
constexpr int shootChangeLevelDownBtn = 5; //Left Bumper (Operator)
constexpr int moveWristChl = 3; //Right Trigger (Driver)

constexpr int climbStatusBtn = 8; //Menu button (Operator)
constexpr int climbJoyChl = 3; //Right Trigger (Driver)
constexpr int climbScissorJoyBtn = 3; //X Button (Driver)

constexpr int ballPickupJoyChl = 5; //Y Axis on Right Joystick (Operator)
constexpr int ballPickupMoveArmJoyChl = 2; //Left Trigger (Driver)
constexpr int ballPickupMoveArmReverseJoyBtn = 3; //Y Button (Driver)

constexpr int indexFwdJoyChl = 3; //Right Trigger (Operator) 
constexpr int indexJoyFeederChl = 1; //Y Axis on Left Joystick (Operator)
constexpr int indexReverseJoyChl = 2; //Left Trigger (Operator) 
constexpr int indexPusherBtn = 2; //B (Operator)

constexpr int switchVisionPipelineBtn = 7; //View Button (Driver)

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------

//Joystick - Sequencing
constexpr int ballPickupmMoveArmBtnSequence = 4; //Y button (Operator)

constexpr int activateVisionShootHighBtnSequence = 3; //X Button (Operator)
constexpr int cancelVisionShootHighBtnSequence = 8; //Menu Button (Operator)

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------

//Drivetrain
constexpr int frontLeftMotorID = 12; //FX
constexpr int frontRightMotorID = 9; //FX
constexpr int backLeftMotorID = 11; //FX
constexpr int backRightMotorID = 10; //FX

constexpr double drive_P = 0;
constexpr double drive_I = 0;
constexpr double drive_D = 0;

constexpr int shiferFirstGear = 3; 
constexpr int shifterSecondGear = 4; 

//Climber
constexpr int winchMotorID = 4; //SRX

//Ball Pickup
constexpr int pickupMotorID = 0; //SRX
constexpr int armMotorID = 8; //SRX Changed from  3

constexpr double pickup_P = 1; 
constexpr double pickup_I = 0;
constexpr double pickup_D = 0; 
constexpr double pickup_F = 0;

constexpr double posRetract = 3650;
constexpr double posPOut = 4150; 

//PanelSpinner
constexpr int spinnerMotorID = 100; //SRX? Fix

static constexpr auto i2cPort = frc::I2C::Port::kOnboard;

static constexpr frc::Color kBlueTarget = frc::Color(0.121, 0.430, 0.447);
static constexpr frc::Color kGreenTarget = frc::Color(0.165, 0.587, 0.249);
static constexpr frc::Color kRedTarget = frc::Color(0.520, 0.356, 0.125);
static constexpr frc::Color kYellowTarget = frc::Color(0.320, 0.563, 0.114);

//Shooter
constexpr int shooterMotorID = 1; //Spark
constexpr int slaveShoooterMotorID = 2; //Spark
constexpr int wristMotorID = 3; //SRX Changed from 8

constexpr double shooter_P = 0.00006;
constexpr double shooter_I = 0.000001;
constexpr double shooter_D = 0;
constexpr double shooter_IZone = 0;
constexpr double shooter_F = 0.000015;

/*constexpr double wrist_P = 0;
constexpr double wrist_I = 0;
constexpr double wrist_D = 0;*/

//Indexer 
constexpr int indexerMotorID = 7; //SRX 
constexpr int feederMotorID = 1; //SRX

constexpr int pusherKReverse = 2;
constexpr int pusherKForward = 5;



