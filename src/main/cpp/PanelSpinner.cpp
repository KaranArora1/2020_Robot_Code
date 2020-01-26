/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "PanelSpinner.h"

PanelSpinner::PanelSpinner() {

}

void PanelSpinner::SpinRevolutions(double speed) { //Eventually Parameter for speed won't be needed, it will be automatic
    spinner.Set(ControlMode::PercentOutput, speed);
    //Add color sensor code that stops the motor here
}

void PanelSpinner::SpinColor(double speed) {
    
}
