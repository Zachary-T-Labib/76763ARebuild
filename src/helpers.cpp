#include "main.h"

double BROWN_REST = 35300;
double BROWN_ACTIVE = 33300;
double BROWN_SCORE = 22400;

int BLUE_LOW = 200;
int BLUE_HIGH = 270;
int RED_LOW = 1;
int RED_HIGH = 25;
int oppColorMin = 0;
int oppColorMax = 0;

void setColor(char color) {
    if (color == 'r') {
        oppColorMax = RED_HIGH;
        oppColorMin = RED_LOW;
    } else if (color == 'b') {
        oppColorMax = BLUE_HIGH;
        oppColorMin = BLUE_LOW;
    }
}

void setIntake(int intakePower) {
    intake.move_velocity(intakePower);
    intake5_5w.move_velocity(intakePower*0.33333333333);
}

void stopIntake() {
    intakeVoltageActive = false;
    intake.brake();
    intake5_5w.brake();
}

void clampActivated(bool activated) {
    mogoClamp.set_value(activated);
}

void setBrown(int brownPower) {
    ladyBrown.move(brownPower);
}

void setAutoMogo(bool activated) {
    mogoSearchEnabled = activated;
}

void releaseMogo() {
    mogoRelease = true;
}

void activateRingHolding(bool activated) {
    activeRingHolding = activated;
}

void activateIntakeVoltageControl(bool activated) {
    intakeVoltageActive = activated;
}

void activateColorSort(bool activated) {
    colorSortEnabled = activated;
}

bool intakeVoltageActive = false;
void intakeVoltage() {
    while (true){    
        printf("Actual velocity: %lf", intake.get_actual_velocity());
        if (intake.get_actual_velocity() < 400 && intakeVoltageActive == true) {
            intake.move_voltage(12000);
        } else if (intakeVoltageActive == true){
            intake.move_voltage(8400);
        }
        pros::delay(20);
    }
}
// d 0.1
lemlib::PID brownPID(0.04, 0.0, 0.05, 0);
double brownError = BROWN_REST - brownAngle.get_position();

void brownTask() {
    while (true){
        setBrown(brownPID.update(brownError));
        pros::delay(20);
    }
    
}

void setBrownTarget(double target) {
    brownPID.reset();
    brownError = target - brownAngle.get_position();
}

bool holdRingEnabled = false;
bool activeRingHolding = false;
void holdRing() {
    pros::delay(2000);
    while (true) {
        while (holdRingEnabled) {
            if (activeRingHolding == true && intakeOccupied.get() <= 72) {
                stopIntake();
            }

            pros::delay(20);
        }

    pros::delay(20);
    }
}

bool colorSortEnabled = false;
void colorSorter() {
    printf("workijg");
    pros::delay(2000);
    colorSort.set_integration_time(5);
    colorSort.set_led_pwm(100);

    while (true) {
       while(colorSortEnabled) {
            if ((colorSort.get_hue() >= oppColorMin && colorSort.get_hue() <= oppColorMax) && colorSort.get_proximity() < 250) {
                // pros::delay(1);
                setIntake(-450);
                pros::delay(100);
                setIntake(450);
            }

       }
       pros::delay(20);
    }
}


bool mogoSearchEnabled = false;
bool mogoRelease = false;
void autoMogo() {
    pros::delay(2000);
    while (true) {
        while (mogoSearchEnabled) {
            if (master.get_digital(DIGITAL_B) || mogoRelease == true) {
                clampActivated(false);

                while (mogoOccupied.get() <= 50)
                {
                    pros::delay(20);
                }
            
                mogoRelease = false;
            }

            if (master.get_digital(DIGITAL_Y) || mogoOccupied.get() <= 50) {
                pros::delay(10);
                clampActivated(true);
            }

            pros::delay(20);
        }

    pros::delay(20);
    }
}