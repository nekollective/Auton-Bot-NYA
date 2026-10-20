#include "robotConfig.h"
#include "main.h"
#include "api.h"

void testAuton() {
    chassis.setPose(0, 0, 0);

    chassis.moveToPoint(0, 24, 127, {.maxSpeed = 127});

    chassis.turnToHeading(90, 127, {.maxSpeed = 127});

    chassis.swingToHeading(45, lemlib::DriveSide::RIGHT, 750, {.maxSpeed = 127});
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

// Auto for Red Near Side / In four parts, will adjust according to results.
void redNear() {
    chassis.setPose(0, 0, 0);
    chassis.moveToPoint(10.7, 22.8, 2000, {.maxSpeed = 100});
    chassis.waitUntilDone();
    chassis.moveToPoint(10.7, 46.5, 2000, {.maxSpeed = 100});
    chassis.waitUntilDone();
    chassis.moveToPoint(10.7, 22.8, 2000, {.forwards = false, .maxSpeed = 100});
    chassis.waitUntilDone();
    chassis.moveToPoint(34.3, 22.8, 2000, {.maxSpeed = 100});
    chassis.waitUntilDone();
    chassis.moveToPoint(10.7, 22.8, 2000, {.forwards = false, .maxSpeed = 100});
    chassis.waitUntilDone();
    chassis.moveToPoint(41.1, 8.0, 2500, {.maxSpeed = 100});
    chassis.waitUntilDone();
}


void redFar(){

}

void blueNear(){

}

void blueFar(){

}

void skills(){

}

