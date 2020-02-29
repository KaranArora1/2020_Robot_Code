/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Shooter.h"

Shooter::Shooter() {
    slaveShooter.SetInverted(false);
    shooter.SetInverted(true);

    //wrist.SetInverted(true); - Demo Bot
    wrist.SetInverted(false);
    wrist.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Absolute, 0, 10);
    wrist.SetSensorPhase(true);
    wrist.SetSelectedSensorPosition(0);

    wrist.ConfigPeakOutputForward(.85);
    wrist.ConfigPeakOutputReverse(-.85);

    wrist.ConfigAllowableClosedloopError(0, 20, 10);

    //wrist.ConfigForwardSoftLimitThreshold(80 * 11.4); //Is this right direction? //80 degrees * 11.4 encoder counts per degree
    //wrist.ConfigReverseSoftLimitThreshold(0);
    wrist.ConfigForwardSoftLimitEnable(false);
    wrist.ConfigReverseSoftLimitEnable(false);

    wrist.Config_kP(0, wrist_P, 10);
    wrist.Config_kI(0, wrist_I, 10);
    wrist.Config_kI(0, wrist_D, 10);
    wrist.ConfigMaxIntegralAccumulator(0, wrist_maxIntegralAccum, 10);

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
}

//Will be used with Vision most likely
void Shooter::Shoot(double speed) { 
    shooter.Set(speed);
    slaveShooter.Set(speed);
    /*if (shooter.GetOutputCurrent() > 45) { //FIX CURRENT VALUE
        ballsShot++;
    }*/
}

//Shoot at a pre-set speed
void Shooter::ShootRPMs() { 

    //Each time button is pressed, it switches between enabled and disabled 
    if (shooterEnabled == ENABLED) {
        shooterEnabled = DISABLED;
        currentRPM = 0;
    }
  
    else {
        shooterEnabled = ENABLED;
        currentRPM = plannedRPM;
    }

    shooterPID.SetReference(currentRPM, rev::ControlType::kVelocity);
    slaveShooterPID.SetReference(currentRPM, rev::ControlType::kVelocity);
}

//Overloaded method - increments desired RPM but a pre-set value
void Shooter::incSpeed(int rpm) { 
    
    plannedRPM += rpm;

    if (plannedRPM > 6000) {
        plannedRPM = 0;
    }
    else if (plannedRPM < 0) {
        plannedRPM = SHOOTER_MAX_RPM;
    }
    else if (plannedRPM > 5000) {
        plannedRPM = SHOOTER_MAX_RPM;
    } 
}

//Overloaded method - can increment and decrement RPM and uses array to do so
void Shooter::incSpeed(direction dir) { 
    if (dir == UP) {
        currentSpeedPos++;
        if (currentSpeedPos == 7) {
            currentSpeedPos = 0;
        }
    }
    else {
        currentSpeedPos--;
        if (currentSpeedPos == -1) {
            currentSpeedPos = 6;
        }
    }

    plannedRPM = speeds[currentSpeedPos];
}

//Move wrist up or down using array of positions
void Shooter::moveWristFixedPositions(direction dir) { 
    if (dir == UP) {
        currentWristPos++;
        if (currentWristPos == 6) {
            currentWristPos = 0;
        }
    }
    else {
        currentWristPos--;
        if (currentWristPos == -1) {
            currentWristPos = 5;
        }
    }

    wrist.Set(ControlMode::Position, wristPosList[currentWristPos]);
}

//Use joystick to move the Wrist
void Shooter::moveWrist(double input) { 
    wrist.Set(ControlMode::PercentOutput, input);
}

//Move wrist to a position determined by the Limelight
void Shooter::moveWristToPosition(int pos) { 

}

//Used to override wrist and move it down forcibly
void Shooter::moveWristDownOverride() {
    wrist.Set(ControlMode::PercentOutput, -.15);
}

void Shooter::toggleWristOverride()  {
    if (wristOverride == ENABLED) {
        wristOverride = DISABLED;
    }
    else {
        wristOverride = ENABLED;
    }
}

//Returns if switch is depressed
bool Shooter::checkLimitSwitch() { //Is there a better way to update encoder counts?
    if (!(wristSwitch.Get())) {
        wrist.SetSelectedSensorPosition(0); 
        return true;
    }
    return false;
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
    std::cout << "Target RPM: " << plannedRPM << std::endl;
}

void Shooter::dashboardPrinter() {
    getRPMs();

    frc::SmartDashboard::PutNumber("Difference Between Target and Actual", fabs(currentRPM - shooterEncoder.GetVelocity()));
    frc::SmartDashboard::PutNumber("Shooter (CAN ID 1) RPM", rpms[0]);
    frc::SmartDashboard::PutNumber("Slave Shooter (CAN ID 2) RPM", rpms[1]);
    frc::SmartDashboard::PutNumber("Wrist Position (counts)", getWristPosition());
    frc::SmartDashboard::PutNumber("Target RPM", plannedRPM);
    frc::SmartDashboard::PutNumber("Balls Shot", ballsShot);
    frc::SmartDashboard::PutNumber("Wrist Position (0-5)", currentWristPos);
    frc::SmartDashboard::PutBoolean("Shooter Switch Open", checkLimitSwitch());
    frc::SmartDashboard::PutString("", "");
    frc::SmartDashboard::PutString("", "");
}