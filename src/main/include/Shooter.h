/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "RobotMap.h"

class Shooter {
 public:
    Shooter();
    void Shoot(double);
    void Intake(double);

  private:
    rev::CANSparkMax intake{1, rev::CANSparkMax::MotorType::kBrushless};
    rev::CANSparkMax shooter{2, rev::CANSparkMax::MotorType::kBrushless};
    
    rev::CANEncoder intakeEncoder = intake.GetEncoder();
    rev::CANEncoder shooterEncoder = shooter.GetEncoder();
};
