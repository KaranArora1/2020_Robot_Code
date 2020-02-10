/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Drivetrain.h"

Drivetrain::Drivetrain() {
    //Use Phoenix Tuner to test encoders, maybe use IntegratedSensor or Encoder Class, CTRE_MagEncoder_Relative
    //back_left.ConfigSelectedFeedbackSensor(FeedbackDevice::IntegratedSensor, 0, 10);
    //back_right.ConfigSelectedFeedbackSensor(FeedbackDevice::IntegratedSensor, 0, 10);
    //front_left.ConfigSelectedFeedbackSensor(FeedbackDevice::IntegratedSensor, 0, 10);
    //front_right.ConfigSelectedFeedbackSensor(FeedbackDevice::IntegratedSensor, 0, 10);

    backLeft.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, 10);
    backRight.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, 10);
    frontLeft.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, 10);
    frontRight.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, 10);
  
    frontRight.SetSelectedSensorPosition(0);
    backRight.SetSelectedSensorPosition(0);
    frontLeft.SetSelectedSensorPosition(0);
    backLeft.SetSelectedSensorPosition(0);
}

void Drivetrain::Drive(double forward, double turn) {
    
    leftThrot = turn - forward;
    rightThrot = turn + forward;
    
    backLeft.Set(ControlMode::PercentOutput, leftThrot);
    frontLeft.Set(ControlMode::PercentOutput, leftThrot);
    backRight.Set(ControlMode::PercentOutput, rightThrot);
    frontRight.Set(ControlMode::PercentOutput, rightThrot);

    //Printer();
    dashboardPrinter();
}

void Drivetrain::Shift() {
    if (shifter.Get() == frc::DoubleSolenoid::Value::kForward) {
		shifter.Set(frc::DoubleSolenoid::Value::kReverse);
		//currentGear = 2;
		//gearHasChanged = true;
	}
    else {
		shifter.Set(frc::DoubleSolenoid::Value::kForward);
		//currentGear = 1;
		//gearHasChanged = true;
	}
}

int * Drivetrain::getPositions() {
    positions[0] = backLeft.GetSelectedSensorPosition(0);
    positions[1] = frontLeft.GetSelectedSensorPosition(0);
    positions[2] = backRight.GetSelectedSensorPosition(0);
    positions[3] = frontRight.GetSelectedSensorPosition(0);

    return positions;
}

int * Drivetrain::getVelocities() {
    velocities[0] = backLeft.GetSelectedSensorVelocity(0);
    velocities[1] = frontLeft.GetSelectedSensorVelocity(0);
    velocities[2] = backRight.GetSelectedSensorVelocity(0);
    velocities[3] = frontRight.GetSelectedSensorVelocity(0);

    return velocities;
}

double * Drivetrain::getRPMs() {
    rpms[0] = backLeft.GetSelectedSensorVelocity(0) * velToRPM_FX;
    rpms[1] = frontLeft.GetSelectedSensorVelocity(0) * velToRPM_FX;
    rpms[2] = backRight.GetSelectedSensorVelocity(0) * velToRPM_FX;
    rpms[3] = frontRight.GetSelectedSensorVelocity(0) * velToRPM_FX;

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
}

void Drivetrain::dashboardPrinter() { 

    getPositions();
    getVelocities();
    getRPMs();
    getCurrents();

    /*frc::SmartDashboard::PutNumber("Back Left Motor Position (counts)", positions[0]);
    frc::SmartDashboard::PutNumber("Back Left Motor Velocity (counts/100ms)", velocities[0]);
    frc::SmartDashboard::PutNumber("Back Left Motor RPM", rpms[0]);*/
    frc::SmartDashboard::PutNumber("Back Left Motor Current", currents[0]);

    /*frc::SmartDashboard::PutNumber("Front Left Motor Position (counts)", positions[1]);
    frc::SmartDashboard::PutNumber("Front Left Motor Velocity (counts/100ms)", velocities[1]);
    frc::SmartDashboard::PutNumber("Front Left Motor RPM", rpms[1]);*/
    frc::SmartDashboard::PutNumber("Front Left Motor Current", currents[1]);

    /*frc::SmartDashboard::PutNumber("Back Right Motor Position (counts)", positions[2]);
    frc::SmartDashboard::PutNumber("Back Right Motor Velocity (counts/100ms)", velocities[2]);
    frc::SmartDashboard::PutNumber("Back Right Motor RPM", rpms[2]);*/
    frc::SmartDashboard::PutNumber("Back Right Motor Current", currents[2]);

    /*frc::SmartDashboard::PutNumber("Front Right Motor Position (counts)", positions[3]);
    frc::SmartDashboard::PutNumber("Front Right Motor Velocity (counts/100ms)", velocities[3]);
    frc::SmartDashboard::PutNumber("Front Right Motor RPM", rpms[3]);*/
    frc::SmartDashboard::PutNumber("Front Right Motor Current", currents[3]);

    frc::SmartDashboard::PutString("Shifter State", (shifter.Get() == frc::DoubleSolenoid::Value::kForward) ? "kForward" : "kReverse");
}