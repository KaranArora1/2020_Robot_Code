/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Drivetrain.h"

Drivetrain::Drivetrain() {

    frontRight.SetInverted(true);
    backRight.SetInverted(true); //Do I have to switch between these when doing percent and velocity control? 
    frontRight.SetSensorPhase(true);
    backRight.SetSensorPhase(true);

    frontLeft.SetInverted(false);
    backLeft.SetInverted(false);
    frontLeft.SetSensorPhase(false);
    backLeft.SetSensorPhase(false);

    configMotor(backLeft);
    configMotor(frontLeft);
    configMotor(frontRight);
    configMotor(backRight);
    setGear(1);
    setBrakeMode(DISABLED);

    //Current limits on devices and on Talon FX's
    //Current too high for too long return to home position
    //figure out encoder phase and inverting
    //Velocity control on drivetain
    //Switch gears automatically maybe? 
    //Safety stuff for BallPickup and Shooter
    //Winch
    //Set range on what counts each devicd can operate for encoder counts ADD OVERRIDE AND TALK WITH ANITA
    //figure out different PID slots for balaji
    //Integrate Auton
    //Remove Peak Outputs in Drivetrain
    //Clean up Balaji code and other code 
    //Figure out brake mode stuff
    //Update smartdashboard and printer functions
}

void Drivetrain::drivePercent(double forward, double turn) {
    
    leftThrot = turn - forward;
    rightThrot = turn + forward;
    
    backLeft.Set(TalonFXControlMode::PercentOutput, leftThrot);
    frontLeft.Set(TalonFXControlMode::PercentOutput, leftThrot);
    backRight.Set(TalonFXControlMode::PercentOutput, rightThrot);
    frontRight.Set(TalonFXControlMode::PercentOutput, rightThrot);
}

