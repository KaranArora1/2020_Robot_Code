/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "PanelSpinner.h"

//Add thing to count number of times wheel has spun to confirm that color is correct 

PanelSpinner::PanelSpinner() {
    colorSensor.AddColorMatch(kBlueTarget); //Color Sensor Stuff
    colorSensor.AddColorMatch(kGreenTarget);
    colorSensor.AddColorMatch(kRedTarget);
    colorSensor.AddColorMatch(kYellowTarget);
}

void PanelSpinner::SpinRevolutions(double speed) { //Eventually Parameter for speed won't be needed, it will be automatic
    spinner.Set(ControlMode::PercentOutput, speed);
    ///Add color sensor code that stops the motor here charliewas here
}

void PanelSpinner::SpinToColor(double speed) {
    
}

std::string PanelSpinner::DetectColor() {
	detectedColor = m_colorSensor.GetColor();
	matchedColor = colorSensor.MatchClosestColor(detectedColor, confidence);
	
    if (matchedColor == kBlueTarget) {
            colorString = "Blue";
            std::cout << "Detected Blue" << std::endl;
        }
    else if (matchedColor == kRedTarget){
        colorString = "Red";
        std::cout << "Detected Red" << std::endl;
        }
    else if (matchedColor == kGreenTarget) {
        colorString = "Green";
        std::cout << "Detected Green" << std::endl; 
        }
    else if (matchedColor == kYellowTarget) {
        colorString = "Yellow";
        std::cout << "Detected Yellow" << std::endl; 
        }
    else {
        colorString = "Unknown";
        }

    frc::SmartDashboard::PutNumber("Red", detectedColor.red);
    frc::SmartDashboard::PutNumber("Green", detectedColor.green);
    frc::SmartDashboard::PutNumber("Blue", detectedColor.blue);
    frc::SmartDashboard::PutNumber("Confidence", confidence);
    frc::SmartDashboard::PutString("This is the color", colorString);

    return colorString;
}

