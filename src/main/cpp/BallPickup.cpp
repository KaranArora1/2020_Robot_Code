/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "BallPickup.h"

BallPickup::BallPickup() {
   //Encoder should be here I think
}

void BallPickup::Pickup(double speed) {
    
    pickup.Set(ControlMode::PercentOutput, speed);

    /*//New Code
    if (speed > 0) {
        extndBallIntake.Set(frc::DoubleSolenoid::Value::kForward);
        pickup.Set(ControlMode::PercentOutput, speed);
        Index.Spin(speed/2);
    }
    else if (speed == 0) {
        extndBallIntake.Set(frc::DoubleSolenoid::Value::kReverse);
        
    }
    else if (speed < 0) {
        extndBallIntake.Set(frc::DoubleSolenoid::Value::kForward);
        pickup.Set(ControlMode::PercentOutput, speed * -1);   
    }*/
    
    //Printer();
    dashboardPrinter();
}

void BallPickup::Printer() {
    
}

void BallPickup::dashboardPrinter() {
    
}