void Drivetrain::driveVelocity(double forward, double turn) {
    
    leftThrot = turn - forward;
    rightThrot = turn + forward;

    //leftThrot = leftThrot* maxFalconVelocity; //Not 18750 like in email
    //rightThrot = rightThrot* maxFalconVelocity;

    leftThrot = (leftThrot * 18750) - 1750;
    rightThrot = (rightThrot * 18750) - 1750;

    getVelocities();

    frc::SmartDashboard::PutNumber("leftThrot", leftThrot);
    frc::SmartDashboard::PutNumber("velocity on backLeft", velocities[0]);
    frc::SmartDashboard::PutNumber("closed loop errror", backLeft.GetClosedLoopError(0));
    frc::SmartDashboard::PutNumber("Setpoint", backLeft.GetClosedLoopTarget(0));

    backLeft.Set(TalonFXControlMode::Velocity, leftThrot);
    frontLeft.Set(TalonFXControlMode::Velocity, leftThrot);
    backRight.Set(TalonFXControlMode::Velocity, rightThrot);
    frontRight.Set(TalonFXControlMode::Velocity, rightThrot);
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

void Drivetrain::setScissorPeakOutput(positionStatus scissor) {
    if (scissor == EXTENDED) {
        backLeft.ConfigPeakOutputForward(.2, 10);
        backLeft.ConfigPeakOutputReverse(-.2, 10);

        backRight.ConfigPeakOutputForward(.2, 10);
        backRight.ConfigPeakOutputReverse(-.2, 10);

        frontLeft.ConfigPeakOutputForward(.2, 10);
        frontLeft.ConfigPeakOutputReverse(-.2, 10);

        frontRight.ConfigPeakOutputForward(.2, 10);
        frontRight.ConfigPeakOutputReverse(-.2, 10);
    }

    else {
        backLeft.ConfigPeakOutputForward(1, 10);
        backLeft.ConfigPeakOutputReverse(-1, 10);

        backRight.ConfigPeakOutputForward(1, 10);
        backRight.ConfigPeakOutputReverse(-1, 10);

        frontLeft.ConfigPeakOutputForward(1, 10);
        frontLeft.ConfigPeakOutputReverse(-1, 10);

        frontRight.ConfigPeakOutputForward(1, 10);
        frontRight.ConfigPeakOutputReverse(-1, 10);
    }
}

void Drivetrain::setBrakeMode(enableStatus status) {
    if (status == ENABLED) {
        backLeft.SetNeutralMode(NeutralMode::Brake);
        frontLeft.SetNeutralMode(NeutralMode::Brake);
        backRight.SetNeutralMode(NeutralMode::Brake);
        frontRight.SetNeutralMode(NeutralMode::Brake);
    }
    else {
        backLeft.SetNeutralMode(NeutralMode::Coast);
        frontLeft.SetNeutralMode(NeutralMode::Coast);
        backRight.SetNeutralMode(NeutralMode::Coast);
        frontRight.SetNeutralMode(NeutralMode::Coast);
    }
}

void Drivetrain::setSlot(int slot) {
    backLeft.SelectProfileSlot(slot, 0);
    backRight.SelectProfileSlot(slot, 0);
    frontLeft.SelectProfileSlot(slot, 0);
    frontRight.SelectProfileSlot(slot, 0);
}

void Drivetrain::configMotor(WPI_TalonFX& falcon) {
    falcon.ConfigSelectedFeedbackSensor(FeedbackDevice::IntegratedSensor, 0, 10);
    falcon.ConfigClosedloopRamp(0, 10);
    falcon.ConfigSupplyCurrentLimit(SupplyCurrentLimitConfiguration(true, 40, 60, 1), 10);
    falcon.SetSelectedSensorPosition(0);
    falcon.Config_kP(0, drive_P, 10);
    falcon.Config_kI(0, drive_I, 10);
    falcon.Config_kD(0, drive_D, 10);
    falcon.Config_kF(0, drive_F, 10);
    falcon.Config_IntegralZone(0, 0, 10);
    falcon.ConfigClosedLoopPeriod(0, 1, 10);
    falcon.ConfigMaxIntegralAccumulator(0, drive_maxIntegralAccum, 10);
    falcon.ConfigAllowableClosedloopError(0, drive_allowableClosedLoopError, 10);
    falcon.SelectProfileSlot(0, 0);

     /*
    * Configure the current limits that will be used
    * Stator Current is the current that passes through the motor stators.
    * Use stator current limits to limit rotor acceleration/heat production
    * Supply Current is the current that passes into the controller from the supply
    * Use supply current limits to prevent breakers from tripping
    * */
}

void Drivetrain::resetEncoderCounts(){
    backLeft.SetSelectedSensorPosition(0, 0, 50);
    backRight.SetSelectedSensorPosition(0, 0, 50);
    frontLeft.SetSelectedSensorPosition(0, 0, 50);
    frontRight.SetSelectedSensorPosition(0, 0, 50);
}

int * Drivetrain::getPositions() {
    positions[0] = backLeft.GetSelectedSensorPosition();
    positions[1] = frontLeft.GetSelectedSensorPosition();
    positions[2] = backRight.GetSelectedSensorPosition();
    positions[3] = frontRight.GetSelectedSensorPosition();

    return positions;
}

int * Drivetrain::getVelocities() {
    velocities[0] = backLeft.GetSelectedSensorVelocity();
    velocities[1] = frontLeft.GetSelectedSensorVelocity();
    velocities[2] = backRight.GetSelectedSensorVelocity();
    velocities[3] = frontRight.GetSelectedSensorVelocity();

    return velocities;
}

double * Drivetrain::getRPMs() {
    rpms[0] = backLeft.GetSelectedSensorVelocity() * velToRPM_FX;
    rpms[1] = frontLeft.GetSelectedSensorVelocity() * velToRPM_FX;
    rpms[2] = backRight.GetSelectedSensorVelocity() * velToRPM_FX;
    rpms[3] = frontRight.GetSelectedSensorVelocity() * velToRPM_FX;

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

    frc::SmartDashboard::PutNumber("Back Left Current Position", positions[0]);
}

//----------------------------------------------------------------Auton---------------------------------------------------------------------------------//

void Drivetrain::autonBaseLine(double  userBackLeft, double forward, double turn) {
    
    if (positions[0] <= backLeftInitialPosition + userBackLeft) {
        leftThrot = turn - forward;
        rightThrot = turn + forward;
        
        backLeft.Set(ControlMode::PercentOutput, leftThrot);
        frontLeft.Set(ControlMode::PercentOutput, leftThrot);
        backRight.Set(ControlMode::PercentOutput, rightThrot);
        frontRight.Set(ControlMode::PercentOutput, rightThrot);

        backLeft.SetNeutralMode(NeutralMode::Brake); 
        backRight.SetNeutralMode(NeutralMode::Brake);
        frontLeft.SetNeutralMode(NeutralMode::Brake); //Use drivetrain function
        frontRight.SetNeutralMode(NeutralMode::Brake);

        frc::Wait(2);

        backLeft.SetNeutralMode(NeutralMode::Coast); 
        backRight.SetNeutralMode(NeutralMode::Coast);
        frontLeft.SetNeutralMode(NeutralMode::Coast);
        frontRight.SetNeutralMode(NeutralMode::Coast); 
    }
    
    else {
        backLeft.Set(ControlMode::PercentOutput, 0);
        frontLeft.Set(ControlMode::PercentOutput, 0);
        backRight.Set(ControlMode::PercentOutput, 0);
        frontRight.Set(ControlMode::PercentOutput, 0);
    }
}
