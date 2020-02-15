/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "BallPickup.h"

BallPickup::BallPickup() {
    arm.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Absolute, 0, 10); //Relative or Absolute? 
    arm.SetSelectedSensorPosition(0);

    pickup.Config_kP(0, pickupP, 10);
    pickup.Config_kI(0, pickupI, 10);
    pickup.Config_kD(0, pickupD, 10);
    pickup.Config_kF(0, pickupF, 10);

    arm.ConfigPeakOutputForward(0.75);
}

void BallPickup::Pickup(double speed) {
    
    pickup.Set(ControlMode::PercentOutput, speed);
    
}

void BallPickup::moveArm() {
    if (state) {
        //arm.Set(ControlMode::Position, posRetract);
        arm.Set(ControlMode::Position, 0);
        state = false;
    }
    else { //shooter to
        //arm.Set(ControlMode::Position, posPOut);
        arm.Set(ControlMode::Position, 500);
        state = true;
    }
}

void BallPickup::moveArm(double speed) {
    arm.Set(ControlMode::PercentOutput, speed);
}

bool BallPickup::getState() {
    return state;
}

int BallPickup::getPickupArmPosition() {
    return arm.GetSelectedSensorPosition(0);
}

void BallPickup::Printer() {
    
}

void BallPickup::dashboardPrinter() {
    frc::SmartDashboard::PutNumber("Arm Position Counts", getPickupArmPosition());
}