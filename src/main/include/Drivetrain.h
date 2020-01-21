/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "RobotMap.h"

class Drivetrain {
  public:
    Drivetrain();
    void Drive(double, double);

  private:
  
    WPI_TalonFX front_left{12};
    WPI_TalonFX front_right{9};
    WPI_TalonFX back_left{11};
    WPI_TalonFX back_right{10};

    double turn, forward, leftThrot, rightThrot;

};
