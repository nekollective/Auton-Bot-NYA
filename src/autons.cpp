#include "robotConfig.h"
#include "main.h"
#include "api.h"

void testAuton() {
    //chassis.setPose(0, 0, 0);

    //chassis.moveToPoint(0, 24, 10000, {.maxSpeed = 60});

    //chassis.turnToHeading(90, 10000);

    //chassis.turnToHeading(90, 127, {.maxSpeed = 127});

    //chassis.swingToHeading(45, lemlib::DriveSide::RIGHT, 750, {.maxSpeed = 127
}

void printTemp() {
    while (true) {
    pros::lcd::print(0, "L1: %f", pros::c::motor_get_temperature(1));
    pros::lcd::print(1, "L2: %f", pros::c::motor_get_temperature(2));
    pros::lcd::print(2, "L3: %f", pros::c::motor_get_temperature(3));
    pros::lcd::print(3, "R1: %f", pros::c::motor_get_temperature(4));
    pros::lcd::print(4, "R2: %f", pros::c::motor_get_temperature(5));
    pros::lcd::print(5, "R3: %f", pros::c::motor_get_temperature(6));

    pros::delay(500);
    }
}

void redNear() {
  chassis.setPose(0, 0, 0);
 
  // ---- 1: hit the yellow bar twice (the robot starts with its front against the bar) ----
  /*for (int i = 0; i < 2; i++) {
    chassis.tank(-90, -90, true);  // back off from the bar
    pros::delay(250);
    chassis.tank(127, 127, true);  // ram it at full power
    pros::delay(450);*/

  chassis.tank(0, 0, true);
  chassis.setPose(0, 0, 0);  // pressed against the bar again = back at the start, so fix the odometry
 
  // ---- 2: to the red goal ----
  chassis.moveToPose(-11.4, -9.9, -131, 2000);
  chassis.waitUntilDone();
  // (place a piece here later)
 
  // ---- 3: to the yellow peg on the right, then back to the goal ----
  chassis.moveToPose(-15.8, -31.0, -168, 2000);
  chassis.waitUntilDone();
  // (pick up a piece here later)
 
  chassis.moveToPose(-16.6, -22.9, -6, 2000);
  chassis.waitUntilDone();
  // (place a piece here later)
 
  // ---- 4: to the yellow peg below, then back to the goal ----
  chassis.moveToPose(-33.4, -17.5, -72, 2000);
  chassis.waitUntilDone();
  // (pick up a piece here later)
 
  chassis.moveToPose(-25.1, -16.3, 82, 2000);
  chassis.waitUntilDone();
  // (place a piece here later)
 
  // ---- 5: to the red zone in the bottom-left corner ----
  chassis.moveToPose(-48.0, -1.0, -56, 2000);
  chassis.waitUntilDone();
}