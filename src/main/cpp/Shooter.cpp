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
    wrist.ConfigPeakOutputReverse(-.25);

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
void Shooter::ShootRPMs(double speed) { 
    currentRPM = speed; //Keep?

    shooterPID.SetReference(speed, rev::ControlType::kVelocity);
    slaveShooterPID.SetReference(speed, rev::ControlType::kVelocity);
}

//Shoot at a pre-set speed determined by plannedRPM, gotten from the speeds[] array
void Shooter::ShootFixedRPMS() { 

    if (shootOverrideStatus == DISABLED) {
        //Each time button is pressed, it switches between enabled and disabled 
        if (shooterStatus == ENABLED) {
            shooterStatus = DISABLED;
            currentRPM = 0;
        }
    
        else {
            shooterStatus = ENABLED;
            currentRPM = plannedRPM;
        }

        shooterPID.SetReference(currentRPM, rev::ControlType::kVelocity); //Later change this to ShootRPMs
        slaveShooterPID.SetReference(currentRPM, rev::ControlType::kVelocity);
    }
}

void Shooter::shootOverride() {

    if (shooterStatus == DISABLED) {
        if (shootOverrideStatus == ENABLED) {
            shootOverrideStatus = DISABLED;
            currentRPM = 0;
        }

        else {
            shootOverrideStatus = ENABLED;
            currentRPM = -250;
        }
        
        shooterPID.SetReference(currentRPM, rev::ControlType::kVelocity);
        slaveShooterPID.SetReference(currentRPM, rev::ControlType::kVelocity); //Later change this to ShootRPMs
    }
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
        if (currentSpeedPos == 10) {
            currentSpeedPos = 9;
        }
    }
    else {
        currentSpeedPos--;
        if (currentSpeedPos == -1) {
            currentSpeedPos = 9;
        }
    }

    plannedRPM = speeds[currentSpeedPos];
    
    //If speed is incremented while shooter is enabled change it to that speed
    if (shooterStatus == ENABLED) {
        currentRPM = plannedRPM;

        shooterPID.SetReference(currentRPM, rev::ControlType::kVelocity);
        slaveShooterPID.SetReference(currentRPM, rev::ControlType::kVelocity);
    }
}

//Move wrist up or down using array of positions
void Shooter::moveWristFixedPositions(direction dir) { 
    if (dir == UP) {
        currentWristPos++;
        if (currentWristPos == 8) {
            currentWristPos = 7;
        }
    }
    else {
        currentWristPos--;
        if (currentWristPos == -1) {
            currentWristPos = 0;
        }
    }

    wrist.Set(ControlMode::Position, wristPosList[currentWristPos]);
}

void Shooter::shootSolution(direction dir) {
    if (dir == UP) {
        currentWristPos++;
        currentSpeedPos++;

        if (currentWristPos == 5) {
            currentWristPos = 4;
        }
        if (currentSpeedPos == 5) {
            currentSpeedPos = 4;
        } 
    }

    else {
        currentSpeedPos--;
        currentWristPos--;

        if (currentWristPos == -1) {
            currentWristPos = 0;
        }
        if (currentSpeedPos == -1) {
            currentSpeedPos = 0;
        }
    }

    wrist.Set(ControlMode::Position, wristPosList[currentWristPos]);
    
    plannedRPM = speeds[currentSpeedPos];

    if (shooterStatus == ENABLED) {
        currentRPM = plannedRPM;

        shooterPID.SetReference(currentRPM, rev::ControlType::kVelocity);
        slaveShooterPID.SetReference(currentRPM, rev::ControlType::kVelocity);
    }
}

//Move wrist to a position determined by the Limelight
void Shooter::moveWristToPosition(int pos) { 
    wrist.Set(ControlMode::Position, pos);
}

void Shooter::toggleWristOverride()  {
    if (wristOverrideStatus == ENABLED) {
        wristOverrideStatus = DISABLED;
    }
    else {
        wristOverrideStatus = ENABLED;
    }
}

void Shooter::moveWrist(double speed) {
    wrist.Set(ControlMode::PercentOutput, speed);
}

//Returns if switch is depressed
bool Shooter::checkLimitSwitch() { //Is there a better way to update encoder counts? //WHEN SWITCH IS PRESSED GET() is FALSE
    if (!(wristSwitch.Get())) { 
        if (currentWristPos == 0 || wristOverrideStatus == ENABLED) {
            moveWrist(0); //Used to not be there
            wrist.SetSelectedSensorPosition(0);
            currentWristPos = 0; //Used to not be here
            currentSpeedPos = 0; //Fix?

            if (wristOverrideStatus == ENABLED) {
                wristOverrideStatus = DISABLED; //Used to not be here
            }

            return true;
        }
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

    frc::SmartDashboard::PutNumber("Difference Between Target and Actual", shooterEncoder.GetVelocity() - currentRPM);
    frc::SmartDashboard::PutNumber("Shooter (CAN ID 1) RPM", rpms[0]);
    frc::SmartDashboard::PutNumber("Slave Shooter (CAN ID 2) RPM", rpms[1]);
    frc::SmartDashboard::PutNumber("Wrist Position (counts)", getWristPosition());
    //frc::SmartDashboard::PutNumber("Actual Wrist Position (counts)", getWristPosition());
    frc::SmartDashboard::PutNumber("Target RPM", plannedRPM);
    frc::SmartDashboard::PutNumber("Wrist Position (0-4)", currentWristPos);
    frc::SmartDashboard::PutString("Wrist Override", (wristOverrideStatus == ENABLED) ? "ENABLED" : "DISABLED");
    frc::SmartDashboard::PutNumber("Wrist Targeted Position", wristPosList[currentWristPos]);
    frc::SmartDashboard::PutString("Shooter Enabled", (shooterStatus == ENABLED) ? "ENABLED" : "DISABLED");
    frc::SmartDashboard::PutBoolean("Shooter Switch Get()", wristSwitch.Get());
    frc::SmartDashboard::PutString("Shooter Override", (shootOverrideStatus == ENABLED) ? "ENABLED" : "DISABLED");

    //frc::SmartDashboard::PutString("Wrist Override Enabled", (wristOverrideStatus == ENABLED) ? "ENABLED" : "DISABLED");
    //frc::SmartDashboard::PutString("Shooter Override Enabled", (shootOverrideStatus == ENABLED) ? "ENABLED" : "DISABLED");
}

void Shooter::unJamBall(){
    getRPMs(); 

    if (currentRPM > 1000 && rpms[0] < 500 || rpms[1] < 500 ) {
        
        shooterLoopTime += 1;
        shooterRealTime = (shooterLoopTime * 40) / 1000;
      
        if (shooterRealTime > 2) {
            if (shooterRealTime < 4) {
                shooterPID.SetReference(-250, rev::ControlType::kVelocity);
                slaveShooterPID.SetReference(-250, rev::ControlType::kVelocity);

                shooterRealTime = 0;
            }
        }
    }

    else {
        shooterRealTime = 0;
    }
}