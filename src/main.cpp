#include "main.h"
#include "pros/misc.h"
#include "pros/motors.h"
#include "robotConfig.h"
#include "autons.h"
#include "autonSelector.h"
#include <cmath>

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
// initialize function. Runs on program startup
void initialize() {
    pros::lcd::initialize(); // initialize brain screen
	pros::lcd::print(3, "CALIBRATING");
    chassis.calibrate(); // calibrate sensors
	pros::lcd::print(3, "READY");
	displayAutonselector(); // display auton selector on brain screen
}
/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	// run the selected autonomous routine
	switch (getSelectedAuton()) {
		case 0:
			testAuton();
			break;
		case 1:
			printTemp();
			break;
		case 2:
			redNear();
			break;
		case 3:
			redFar();
			break;
		case 4:
			blueNear();
			break;
		case 5:
			blueFar();
			break;
		case 6:
			skills();
			break;
		default:
			pros::lcd::print(3, "Error: Ongeldige auton selectie");
			break;
	}
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	pros::Controller controller(pros::E_CONTROLLER_MASTER);
	uint32_t lastDisplayUpdate = 0;
	pros::lcd::print(3, "OPCONTROL");

	while (true) {
		// ARCADE DRIVE //

		int throttle = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		int turn = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
		if (pros::millis() - lastDisplayUpdate >= 200) {
			lastDisplayUpdate = pros::millis();
			lemlib::Pose pose = chassis.getPose();
			pros::lcd::print(0, "X:%.1f Y:%.1f", pose.x, pose.y);
			pros::lcd::print(1, "Theta:%.1f", pose.theta);
		}

		// move the robot
		chassis.arcade(throttle, turn);

		pros::delay(20);

		// TANK DRIVE //

		/* int throttle = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		int rightY = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

		chassis.tank(throttle, rightY); */

		// INTAKE //
		if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
			Intake.move_velocity(200);
		} else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2	)) {
			Intake.move_velocity(-200);
		} else {
			Intake.move_velocity(0);
		}

		// CASCADE //
		if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
			Cascade.move_velocity(200);
		} else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
			Cascade.move_velocity(-200);
		} else {
			Cascade.move_velocity(0);
		}

		// KLEM TOGGLE //
		if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) {
			KlemToggle1.set_value(!KlemToggle1.is_extended());
			KlemToggle2.set_value(!KlemToggle2.is_extended());
		}
	}

}