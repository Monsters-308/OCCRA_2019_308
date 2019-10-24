#pragma config(Sensor, dgtl1,  bottomStage,    sensorDigitalIn)
#pragma config(Sensor, dgtl2,  midStage,       sensorDigitalIn)
#pragma config(Sensor, dgtl3,  topStage,       sensorDigitalIn)
#pragma config(Sensor, dgtl5,  bumpLeft,       sensorDigitalIn)
#pragma config(Sensor, dgtl7,  clamp,          sensorDigitalOut)
#pragma config(Sensor, dgtl10, bumpRight,      sensorDigitalIn)
#pragma config(Sensor, dgtl11, pusher,         sensorDigitalOut)
#pragma config(Motor,  port2,           frontLeftMotor, tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port3,           backLeftMotor, tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port4,           frontRightMotor, tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Motor,  port5,           backRightMotor, tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Motor,  port6,           elevatorMotor, tmotorServoContinuousRotation, openLoop, reversed)
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description: Competition template for VEX EDR                      */
/*                                                                           */
/*---------------------------------------------------------------------------*/

// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton()
{
  // Set bStopTasksBetweenModes to false if you want to keep user created tasks
  // running between Autonomous and Driver controlled modes. You will need to
  // manage all user created tasks if set to false.
  bStopTasksBetweenModes = true;

	// Set bDisplayCompetitionStatusOnLcd to false if you don't want the LCD
	// used by the competition include file, for example, you might want
	// to display your team name on the LCD in this function.
	// bDisplayCompetitionStatusOnLcd = false;

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

task autonomous()
{
  // ..........................................................................
  // Insert user code here.
  // ..........................................................................

  // Remove this function call once you have "real" code.
  AutonomousCodePlaceholderForTesting();
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

task usercontrol()
{
  // User control code here, inside the loop

  while (true)
  {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    // Remove this function call once you have "real" code.
    	int topSpeedPercent = 40;
	int topSpeedTurnPercent = 20;
	SensorValue[pusher] = 0;
	SensorValue[clamp] = 0;
	int push_loop_count = 0;
	bool push_active = false;
	while(1 == 1)
  {
  	//Cubic
  	//For arcade drive
  	//int rightStickCubed = vexRT[Ch1]*vexRT[Ch1]*vexRT[Ch1]/16129;

  	//For tank drive
  	//int rightStickCubed = vexRT[Ch2]*vexRT[Ch2]*vexRT[Ch2]/16129;

  	//int leftStickCubed = vexRT[Ch3]*vexRT[Ch3]*vexRT[Ch3]/16129;
		//Linear
   	int rightStickCubed = vexRT[Ch1];
  	int leftStickCubed = vexRT[Ch3];

  	if(vexRT[Btn5U]){
  		topSpeedPercent = 60;
  		topSpeedTurnPercent = 30;
  	}else{
  		topSpeedPercent = 40;
  		topSpeedTurnPercent = 20;
	  }

  	rightStickCubed = (rightStickCubed * topSpeedTurnPercent)/100;
  	leftStickCubed = (leftStickCubed * topSpeedPercent)/100;
  /* Tank Drive
  	//Right side of the robot is controlled by the right joystick, Y-axis
    motor[frontRightMotor] = vexRT[Ch2];
    motor[backRightMotor]  = vexRT[Ch2];
    //Left side of the robot is controlled by the left joystick, Y-axis
    motor[frontLeftMotor] = vexRT[Ch3];
    motor[backLeftMotor]  = vexRT[Ch3];
   */

   //Arcade drive
    motor[frontLeftMotor]  = leftStickCubed + rightStickCubed;
    motor[frontRightMotor] = leftStickCubed - rightStickCubed;
    motor[backLeftMotor]  = leftStickCubed + rightStickCubed;
    motor[backRightMotor] = leftStickCubed - rightStickCubed;

/*
    if(vexRT[Btn5U]){
    	motor[elevatorMotor] = 63;
    }else if(vexRT[Btn5D]){
    	motor[elevatorMotor] = -63;
    }else{
    	motor[elevatorMotor] = 0;
	  }
*/
		//elevator
    if(vexRT[Btn5UXmtr2] && SensorValue[topStage] == 0){
    	motor[elevatorMotor] = 63;
    }else if(vexRT[Btn5DXmtr2] && SensorValue[bottomStage] == 0){
    	motor[elevatorMotor] = -63;
    }else{
    	motor[elevatorMotor] = 0;
	  }
		//The arm
	  if(vexRT[Btn6UXmtr2]  || vexRT[Btn8RXmtr2]){
	  	SensorValue[clamp] = 1;
		}else if(vexRT[Btn6DXmtr2] || ((SensorValue[bumpLeft] == 0) && (SensorValue[bumpRight] == 0))){
			SensorValue[clamp] = 0;
		}

		//The thing to push the cube and opens clamp
		if(vexRT[Btn8UXmtr2]){
	  	SensorValue[pusher] = 1;
		}
		else if(vexRT[Btn8DXmtr2]  || vexRT[Btn8RXmtr2]){
			SensorValue[pusher] = 0;
		}

		if(vexRT[Btn8RXmtr2]){
			push_active = true;
		  push_loop_count =20000;
		}

		if(push_active){
			if(push_loop_count == 0){
				SensorValue[pusher] = 1;
				push_active = false;
			}else{
				push_loop_count--;
			}
		}
	}
}
}
