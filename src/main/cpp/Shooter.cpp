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
    std::cout << "Shooter (CAN ID 1) " << shooterEncoder.GetVelocity() << " RPM" << std::endl;
    std::cout << "Slave Shooter (CAN ID 2) " << slaveShooterEncoder.GetVelocity() << " RPM" << std::endl;
}

void Shooter::DashboardPrinter() {
    
}