/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "BallPickup.h"

BallPickup::BallPickup() {
    arm.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Absolute, 0, 10); 
    arm.SetSelectedSensorPosition(0);

    pickup.Config_kP(0, pickup_P, 10);
    pickup.Config_kI(0, pickup_I, 10);
    pickup.Config_kD(0, pickup_D, 10);
    pickup.Config_kF(0, pickup_F, 10);

    arm.ConfigPeakOutputForward(0.75);
    arm.ConfigPeakOutputReverse(-0.75);

    arm.ConfigForwardSoftLimitThreshold(500); //Right direction for forward and reverse? Is this fine?
    arm.ConfigReverseSoftLimitThreshold(0); 

    arm.ConfigForwardSoftLimitEnable(true);
    arm.ConfigReverseSoftLimitEnable(true);
}

//Set speed of pickup belts
void BallPickup::Pickup(double speed) {
    pickup.Set(ControlMode::PercentOutput, speed);
}

//Extend/retract arm with position control
void BallPickup::moveArm() {
    if (armState == EXTENDED) {
        arm.Set(ControlMode::Position, posRetract);
        //arm.Set(ControlMode::Position, 0); //Need to fix?
        armState = RETRACTED;
    }
    else { //shooter to
        arm.Set(ControlMode::Position, posOut);
        //arm.Set(ControlMode::Position, 500);
        armState = EXTENDED; 
    }
}

//Extend/retract arm with Joystick instead of position control
void BallPickup::moveArm(double speed) { 
    arm.Set(ControlMode::PercentOutput, speed);
}

int BallPickup::getPickupArmPosition() {
    return arm.GetSelectedSensorPosition(0);
}

void BallPickup::Printer() {
    std::cout << "Arm Position " << getPickupArmPosition() << " Counts" << std::endl;
}

void BallPickup::dashboardPrinter() {
    frc::SmartDashboard::PutNumber("Arm Position Counts", getPickupArmPosition());
    frc::SmartDashboard::PutString("Dither Mode On", (armState == ENABLED) ? "ENABLED" : "DISABLED");
}
