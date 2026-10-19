#ifndef _PROS_ROBOT_CONFIG_H_
#define _PROS_ROBOT_CONFIG_H_

#include "pros/motor_group.hpp"
#include "lemlib/api.hpp"

extern pros::Motor L1;
extern pros::Motor L2;
extern pros::Motor L3;
extern pros::Motor R1;
extern pros::Motor R2;
extern pros::Motor R3;

//DRIVETRAIN
extern pros::MotorGroup left_motor_group;
extern pros::MotorGroup right_motor_group;
extern lemlib::Chassis chassis;
extern lemlib::Drivetrain drivetrain;

//MOTORS
extern pros::Motor Cascade;
extern pros::Motor Intake;

// SENSORS
extern pros::Imu imu;
extern pros::Rotation horizontal_encoder;
extern pros::Rotation vertical_encoder;
extern lemlib::TrackingWheel horizontal_tracking_wheel;
extern lemlib::TrackingWheel vertical_tracking_wheel;
extern lemlib::OdomSensors sensors;

//PISTONS
extern pros::adi::Pneumatics KlemToggle1;
extern pros::adi::Pneumatics KlemToggle2;

#endif // _PROS_ROBOT_CONFIG_H_
