#include "liblvgl/llemu.hpp"
#include "main.h"
#include "robotConfig.h"
#include "autonSelector.h"

int selectedControls = 0;
bool controlsConfirmed = false;

int getSelectedControls() {
    return selectedControls;
}

bool areControlsConfirmed() {
    return controlsConfirmed;
}

void displayControlsSelector(){
    pros::lcd::initialize();
    pros::lcd::set_text(3, "Selecteer Bestuurder:");
    pros::lcd::set_text(4, "[LINKS] Toon | [RECHTS] Warre");
    pros::lcd::set_text(5, "[MIDDEN] Bevestigen");

    // Linkerknop = Toon
    pros::lcd::register_btn0_cb([]() {
        selectedControls = 0;
        pros::lcd::set_text(6, "Geselecteerd: Toon ");
    });

    // Middenknop = Bevestigen
    pros::lcd::register_btn1_cb([]() {
        controlsConfirmed = true;
        pros::lcd::set_text(6, "Bestuurder bevestigd!");
    });

    // Rechterknop = Warre
    pros::lcd::register_btn2_cb([]() {
        selectedControls = 1;
        pros::lcd::set_text(6, "Geselecteerd: Warre ");
    });

    if (controlsConfirmed) {
        pros::delay(20);
        pros::lcd::clear_line(3);
        pros::lcd::clear_line(4);
        pros::lcd::clear_line(5);
        pros::lcd::clear_line(6);
        displayAutonSelector();
    }
}