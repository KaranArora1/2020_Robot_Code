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
void Auton::lowGoal(double userBackLeft, double fwd, double turn, Drivetrain& Drive, Shooter& Shoot, Indexer& Index){
    //Drive.resetEncoderCounts();
    //Drive.setGear(1); //THIS IS DEFNIITELY NOT RIGHT

    if (Drive.getPositions()[0] <= backLeftAutonInitialPosition + userBackLeft) {
        Drive.drivePercent(-.20, 0);
        
        Shoot.moveWristToPosition(500);
        Shoot.Shoot(1000); 
    }
       
    else {
        Drive.drivePercent(0, 0);
        Drive.setBrakeMode(ENABLED); //Only for testing
        loopTime += 1;
        realTime = (loopTime * 40) / 1000;
        //frc::Wait(2);
        //Drive.setBrakeMode(DISABLED); //Only for testing
        
        if (realTime < 2) {
            Index.feedBall(FEEDER_WHEEL_SPEED);
            Index.setPushBall(EXTENDED);
            Index.Spin(INDEXER_SPEED_FINAL_BOT);
        }
        else {
            Index.feedBall(0);
            Index.setPushBall(RETRACTED);
            Index.Spin(0);
            Shoot.Shoot(0);
            Shoot.moveWristToPosition(0);
        }

    /*if(ifshot = false){

        Shoot.Shoot(0.30);
        ifshot = true;
    }*/
}
}

void Auton::highGoal(double userBackLeft, double fwd, double turn, Drivetrain& Drive, Shooter& Shoot, Indexer& Index){

    if (Drive.getPositions()[0] <= backLeftAutonInitialPosition + userBackLeft) {
        Drive.drivePercent(-.20, 0);
        
        Shoot.moveWristToPosition(1100);
        Shoot.Shoot(2000); 
    }

    else {
        Drive.drivePercent(0, 0);
        Drive.setBrakeMode(ENABLED); //Only for testing
        loopTime += 1;
        realTime = (loopTime * 40) / 1000;
        //frc::Wait(2);
        //Drive.setBrakeMode(DISABLED); //Only for testing
        
        if (realTime < 2) {
            Index.feedBall(FEEDER_WHEEL_SPEED);
            Index.setPushBall(EXTENDED);
            Index.Spin(INDEXER_SPEED_FINAL_BOT);
        }
        else {
            Index.feedBall(0);
            Index.setPushBall(RETRACTED);
            Index.Spin(0);
            Shoot.Shoot(0);
            Shoot.moveWristToPosition(0);
        }
    }

    /*if(ifshot = false){

        Shoot.Shoot(0.30);
        ifshot = true;
    }*/
}

void Auton::Printer() {

}

void Auton::dashboardPrinter() {
    
}