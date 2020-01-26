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
#include "frc/TimedRobot.h"
#include "frc/smartdashboard/SendableChooser.h"
#include "frc/smartdashboard/SmartDashboard.h"
#include "networktables/NetworkTable.h" //Vision
#include "networktables/NetworkTableInstance.h" //Vision
#include "rev/ColorSensorV3.h" //Color Sensor
#include "rev/ColorMatch.h" //Color Sensor
#include "ctre/Phoenix.h"
#include "rev/CANSparkMax.h" //Sparks

//Joystick
constexpr int driverJoyUSBPort = 0; //Can be changed in Driver Station
constexpr int operatorJoyUSBPort = 1;

constexpr int fwdJoyChl = 1; //Y Axis on Left Joystick
constexpr int trnJoyChl = 4; //X Axis on Right Joystick

constexpr int shootJoyChl = 3;  //Right Trigger
constexpr int shootIntakeJoyChl = 2; //Left Trigger
constexpr int shootChangeLevelUpBtn = 6; //Right Bumper
constexpr int shootChangeLevelDownBtn = 5; //Left Bumper

constexpr int climbBtn = 8; //Menu button

//Drivetrain
constexpr int frontLeftMotorID = 12; //FX
constexpr int frontRightMotorID = 9; //FX
constexpr int backLeftMotorID = 11; //FX
constexpr int backRightMotorID = 10; //FX

constexpr int PCMID = 100; //FIX
constexpr int 

//Climber
constexpr int climbID = 100; //SRX Probably (FIX)
constexpr int setShifterFirstGear = ;
constexpr int setShifterSecondGear = 4;

//Intake

//PanelSpinner
constexpr int spinnerID = 100; //SRX? Fix

//Shooter
constexpr int shooterID = 1; //Spark
constexpr int slaveShoooterID = 2; //Spark
constexpr int wristID = 100; //SRX Fix

//Drivetrain

constexpr int pigeonID = 0; //Fix

constexpr double Drivetrain_P = 0;
constexpr double Drivetrain_I = 0;
constexpr double Drivetrain_D = 0;

constexpr int maxSpeedLo = 0;
constexpr int maxSpeedHi = 0;
constexpr double gearRatioLo = 0;
constexpr double gearRatioHi = 0;
constexpr int wheelR = 0;

constexpr bool ACCEL_LIMIT_ENABLED = false;

constexpr bool drivetrainVoltageControl = true;
constexpr bool drivetrainAutoheading = false;


