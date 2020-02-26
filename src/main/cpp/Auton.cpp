/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Auton.h"
#include "Drivetrain.h"

Auton::Auton() {
}

void Auton::crossBaseLine(double userBackLeft, double fwd, double turn, Drivetrain& Drive){
    Drive.resetEncoderCounts();

    Drive.setGear(1);

    if (Drive.getPositions()[0] <= backLeftAutonInitialPosition + userBackLeft) {

        /*backLeft.Set(ControlMode::PercentOutput, leftThrot);
        frontLeft.Set(ControlMode::PercentOutput, leftThrot);
        backRight.Set(ControlMode::PercentOutput, rightThrot);
        frontRight.Set(ControlMode::PercentOutput, rightThrot);*/
        Drive.drivePercent(-.10, 0);
    }

    else {

    /*  backLeft.Set(ControlMode::PercentOutput, 0);
        frontLeft.Set(ControlMode::PercentOutput, 0);
        backRight.Set(ControlMode::PercentOutput, 0);
        frontRight.Set(ControlMode::PercentOutput, 0);   

        backLeft.SetNeutralMode(NeutralMode::Brake);
        backRight.SetNeutralMode(NeutralMode::Brake);
        frontLeft.SetNeutralMode(NeutralMode::Brake);
        frontRight.SetNeutralMode(NeutralMode::Brake);

        frc::Wait(2);

        backLeft.SetNeutralMode(NeutralMode::Coast);
        backRight.SetNeutralMode(NeutralMode::Coast);
        frontLeft.SetNeutralMode(NeutralMode::Coast);
        frontRight.SetNeutralMode(NeutralMode::Coast);*/

        Drive.drivePercent(0,0);
        Drive.setBrakeMode(ENABLED);
        frc::Wait(2);
        Drive.setBrakeMode(ENABLED);
    }
}
