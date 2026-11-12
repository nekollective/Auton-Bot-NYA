#include "main.h"
#include "pros/abstract_motor.hpp"
#include "pros/adi.hpp"
#include "pros/motors.hpp"

pros::Motor L1(5, pros::MotorGears::blue, pros::MotorEncoderUnits::degrees);
pros::Motor L2(6, pros::MotorGears::blue, pros::MotorEncoderUnits::degrees);
pros::Motor L3(7, pros::MotorGears::blue, pros::MotorEncoderUnits::degrees);
pros::Motor R1(8, pros::MotorGears::blue, pros::MotorEncoderUnits::degrees);
pros::Motor R2(9, pros::MotorGears::blue, pros::MotorEncoderUnits::degrees);
pros::Motor R3(10, pros::MotorGears::blue, pros::MotorEncoderUnits::degrees);

// left motor group
pros::MotorGroup left_motor_group({-13, -12, 11});
// right motor group
pros::MotorGroup right_motor_group({3, 2, -1});

pros::adi::Pneumatics KlemToggle1('A', false);
pros::adi::Pneumatics RollerToggle1('B', false);

// MOTORS
pros::Motor Cascade(16, pros::MotorGears::blue, pros::MotorEncoderUnits::degrees);
pros::MotorGroup IntakeV({1, -18, 14}, pros::MotorGears::blue, pros::MotorEncoderUnits::degrees);
pros::Motor Klem(19, pros::MotorGears::blue, pros::MotorEncoderUnits::degrees);
pros::MotorGroup Intake({18, -14}, pros::MotorGears::blue, pros::MotorEncoderUnits::degrees);


// drivetrain settings
lemlib::Drivetrain drivetrain(&left_motor_group, // left motor group
                              &right_motor_group, // right motor group
                              12, // 12 inch track width
                              lemlib::Omniwheel::NEW_325, // using new 4" omnis
                              360, // drivetrain rpm is 360
                              2 // horizontal drift is 2 (for now)
);


// imu
pros::Imu imu(5);
// horizontal tracking wheel encoder
pros::Rotation horizontal_encoder(10);
// vertical tracking wheel encoder
pros::Rotation vertical_encoder(6);
// horizontal tracking wheel
lemlib::TrackingWheel horizontal_tracking_wheel(&horizontal_encoder, lemlib::Omniwheel::NEW_2, -3);
// vertical tracking wheel
lemlib::TrackingWheel vertical_tracking_wheel(&vertical_encoder, lemlib::Omniwheel::NEW_2, -1);

// odometry settings
lemlib::OdomSensors sensors(&vertical_tracking_wheel, // vertical tracking wheel 1, set to null
                            nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                            &horizontal_tracking_wheel, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);

// lateral PID controller
lemlib::ControllerSettings lateral_controller(5, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              3, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              20 // maximum acceleration (slew)
);

// angular PID controller
lemlib::ControllerSettings angular_controller(2, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              10, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in degrees
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in degrees
                                              500, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

// create the chassis
lemlib::Chassis chassis(drivetrain, // drivetrain settings
                        lateral_controller, // lateral PID settings
                        angular_controller, // angular PID settings
                        sensors // odometry sensors
);