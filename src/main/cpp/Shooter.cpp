/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Shooter.h"

Shooter::Shooter() {
    slaveShooter.SetInverted(true);

    wrist.SetInverted(true);
    wrist.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Absolute, 0, 10);
    wrist.SetSelectedSensorPosition(0);

    shooterPID.SetP(shooter_P);
    slaveShooterPID.SetP(shooter_P);

    shooterPID.SetI(shooter_I);
    slaveShooterPID.SetI(shooter_I);

    shooterPID.SetD(shooter_D);
    slaveShooterPID.SetD(shooter_D);

    shooterPID.SetFF(shooter_F);
    slaveShooterPID.SetFF(shooter_F);

    shooterPID.SetIZone(shooter_IZone);
    slaveShooterPID.SetIZone(shooter_IZone);

    /*wrist.Config_kP(0, wrist_P, 10);
    wrist.Config_kI(0, wrist_I, 10);
    wrist.Config_kI(0, wrist_D, 10);*/
}

void Shooter::Shoot(double speed) {
    shooter.Set(speed);
    slaveShooter.Set(speed);
    /*if (shooter.GetOutputCurrent() > 45) { //FIX CURRENT VALUE
        ballsShot++;
    }*/
}

//Temporary function
void Shooter::ShootRPMs() {
    shooterPID.SetReference(currentRPM, rev::ControlType::kVelocity);
    slaveShooterPID.SetReference(currentRPM, rev::ControlType::kVelocity);
}

//Temporary function
void Shooter::incSpeed() {
    currentRPM += incRPM;

    if (currentRPM > 6000) {
        currentRPM = 0;
    }
    else if (currentRPM > 5000) {
        currentRPM = 5800;
    } 
}

void Shooter::moveWrist(double input) {
    wrist.Set(ControlMode::PercentOutput, input);
   /*if(currentPos == Home){
       master.Set(ControlMode::Position, downPos + sensorOffset);
       slave.Follow(master);
       currentPos = Down;
   }else if(currentPos == Down){
        master.Set(ControlMode::Position, homePos + sensorOffset);
        slave.Follow(master);
        currentPos = Home;
       }*/
}

double * Shooter::getRPMs() {
    rpms[0] = shooterEncoder.GetVelocity();
    rpms[1] = slaveShooterEncoder.GetVelocity();

    return rpms;
}

int Shooter::getWristPosition() {
    return wrist.GetSelectedSensorPosition(0);
}

void Shooter::Printer() {
    getRPMs();

    std::cout << "Shooter (CAN ID 1) " << rpms[0] << " RPM" << std::endl;
    std::cout << "Slave Shooter (CAN ID 2) " << rpms[1] << " RPM" << std::endl;
    std::cout << "Wrist Position " << getWristPosition() << " counts" << std::endl;
    std::cout << "Target RPM: " << currentRPM << std::endl;
}

void Shooter::dashboardPrinter() {
    getRPMs();

    frc::SmartDashboard::PutNumber("Difference Between Target and Actual", fabs(currentRPM - shooterEncoder.GetVelocity()));
    frc::SmartDashboard::PutNumber("Shooter (CAN ID 1) RPM", rpms[0]);
    frc::SmartDashboard::PutNumber("Slave Shooter (CAN ID 2) RPM", rpms[1]);
    frc::SmartDashboard::PutNumber("Wrist Position (counts)", getWristPosition());
    frc::SmartDashboard::PutNumber("Target RPM", currentRPM);
    frc::SmartDashboard::PutNumber("Balls Shot", ballsShot);
}