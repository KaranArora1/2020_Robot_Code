/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Climber.h"

Climber::Climber() {
    winch.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Absolute, 0, 10); 
    winch.SetSelectedSensorPosition(0); 

    winch.Config_kP(0, winch_P, 10);
    winch.Config_kI(0, winch_I, 10);
    winch.Config_kD(0, winch_D, 10);

    winch.SetSensorPhase(true);
    winch.SetInverted(false);

    winch.ConfigPeakOutputForward(0.5, 10);
    winch.ConfigPeakOutputReverse(-0.5, 10);
}

//Spins winch using Joystick, eventually will be position control with no parameters to the encoder position target
void Climber::Climb(double speed) { 
    winch.Set(ControlMode::PercentOutput, speed);
}

void Climber::climbToPos() {
    winch.Set(ControlMode::Position, winchPos);
}

//Activate scissor lift - sets gear to one for Drivetrain for safety and limits peak output
void Climber::scissorLift(Drivetrain& Drive) { 
    if (scissor.Get() == frc::DoubleSolenoid::Value::kForward) {
		scissor.Set(frc::DoubleSolenoid::Value::kReverse); //Which one means that it actually goes up? assuming its kForward
        scissorLiftStatus = RETRACTED;
        hookIsOn = true;
        //toggleScissorCanBeDeployedStatus(); //Automatically makes scissorCanBeDeployed back to disabled once it is retracted
	}
    else {
		scissor.Set(frc::DoubleSolenoid::Value::kForward);
        scissorLiftStatus = EXTENDED;
        Drive.setGear(1);
        hookIsOn = false;
	}

    Drive.setScissorPeakOutput(scissorLiftStatus);
}

void Climber::toggleScissorCanBeDeployedStatus() {
    if (scissorCanBeDeployedStatus == ENABLED) {
        scissorCanBeDeployedStatus = DISABLED;
    }
    else {
        scissorCanBeDeployedStatus = ENABLED;
    }
}

int Climber::getWinchPosition() {
    return winch.GetSelectedSensorPosition(0);
}

void Climber::Printer() {
    std::cout << "Winch Position " << getWinchPosition() << " counts" << std::endl;
    std::cout << "Scissor Climb Can Be Deployed Status " << ((scissorCanBeDeployedStatus == ENABLED) ? "ENABLED" : "DISABLED") << std::endl;
    std::cout << "Scissor Climb Deployed " << ((scissorLiftStatus == EXTENDED) ? "EXTENDED" : "RETRACTED") << std::endl;
}

void Climber::dashboardPrinter() {
    frc::SmartDashboard::PutNumber("Winch Position (counts)", getWinchPosition());
    frc::SmartDashboard::PutString("Scissor Climb Can Be Deployed Status", (scissorCanBeDeployedStatus == ENABLED) ? "ENABLED" : "DISABLED"); 
    frc::SmartDashboard::PutString("Scissor Climb Deployed", (scissorLiftStatus == EXTENDED) ? "EXTENDED" : "RETRACTED");
    frc::SmartDashboard::PutBoolean("Hook is On", hookIsOn);
}
