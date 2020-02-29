/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Auton.h"
#include "Drivetrain.h"

Auton::Auton() {}

//Needs to be commented
void Auton::crossBaseLine(double userBackLeft, double fwd, double turn, Drivetrain& Drive){
    Drive.resetEncoderCounts();
    Drive.setGear(1);

    if (Drive.getPositions()[0] <= backLeftAutonInitialPosition + userBackLeft) {
        Drive.drivePercent(-.10, 0);
    }

    else {
        Drive.drivePercent(0,0);
        Drive.setBrakeMode(ENABLED);
        frc::Wait(2);
        Drive.setBrakeMode(DISABLED);
    }
}
