/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Us                                                        */
/*    Created:      Thu Oct 21 2021                                           */
/*    Description:  Competition                                               */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Expander1            triport       1 
// Motor393A            motor29       1A               
// Motor393B            motor29       1B               
// Motor393C            motor29       1C               
// Motor393D            motor29       1D               
// Motor393E            motor29       1E               
// Motor393F            motor29       1F
// Motor393G            motor29       1G
// Relay12V             Relay         A               
// Controller1          controller     
// Controller2          controller       
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  int turbo=1;

  vex::color c1=vex::color(255,255,255);
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................
    turbo=1;
    int lspeed=Controller1.Axis3.position(percent)/2;
    int rspeed=Controller1.Axis2.position(percent)*-1/2;

    if(abs(lspeed)<5){
      lspeed=0;
    }
    if(abs(rspeed)<5){
      rspeed=0;
    }

    if(Controller1.ButtonR1.pressing()){
        turbo=2;
    }
    
    if(Controller1.ButtonL2.pressing()){
      Motor393A.state(50,percent);
      Motor393B.state(50,percent);
      Motor393C.state(-50,percent);
      Motor393D.state(-50,percent);
    }else if(Controller1.ButtonR2.pressing()){
      Motor393A.state(-50,percent);
      Motor393B.state(-50,percent);
      Motor393C.state(50,percent);
      Motor393D.state(50,percent);
    }else{
      lspeed=lspeed*turbo;
      rspeed=rspeed*turbo;
      Motor393A.state(lspeed, percent);
      Motor393B.state(lspeed, percent);
      Motor393C.state(rspeed, percent);
      Motor393D.state(rspeed, percent);
    }
    
    if(Controller2.ButtonA.pressing()){
      Motor393E.state(65,percent);
      Motor393F.state(55,percent);
    }
    else if(Controller2.ButtonY.pressing()){
      Motor393E.state(-25,percent);
      Motor393F.state(-25,percent);
    }
    else{
      Motor393E.state(0,percent);
      Motor393F.state(0,percent);
    }

    if(Controller2.ButtonB.pressing()){
      Motor393G.state(-65,percent);
    }
    else{
      Motor393G.state(0,percent);
    }

    Relay12V.set(Controller2.ButtonR1.pressing());

    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1,1);
    Brain.Screen.setPenColor(c1);
    Brain.Screen.print(Controller1.Axis3.position(percent));
    Brain.Screen.print(":");
    Brain.Screen.print(Controller1.Axis2.position(percent));
    Brain.Screen.print("    Battery : ");
    Brain.Screen.print(Brain.Battery.capacity());
    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
