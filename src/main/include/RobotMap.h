#pragma once

#include <iostream>
#include <string>
#include "frc/WPILib.h"
#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include "rev/ColorSensorV3.h"
#include "rev/ColorMatch.h"
#include "ctre/Phoenix.h"

constexpr int fwdJoyChl = 1;
constexpr int trnJoyChl = 4;

constexpr int shiftBtn = 1; //A
constexpr int shiftStick = 9; //left stick

constexpr int hatchRun = 1; //A
constexpr int hatchAbort = 2; //B

constexpr int eleLift = 6; //Right Bumper
constexpr int eleLower = 5; //Left Bumper
constexpr int eleOverride = 3; //X
constexpr int eleOverrideAxis = 1; //Axis 1

constexpr int climbIncStage = 8; //Menu
constexpr int climbDecStage = 7; //View
constexpr int climbWheelAxis = 1; //Axis 1

constexpr int cargoToggle = 4; //Y
constexpr int cargoIntakeAxis = 2; //Eject Is Right Trigger, Intake Is Left Trigger
constexpr int cargoEjectAxis = 3;

constexpr int climberWheelsFwdAxis = 2;
constexpr int climberWheelsRevAxis = 3;

constexpr int pressureTransID = 0;


//
//
//
//Drivetrain
//
//
//

constexpr int leftDriveMotor1 = 9;
constexpr int leftDirveMotor2 = 8;
constexpr int rightDriveMotor1 = 7;
constexpr int rightDriveMotor2 = 6;

constexpr int Pigeon = 0;

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

constexpr int setShifterFirstGear = 5;
constexpr int setShifterSecondGear = 4;
