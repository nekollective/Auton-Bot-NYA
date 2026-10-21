#include "main.h"
#include "robotConfig.h"
#include "autons.h"

int selectedAuton = 0;

const char* autonNames[] = {
    "Test Auton",
    "Print Temperatures",
    "Red Near",
    "Red Far",
    "Blue Near",
    "Blue Far",
    "Skills"
};
const int autonCount = sizeof(autonNames) / sizeof(autonNames[0]);

int getSelectedAuton() {
    return selectedAuton;
}

void displayAutonSelector(){
    pros::lcd::set_text(0, "Selecteer Auton:");
    pros::lcd::set_text(1, autonNames[selectedAuton]);
    pros::lcd::register_btn0_cb([]() {
        selectedAuton = (selectedAuton - 1 + autonCount) % autonCount;
        pros::lcd::set_text(1, autonNames[selectedAuton]);
    });
    pros::lcd::register_btn2_cb([]() {
        selectedAuton = (selectedAuton + 1) % autonCount;
        pros::lcd::set_text(1, autonNames[selectedAuton]);
    });
}