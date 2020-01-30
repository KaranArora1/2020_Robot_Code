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
    void moveWrist(double);
    void Printer();
    void DashboardPrinter();

  private:
    rev::CANSparkMax shooter{shooterMotorID, rev::CANSparkMax::MotorType::kBrushless};

    //Rename this possibly if I don't make it into a slave
    rev::CANSparkMax slaveShooter{slaveShoooterMotorID, rev::CANSparkMax::MotorType::kBrushless}; //Make into Slave

    WPI_TalonSRX wrist{wristMotorID};
    
    rev::CANEncoder shooterEncoder = shooter.GetEncoder();
    rev::CANEncoder slaveShooterEncoder = slaveShooter.GetEncoder();

    int posList[5] = {1000, 1000, 1000, 1000, 1000};

};
