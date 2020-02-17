/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Vision.h"
#include "math.h"

Vision::Vision() {

}
 
 /*
  Also look at the following option:
  "stream" Sets limelight’s streaming mode
  0 Standard - Side-by-side streams if a webcam is attached to Limelight
  1 PiP Main - The secondary camera stream is placed in the lower-right corner of the primary camera stream
  2 PiP Secondary - The primary camera stream is placed in the lower-right corner of the secondary camera stream
 */

void Vision::switchPipeline() {
    if (nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("getpipe", 0) == 0) { 
        nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("pipeline", 1);
        }
    else {
        nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("pipeline", 0);
        }
}

void Run(double fwdspeed, double trnspeed, Drivetrain Drive) {
    nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("pipeline", 0); //Sets pipeline to pipe 0 (the vision one)

    std::shared_ptr<NetworkTable> table = NetworkTable::GetTable("limelight");
    float tv = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tv", 0.0);
    float tx = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tx", 0.0);
    float ty = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tx", 0.0); //Declare all the degree variables

    while (tv == 0.0f) {
        Drive.Drive(fwdspeed, trnspeed); //Maybe delete Drivetrain::Drive and just make it Drive since that worked for Arshia
        tv = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tv", 0.0); //Robot spins till it finds a vision target
    }

    while (tv != 0.0) {
        Drive.Drive(fwdspeed, 0);
        tx = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tv", 0.0);
        
        if (tx > 0) {
            Drive.Drive(fwdspeed, trnspeed); //Robot turns left till there is no X error 
        }
        
        else if (tx < 0) {
            Drive.Drive(fwdspeed * -1, trnspeed * -1); //Robot turns right untill there is no horizontal error
        }
        
        else if (tx == 0) {
            if (ty > 0) {
                //turn up code
                
            }
            else if ( ty < 0) {
                //turn down code
            }
            else {
                //yay we are perfectly allighned
            }
        }
    }
}
  // h

//Math goes here
//re ajusting goes here
//shoot method goes here
//storage system eject method goes here

//power port height h1= 91 in
//robot shooter height h2=  10in 
//the angle from 0 - 90 

//put a method here that takes the shooters encoder counts and converts them into degrees 0-90 and have it equal to shooterAng
/*shooterang = 45;
distance = (91 - 10)/tan(shooterang);


if (distance <= 5.3){
    //shoot at 24 
}

//shoot method goes here

//storage system eject method goes here

}*/

void Vision::Shoot(Drivetrain Drive, Shooter Shoot, Indexer Index) {
    nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("pipeline", 0); //Sets pipeline to pipe 0 (the vision one)

    std::shared_ptr<NetworkTable> table = NetworkTable::GetTable("limelight");
    float tv = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tv", 0.0);
    float tx = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tx", 0.0);
    float ty = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tx", 0.0); //Declare all the degree variables

    while (tv == 0.0f) {
        //Drive.Drive(fwdspeed, trnspeed); //Maybe delete Drivetrain::Drive and just make it Drive since that worked for Arshia
        tv = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tv", 0.0); //Robot spins till it finds a vision target
    }

    calculateDistance();
    Shoot.moveWrist(20000); //Something based on ty value
    Drive.Drive(1000, 100); //Something based on tx value

    Shoot.Shoot(100000); //Something based on distance away from target
    Index.feedBall(10000);
    Index.pushBall(); 
    Index.Spin(.13, .13);

    // Balls shoot out

    //Turn everything off
    Index.pushBall();
    Index.feedBall(0);
    Shoot.Shoot(0);
}

double Vision::calculateDistance() {
    return 0;
}

void Vision::Printer() {
    std::cout << "Current Limelight Pipeline Number " << nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("getpipe", 0) << std::endl;
}

void Vision::dashboardPrinter() {
    frc::SmartDashboard::PutNumber("Current Limelight Pipeline Number", nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("getpipe", 0));
}

