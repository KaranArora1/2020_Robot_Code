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

    if (Drive.getPositions()[0] <= backLeftAutonInitialPosition + userBackLeft) {
        Drive.drivePercent(-.20, 0);
        
        Shoot.moveWristToPosition(550);
        Shoot.ShootRPMs(1000); 
    }
       
    else {
        Drive.drivePercent(0, 0);
        Drive.setBrakeMode(ENABLED); //Only for testing

        loopTime += 1;
        realTime = (loopTime * 40) / 1000;
        
        if (realTime < autonTime) {
            Index.feedBall(FEEDER_WHEEL_SPEED);
            Index.setPushBall(EXTENDED);
            Index.Spin(INDEXER_SPEED_FINAL_BOT);
        }
        else {
            Index.feedBall(0);
            Index.setPushBall(RETRACTED);
            Index.Spin(0);
            Shoot.ShootRPMs(0);
            Shoot.moveWristToPosition(0);
        }
    }
}

void Auton::highGoal(double userBackLeft, double fwd, double turn, Drivetrain& Drive, Shooter& Shoot, Indexer& Index){

    loopTime += 1;
    realTime = (loopTime * 40) / 1000;

    if (realTime < 4) {
        Shoot.moveWristToPosition(750); //Used to be 700
        Shoot.ShootRPMs(2500); //Used to be 2250
    }

    else if (realTime < 8) {
        Index.feedBall(FEEDER_WHEEL_SPEED);
        Index.setPushBall(EXTENDED);
        Index.Spin(INDEXER_SPEED_FINAL_BOT);
    }

    else {
        Index.feedBall(0);
        Index.setPushBall(RETRACTED);
        Index.Spin(0);
        Shoot.ShootRPMs(0);
        Shoot.moveWristToPosition(0);

        if (Drive.getPositions()[0] >= backLeftAutonInitialPosition + userBackLeft) {
            Drive.drivePercent(.20, 0);
        }
        else {
            Drive.drivePercent(0, 0);
        }
    }
}

void Auton::highGoalPickup(double userBackLeft, double fwd, double turn, Drivetrain& Drive, Shooter& Shoot, Indexer& Index, BallPickup& Pickup) {
    
    loopTime += 1;
    realTime = (loopTime * 40) / 1000;

    if (realTime < 4) {
        Shoot.moveWristToPosition(750); //Used to be 700
        Shoot.ShootRPMs(2500); //Used to be 2250
    }

    else if (realTime < 8) {
        Index.feedBall(FEEDER_WHEEL_SPEED);
        Index.setPushBall(EXTENDED);
        Index.Spin(INDEXER_SPEED_FINAL_BOT);
    }

    else {
        Index.feedBall(0);
        Index.setPushBall(RETRACTED);
        //Index.Spin(0);
        Shoot.ShootRPMs(0);
        Shoot.moveWristToPosition(0);

        Index.Divet(2.5, 3, INDEXER_SPEED_FINAL_BOT); 

        if (Drive.getPositions()[0] >= backLeftAutonInitialPosition + userBackLeft) {
            Drive.drivePercent(.17, 0);

            if (Pickup.armState == RETRACTED) {
                Pickup.moveArm();
            }

            Pickup.Pickup(BALLPICKUP_ARM_SPEED);
        }
        else {
            if (Pickup.armState == EXTENDED) {
                Pickup.moveArm();
            }

            Pickup.Pickup(0);
            Drive.drivePercent(0, 0);
        } 
    }
}

void Auton::Printer() {

}

void Auton::dashboardPrinter() {
    
}