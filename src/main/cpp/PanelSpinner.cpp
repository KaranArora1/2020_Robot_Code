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

    /*spinner.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, 10); //Relative or Absolute? 
    spinner.SetSelectedSensorPosition(0);*/
}

void PanelSpinner::deployArm() {

}

void PanelSpinner::spinRevolutions(double speed) { //Eventually Parameter for speed won't be needed, it will be automatic
    spinner.Set(ControlMode::PercentOutput, speed);
    ///Add color sensor code that stops the motor here 
}

void PanelSpinner::spinToColor(double speed) {
   //Field data
    if(gameData.length() > 0){
        switch (gameData[0]){
        case 'R':
        targetColor = "Red";
        break;
        case 'G':
        targetColor = "Green";
        break;
        case 'B':
        targetColor = "Blue";
        break;
        case 'Y':
        targetColor = "Yellow";
        break;
        }
        if(targetColor != colorString){
            spinner.Set(0.40);
            spinStatus = true;
        }
        else {
            spinner.Set(0);
            spinStatus = false;
        }
    }
}

double PanelSpinner::getConfidence() { //Is this fine? 
detectedColor = m_colorSensor.GetColor();
matchedColor = colorSensor.MatchClosestColor(detectedColor, confidence);

return confidence;
}

std::string PanelSpinner::detectColor() {
    detectedColor = m_colorSensor.GetColor();
    matchedColor = colorSensor.MatchClosestColor(detectedColor, confidence);

    if (matchedColor == kBlueTarget && confidence > 0.953) {
            colorString = "Blue";
            std::cout << "Detected Blue" << std::endl;
    }
    else if (matchedColor == kRedTarget){
        colorString = "Red";
        std::cout << "Detected Red" << std::endl;
    }
    else if (matchedColor == kGreenTarget && confidence > 0.953) {
        colorString = "Green";
        std::cout << "Detected Green" << std::endl; 
    }
    else if (matchedColor == kYellowTarget && confidence > 0.953) {
        colorString = "Yellow";
        std::cout << "Detected Yellow" << std::endl; 
    }
    else {
        colorString = "Unknown";
    }

return colorString;

}

int PanelSpinner::getPosition() {
    return spinner.GetSelectedSensorPosition(0);
}

int PanelSpinner::getVelocity() {
    return spinner.GetSelectedSensorVelocity(0);
}

double PanelSpinner::getRPM() {
    return spinner.GetSelectedSensorVelocity(0) * velToRPM_SRX;
}

void PanelSpinner::Printer() {
    std::cout << "Spinner Position " << getPosition() << " counts " << std::endl;
    std::cout << "Spinner Velocity " << getVelocity() << " counts/100ms" << std::endl;
    std::cout << "Spinner RPM " << getRPM() << std::endl;
}

void PanelSpinner::dashboardPrinter() {
    //frc::SmartDashboard::PutNumber("Spinner Position (counts)", getPosition());
    //frc::SmartDashboard::PutNumber("Spinner Velocity (counts/100ms)", getVelocity());
    //frc::SmartDashboard::PutNumber("Spinner RPM", getRPM());
    frc::SmartDashboard::PutNumber("Red", detectedColor.red);
    frc::SmartDashboard::PutNumber("Green", detectedColor.green);
    frc::SmartDashboard::PutNumber("Blue", detectedColor.blue);
    frc::SmartDashboard::PutNumber("Confidence", confidence);
    frc::SmartDashboard::PutString("This is the color", colorString);
}