/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Drivetrain.h"

Drivetrain::Drivetrain() {
    backLeft.ConfigSelectedFeedbackSensor(FeedbackDevice::IntegratedSensor, 1, 10);
    backRight.ConfigSelectedFeedbackSensor(FeedbackDevice::IntegratedSensor, 1, 10);
    frontLeft.ConfigSelectedFeedbackSensor(FeedbackDevice::IntegratedSensor, 1, 10);
    frontRight.ConfigSelectedFeedbackSensor(FeedbackDevice::IntegratedSensor, 1, 10);

    backLeft.ConfigClosedloopRamp(2.5, 10);
    backRight.ConfigClosedloopRamp(2.5, 10);
    frontLeft.ConfigClosedloopRamp(2.5, 10);
    frontRight.ConfigClosedloopRamp(2.5, 10);
  
    frontRight.SetSelectedSensorPosition(0);
    backRight.SetSelectedSensorPosition(0);
    frontLeft.SetSelectedSensorPosition(0);
    backLeft.SetSelectedSensorPosition(0);

    backLeft.Config_kP(1, drive_P, 10);
    backLeft.Config_kI(1, drive_I, 10);
    backLeft.Config_kD(1, drive_D, 10);

    backRight.Config_kP(1, drive_P, 10);
    backRight.Config_kI(1, drive_I, 10);
    backRight.Config_kD(1, drive_D, 10);

    frontLeft.Config_kP(1, drive_P, 10);
    frontLeft.Config_kI(1, drive_I, 10);
    frontLeft.Config_kD(1, drive_D, 10);

    frontRight.Config_kP(1, drive_P, 10);
    frontRight.Config_kI(1, drive_I, 10); //PID Slot Correct?
    frontRight.Config_kD(1, drive_D, 10);

    setGear(1);

    //Current limits
    //Velocity control on drivetain
    //Follower motors for Drivetrain? 
    //When scissor is deployed make max speed small and bot on first gear
    //Switch gears automatically maybe? 
    //Digital Input 
    //Safety stuff for BallPickup and Shooter
    //Winch
    //Figure out sequence with Shooting (feedBall(), pushBall())
}

void Drivetrain::Drive(double forward, double turn) {
    
    leftThrot = turn - forward;
    rightThrot = turn + forward;
    
    backLeft.Set(ControlMode::PercentOutput, leftThrot);
    frontLeft.Set(ControlMode::PercentOutput, leftThrot);
    backRight.Set(ControlMode::PercentOutput, rightThrot);
    frontRight.Set(ControlMode::PercentOutput, rightThrot);
}

//kForward = 2nd Gear, kReverse = 1st Gear CONFIRM THIS IS RIGHT
void Drivetrain::Shift() {
    if (shifter.Get() == frc::DoubleSolenoid::Value::kForward) {
		shifter.Set(frc::DoubleSolenoid::Value::kReverse);
	}
    else {
		shifter.Set(frc::DoubleSolenoid::Value::kForward);
	}
}

void Drivetrain::setGear(int gear) {
    if (gear == 1) {
        shifter.Set(frc::DoubleSolenoid::Value::kReverse);
    }
    else if (gear == 2) {
        shifter.Set(frc::DoubleSolenoid::Value::kForward);
    }
}

int * Drivetrain::getPositions() {
    positions[0] = backLeft.GetSelectedSensorPosition(1);
    positions[1] = frontLeft.GetSelectedSensorPosition(1);
    positions[2] = backRight.GetSelectedSensorPosition(1);
    positions[3] = frontRight.GetSelectedSensorPosition(1);

    return positions;
}

int * Drivetrain::getVelocities() {
    velocities[0] = backLeft.GetSelectedSensorVelocity(1);
    velocities[1] = frontLeft.GetSelectedSensorVelocity(1);
    velocities[2] = backRight.GetSelectedSensorVelocity(1);
    velocities[3] = frontRight.GetSelectedSensorVelocity(1);

    return velocities;
}

double * Drivetrain::getRPMs() {
    rpms[0] = backLeft.GetSelectedSensorVelocity(1) * velToRPM_FX;
    rpms[1] = frontLeft.GetSelectedSensorVelocity(1) * velToRPM_FX;
    rpms[2] = backRight.GetSelectedSensorVelocity(1) * velToRPM_FX;
    rpms[3] = frontRight.GetSelectedSensorVelocity(1) * velToRPM_FX;

    return rpms;
}

