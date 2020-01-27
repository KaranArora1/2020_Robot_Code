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
    void Intake(double);
    void moveWrist(double);
    void Printer();

  private:
    rev::CANSparkMax shooter{shooterID, rev::CANSparkMax::MotorType::kBrushless};
    rev::CANSparkMax slaveShooter{slaveShoooterID, rev::CANSparkMax::MotorType::kBrushless};

    WPI_TalonSRX wrist{wristID};
    
    rev::CANEncoder shooterEncoder = shooter.GetEncoder();
    rev::CANEncoder slaveShooterEncoder = slaveShooter.GetEncoder();

    int posList[5] = {1000, 1000, 1000, 1000, 1000};

};
