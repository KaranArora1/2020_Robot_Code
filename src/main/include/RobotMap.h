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
#include "rev/CANSparkMax.h"

constexpr int fwdJoyChl = 1;
constexpr int trnJoyChl = 4;

constexpr int shootJoyChl = 2;
constexpr int shootIntakeJoyChl = 3;

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