double * Drivetrain::getCurrents() {
    currents[0] = backLeft.GetOutputCurrent();
    currents[1] = frontLeft.GetOutputCurrent();
    currents[2] = backRight.GetOutputCurrent();
    currents[3] = frontRight.GetOutputCurrent();

    return currents;
}

void Drivetrain::Printer() {

    getPositions();
    getVelocities();
    getRPMs();
    getCurrents();

    std::cout << "Back left:" << std::endl;
    std::cout << positions[0] << " counts" << std::endl;
    //std::cout << velocities[0] << " counts/100ms" << std::endl;
    std::cout << rpms[0] << " RPM" << std::endl;
    std::cout << currents[0] << " Amps" << std::endl;
    std::cout << std::endl;

    std::cout << "Front left:" << std::endl;
    std::cout << positions[1] << " counts" << std::endl;
    //std::cout << velocities[1] << " counts/100ms" << std::endl;
    std::cout << rpms[1] << " RPM" << std::endl;
    std::cout << currents[1] << " Amps" << std::endl;
    std::cout << std::endl;

    std::cout << "Back right:" << std::endl;
    std::cout << positions[2] << " counts" << std::endl;
    //std::cout << velocities[2] << " counts/100ms" << std::endl;
    std::cout << rpms[2] << " RPM" << std::endl;
    std::cout << currents[2] << " Amps" << std::endl;
    std::cout << std::endl;

    std::cout << "Front right:" << std::endl;
    std::cout << positions[3] << " counts" << std::endl;
    //std::cout << velocities[3] << " counts/100ms" << std::endl;
    std::cout << rpms[3] << " RPM" << std::endl;
    std::cout << currents[3] << " Amps" << std::endl;
    std::cout << std::endl;

    std::cout << "Shifter State " << ((shifter.Get() == frc::DoubleSolenoid::Value::kForward) ? "kForward" : "kReverse") << std::endl;
    std::cout << "Drivetrain Gear " <<  ((shifter.Get() == frc::DoubleSolenoid::Value::kForward) ? "2nd Gear" : "1st Gear") << std::endl;
}

void Drivetrain::dashboardPrinter() { 

    getPositions();
    getVelocities();
    getRPMs();
    getCurrents();

    frc::SmartDashboard::PutNumber("Back Left Motor Position (counts)", positions[0]);
    frc::SmartDashboard::PutNumber("Back Left Motor Velocity (counts/100ms)", velocities[0]);
    frc::SmartDashboard::PutNumber("Back Left Motor RPM", rpms[0]);
    frc::SmartDashboard::PutNumber("Back Left Motor Current", currents[0]);

    frc::SmartDashboard::PutNumber("Front Left Motor Position (counts)", positions[1]);
    frc::SmartDashboard::PutNumber("Front Left Motor Velocity (counts/100ms)", velocities[1]);
    frc::SmartDashboard::PutNumber("Front Left Motor RPM", rpms[1]);
    frc::SmartDashboard::PutNumber("Front Left Motor Current", currents[1]);

    frc::SmartDashboard::PutNumber("Back Right Motor Position (counts)", positions[2]);
    frc::SmartDashboard::PutNumber("Back Right Motor Velocity (counts/100ms)", velocities[2]);
    frc::SmartDashboard::PutNumber("Back Right Motor RPM", rpms[2]);
    frc::SmartDashboard::PutNumber("Back Right Motor Current", currents[2]);

    frc::SmartDashboard::PutNumber("Front Right Motor Position (counts)", positions[3]);
    frc::SmartDashboard::PutNumber("Front Right Motor Velocity (counts/100ms)", velocities[3]);
    frc::SmartDashboard::PutNumber("Front Right Motor RPM", rpms[3]);
    frc::SmartDashboard::PutNumber("Front Right Motor Current", currents[3]);

    frc::SmartDashboard::PutString("Shifter State", (shifter.Get() == frc::DoubleSolenoid::Value::kForward) ? "kForward" : "kReverse"); 
    frc::SmartDashboard::PutString("Drivetrain Gear", (shifter.Get() == frc::DoubleSolenoid::Value::kForward) ? "2nd Gear" : "1st Gear");
}