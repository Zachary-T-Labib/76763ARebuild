#include "main.h"
#include "lemlib/api.hpp"

pros::rtos::Task autonomousMogo(autoMogo);

pros::rtos::Task ringHolding(holdRing);

pros::rtos::Task Brown_Task(brownTask);

pros::rtos::Task Color_Sorter(colorSorter);

pros::rtos::Task brown_Macro(brownMacro);

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
void initialize() {
	pros::lcd::initialize(); // initialize brain screen
    chassis.calibrate(); // calibrate sensors

    // print position to brain screen
    pros::Task screen_task([&]() {
        while (true) {
            // print robot location to the brain screen
            pros::lcd::print(0, "X: %f", chassis.getPose().x); // x
            pros::lcd::print(1, "Y: %f", chassis.getPose().y); // y
            pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
            pros::lcd::print(3, "Hue: %f", colorSort.get_hue()); // heading
            // delay to save resources
            pros::delay(20);
        }
    });
    
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

ASSET(rush_txt);
ASSET(rush2_txt);
ASSET(ringRush_txt);

void autonomous() {
	// set position to x:0, y:0, heading:0
    // set position to x:0, y:0, heading:0
    chassis.setPose(0, 0, 0);
    // turn to face heading 90 with a very long timeout
    chassis.moveToPose(0, 24, 0, 10000);
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
    printf("hi");
    clampActivated(false);
    setAutoMogo(true);
    activateColorSort(true);
    setColor('b');

    while (true) {
        // get left y and right x positions
        int leftY = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightX = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

        // move the robot
        chassis.arcade(leftY, rightX);

        if (master.get_digital(DIGITAL_R1)) {
            setIntake(450, 200);
        } else if (master.get_digital(DIGITAL_R2)) {
            stopIntake();
        } else if (master.get_digital(DIGITAL_L1)) {
            setIntake(-400, -200);
        } else if (master.get_digital(DIGITAL_L2)) {
            intake.move_relative(-100, 400);
        }

        if (master.get_digital(DIGITAL_Y)) {
            clampActivated(false);
        } else if (master.get_digital(DIGITAL_B)) {
            clampActivated(true);
        }

        if (master.get_digital(DIGITAL_UP)) {
            brownMacroActivated = false;
            setBrownTarget(BROWN_SCORE);
        } else if (master.get_digital(DIGITAL_RIGHT)) {
            brownMacroActivated = true;
            setBrownTarget(BROWN_ACTIVE);
        } else if (master.get_digital(DIGITAL_DOWN)) {
            brownMacroActivated = false;
            setBrownTarget(BROWN_REST);
        } else if (master.get_digital(DIGITAL_LEFT)) {
            mogoSearchEnabled = false;
        }

        // delay to save resources
        pros::delay(25);
    }
}