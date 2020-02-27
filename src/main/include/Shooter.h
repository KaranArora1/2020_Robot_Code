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
    void moveWristFixedPositions(bool);
    void moveWrist(double);
    void moveWristToPosition(int);
    void checkLimitSwitch();
    void ShootRPMs();
    void incSpeed();    
    double * getRPMs();
    int getWristPosition();
    void Printer();
    void dashboardPrinter();

    int currentRPM = 0;

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

    int wristPosList[5] = {0, 250, 500, 750, 1000}; //About 20, 40, 60, and 75 degrees
    int currentWristPos = 0;

    double rpms[2];

    int incRPM = 1000;
    int ballsShot = 0;
    int plannedRPM = 0;
};
