/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "RobotMap.h"

//Not needed - made by Michael Kaatz. Just a better version of Mitch's MyTimer, but not in use right now

class YourTimer {
 public:
  YourTimer();
  void SetStart();
  double Total();
  void SetDiffStart();
  double Diff(bool);

 private:
  timeval start;
  timeval last;
};
