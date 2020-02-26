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

void Vision::Run(double fwdspeed, double trnspeed, Drivetrain& Drive) {
    nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("pipeline", 2); //Sets pipeline to pipe 0 (the vision one)

    std::shared_ptr<NetworkTable> table = NetworkTable::GetTable("limelight");
    float tv = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tv", 0.0);
    float tx = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tx", 0.0);
    float ty = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tx", 0.0); //Declare all the degree variables
    
    while (tv == 0) {
        Drive.drivePercent(fwdspeed, trnspeed); 
        tv = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tv", 0.0); //Robot spins till it finds a vision target
    }//end of finding


/*
    while (tv != 0.0) {
        Drive.Drive(fwdspeed, 0);
        tx = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tv", 0.0);
        
        if (tx > 0) {
            Drive.Drive(fwdspeed, trnspeed); //Robot turns left till there is no X error 
        }else if (tx < 0) {
            Drive.Drive(fwdspeed * -1, trnspeed * -1); //Robot turns right untill there is no horizontal error
        }//end of x axis seeking
        
        else if (tx == 0) {
            if (ty > 0) {
                //turn up code
            }
            else if ( ty < 0) {
                //turn down code
            }
            else {
                //yay we are perfectly allighned
            }//end of y axis seeking
        }//end of seeking


        //distance equasion goes here



        //start of long if statement for distance / velocity

        /*if (distance =< 16.5){

        }else if(distance =< 16.00){

        }else if(distance =< 15.5){

        }else if(distance =< 15.00){

        }else if(distance =< 14.5){

        }else if(distance =< 14.00){

        }else if(distance =< 13.5){

        }else if(distance =< 13.00){

        }else if(distance =< 12.5){

        }else if(distance =< 12.00){

        }else if(distance =< 11.5){

        }else if(distance =< 11.00){

        }else if(distance =< 10.5){

        }else if(distance =< 10.0){

        }else if(distance =< 16.5){

        }*/




    }
//}



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

void Vision::setupShootHigh(Drivetrain& Drive, Shooter& Shoot) {
    //nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("pipeline", 0); //Sets pipeline to pipe 0 (the vision one)

    switchPipeline();

    std::shared_ptr<NetworkTable> table = NetworkTable::GetTable("limelight");
    float tv = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tv", 0.0);
    float tx = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tx", 0.0);
    float ty = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tx", 0.0); //Declare all the degree variables

    //Shoot.moveWrist(20000); //Something based on ty value (position limelight)

    //calculateDistance();

    Drive.drivePercent(1000, 100); //Something based on tx value (orient robot)
    switchPipeline();
}

void Vision::shootHigh(Shooter& Shoot, Indexer& Index) {
    switchPipeline();

    Shoot.moveWrist(20000); //Orient SHOOTER to actual position it would need to be to make target

    Shoot.Shoot(100000); //Something based on distance away from target, calculateDistance()? 
    Index.Spin(0, 0); //Move Indexer to first position to shoot
    Index.switchPushBall(); 
    Index.feedBall(FEEDER_WHEEL_SPEED);

    // 5 Balls shoot out somehow

    //Turn everything off
    Shoot.moveWrist(0);
    Index.switchPushBall();
    Index.feedBall(0);
    Shoot.Shoot(0);

    switchPipeline();
}

void Vision::shootLow(Drivetrain& Drive, Shooter& Shoot, Indexer& Index) {

}

void Vision::toggleShootHighStatus() {
    if (shootHighStatus == ENABLED) {
        shootHighStatus = DISABLED;
    }
    else {
        shootHighStatus = ENABLED;
    }
}

double Vision::calculateDistance() {
    return 0;
}

void Vision::Printer() {
    std::cout << "Current Limelight Pipeline Number " << nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("getpipe", 0) << std::endl;
     std::cout << "Current Limelight targets " << nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tv", 0.0) << std::endl;
}

void Vision::dashboardPrinter() {
   
    frc::SmartDashboard::PutNumber("Current Limelight Pipeline Number", nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("getpipe", 0));
    frc::SmartDashboard::PutNumber("Current Limelight targets",  nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tv", 0.0));
}

