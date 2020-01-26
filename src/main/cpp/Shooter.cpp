/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Shooter.h"

Shooter::Shooter() {
  
}

void Shooter::Shoot(double input) {
    shooter.Set(input);
    std::cout << shooterEncoder.GetVelocity() << std::endl;
}

void Shooter::Intake(double input) {
    //intake.Set(input);
    //std::cout << intakeEncoder.GetVelocity() << std::endl;
}

void Shooter::moveWrist(double input) {

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
