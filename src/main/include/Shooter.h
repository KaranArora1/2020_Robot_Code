/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "RobotMap.h"

class Shooter {
 public:
    Shooter();
    void Shoot(double);
    void moveWristFixedPositions(direction);
    void moveWrist(double);
    void moveWristToPosition(int);
    void moveWristDownOverride(double);
    void toggleWristOverride();
    bool checkLimitSwitch();
    void ShootRPMs();
    void incSpeed(int);    
    void incSpeed(direction);
    double * getRPMs();
    int getWristPosition();
    void Printer();
    void dashboardPrinter();

    int currentRPM = 0;
    int currentWristPos = 0;

    enableStatus wristOverrideStatus = DISABLED;

  private:
    rev::CANSparkMax shooter{shooterMotorID, rev::CANSparkMax::MotorType::kBrushless};

    //Rename this possibly if I don't make it into a slave
    rev::CANSparkMax slaveShooter{slaveShoooterMotorID, rev::CANSparkMax::MotorType::kBrushless}; //Make into Slave FIX

    rev::CANPIDController shooterPID = shooter.GetPIDController();
    rev::CANPIDController slaveShooterPID = slaveShooter.GetPIDController();

    WPI_TalonSRX wrist{wristMotorID}; 
    
    rev::CANEncoder shooterEncoder = shooter.GetEncoder();
    rev::CANEncoder slaveShooterEncoder = slaveShooter.GetEncoder();

    frc::DigitalInput wristSwitch{wristSwitchID};

    int wristPosList[8] = {0, 500, 550, 600, 650, 700, 800, 1100}; //About 44, 52, 61, and 70, 100 degrees LOOK AT THIS 

    int speeds[10] = {0, 1000, 1500, 1750, 2000, 2250, 2500, 2750, 3000, 3500};
    int currentSpeedPos = 0;

    double rpms[2];

    int ballsShot = 0;
    int plannedRPM = 0;

    enableStatus shooterStatus = DISABLED;
};
