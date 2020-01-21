/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Drivetrain.h"

Drivetrain::Drivetrain() {

     //Use Phoenix Tuner to test encoders, maybe use IntegratedSensor or Encoder Class, CTRE_MagEncoder_Relative
    /*back_left.ConfigSelectedFeedbackSensor(FeedbackDevice::IntegratedSensor, 0, 10);
    back_right.ConfigSelectedFeedbackSensor(FeedbackDevice::IntegratedSensor, 0, 10);
    front_left.ConfigSelectedFeedbackSensor(FeedbackDevice::IntegratedSensor, 0, 10);
    front_right.ConfigSelectedFeedbackSensor(FeedbackDevice::IntegratedSensor, 0, 10);*/

    back_left.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, 10);
    back_right.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, 10);
    front_left.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, 10);
    front_right.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, 10);
  
    front_right.SetSelectedSensorPosition(0);
    back_right.SetSelectedSensorPosition(0);
    front_left.SetSelectedSensorPosition(0);
    back_left.SetSelectedSensorPosition(0);

}

void Drivetrain::Drive(double forward, double turn) {
    
    leftThrot = turn - forward;
    rightThrot = turn + forward;
    
    back_left.Set(ControlMode::PercentOutput, leftThrot);
    front_left.Set(ControlMode::PercentOutput, leftThrot);
    back_right.Set(ControlMode::PercentOutput, rightThrot);
    front_right.Set(ControlMode::PercentOutput, rightThrot);

    std::cout << "Back left:";
    std::cout << back_left.GetSelectedSensorPosition(0) << std::endl;

    std::cout << "Front left:";
    std::cout << front_left.GetSelectedSensorPosition(0) << std::endl;

    std::cout << "Back right:";
    std::cout << back_right.GetSelectedSensorPosition(0) << std::endl;

    std::cout << "Front right:";
    std::cout << front_right.GetSelectedSensorPosition(0) << std::endl;
}
