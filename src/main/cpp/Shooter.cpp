/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Shooter.h"

Shooter::Shooter() {
    slaveShooter.SetInverted(true);
}

void Shooter::Shoot(double speed) {
    shooter.Set(speed);
    slaveShooter.Set(speed);
    Printer();
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

void Shooter::Printer() {
    /*std::cout << "Back left:" << std::endl;
    std::cout << backLeft.GetSelectedSensorPosition(0) << " counts" << std::endl;
    std::cout << backLeft.GetSelectedSensorVelocity(0) << " counts/100ms" << std::endl;
    std::cout << std::endl;
    std::cout << shooterEncoder.GetVelocity() << std::endl;
    std::cout << slaveShooterEncoder.GetVelocity() << std::endl;*/
}

