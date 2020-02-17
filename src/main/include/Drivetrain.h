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
    void Vision(double, double);
    void Shift();
    void setGear(int);
    int * getPositions();
    int * getVelocities();
    double * getRPMs();
    double * getCurrents(); 
    void Printer();
    void dashboardPrinter();

  private:
    WPI_TalonFX frontLeft{frontLeftMotorID};
    WPI_TalonFX frontRight{frontRightMotorID};
    WPI_TalonFX backLeft{backLeftMotorID};
    WPI_TalonFX backRight{backRightMotorID};

    int positions[4];
    int velocities[4];
    double rpms[4];
    double currents[4];

    frc::DoubleSolenoid shifter{PCMID, shiferFirstGear, shifterSecondGear};

    double turn, forward, leftThrot, rightThrot;
};
