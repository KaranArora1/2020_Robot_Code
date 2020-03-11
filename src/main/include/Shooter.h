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
    void moveWristFixedPositions(direction);
    void moveWrist(double);
    void moveWristToPosition(int);
    void toggleWristOverride();
    bool checkLimitSwitch();
    void ShootRPMs(double);
    void ShootFixedRPMS();
    void shootSolution(direction);
    void shootOverride();
    void incSpeed(int);    
    void incSpeed(direction);
    double * getRPMs();
    int getWristPosition();
    void Printer();
    void dashboardPrinter();
    void unJamBall();

    int currentRPM = 0;
    int currentWristPos = 0;

    enableStatus wristOverrideStatus = DISABLED;
    enableStatus shootOverrideStatus = DISABLED;
    enableStatus shooterStatus = DISABLED;

    double shooterLoopTime;

  private:

    double shooterRealTime = 0;
    rev::CANSparkMax shooter{shooterMotorID, rev::CANSparkMax::MotorType::kBrushless};

    //Rename this possibly if I don't make it into a slave
    rev::CANSparkMax slaveShooter{slaveShoooterMotorID, rev::CANSparkMax::MotorType::kBrushless}; //Make into Slave FIX

    rev::CANPIDController shooterPID = shooter.GetPIDController();
    rev::CANPIDController slaveShooterPID = slaveShooter.GetPIDController();

    WPI_TalonSRX wrist{wristMotorID}; 
    
    rev::CANEncoder shooterEncoder = shooter.GetEncoder();
    rev::CANEncoder slaveShooterEncoder = slaveShooter.GetEncoder();

    frc::DigitalInput wristSwitch{wristSwitchID};

    //int wristPosList[8] = {0, 500, 550, 600, 650, 700, 800, 1100}; //About 44, 52, 61, and 70, 100 degrees LOOK AT THIS 
    //int speeds[10] = {0, 1000, 1500, 1750, 2000, 2250, 2500, 2750, 3000, 3500};

    int wristPosList[4] = {0, 550, 700, 600};
    int speeds[4] = {1000, 1000, 2500, 3000};
    
    int currentSpeedPos = 0;

    double rpms[2];

    int plannedRPM = speeds[0];
};
