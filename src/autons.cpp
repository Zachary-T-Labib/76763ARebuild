#include "main.h"

ASSET(psuedoSkillsFirstGoal_txt);
ASSET(psuedoSkilsBottomFour_txt);
ASSET(psuedoSkillsPlaceGoalOne_txt);
ASSET(psuedoSkillsSecondGoal_txt);
ASSET(psuedoSkillsTopFour_txt);
ASSET(psuedoSkillsPlaceGoalTwo_txt);
ASSET(psuedoSkillsHoldRing_txt);
ASSET(psuedoSkillsThirdGoal_txt);
ASSET(psuedoSkillsPushFourthGoal_txt);
ASSET(psuedoSkillsPushFifthGoal_txt);

void skills() {
    clampActivated(false);
    setAutoMogo(true);

    chassis.setPose(-60.296, 0.131, 90);

    setIntake(450);
    pros::delay(750);

    chassis.turnToPoint(0, 0, 20000, {.forwards = false, .minSpeed = 127, .earlyExitRange = 20});

    chassis.follow(psuedoSkillsFirstGoal_txt, 15, 20000, false);

    chassis.follow(psuedoSkilsBottomFour_txt, 15, 20000);

    chassis.turnToPoint(-50.842, -59.23, 20000, {.forwards = false, .minSpeed = 127, .earlyExitRange = 20});

    chassis.follow(psuedoSkillsPlaceGoalOne_txt, 15, 20000, false);

    releaseMogo();

    chassis.turnToPoint(-59.0, -49.0, 20000, {.forwards = false, .minSpeed = 127, .earlyExitRange = 20});

    chassis.follow(psuedoSkillsSecondGoal_txt, 15, 20000, false);

    chassis.follow(psuedoSkillsTopFour_txt, 15, 20000);

    chassis.turnToPoint(-57.0, 61.0, 20000, {.forwards = false, .minSpeed = 127, .earlyExitRange = 20});

    chassis.follow(psuedoSkillsPlaceGoalTwo_txt, 15, 20000, false);

    releaseMogo();

    activateRingHolding(true);

    chassis.follow(psuedoSkillsHoldRing_txt, 15, 20000);

    chassis.turnToPoint(24.0, 0.0, 20000, {.forwards = false, .minSpeed = 127, .earlyExitRange = 20});

    chassis.follow(psuedoSkillsThirdGoal_txt, 15, 20000, false);

    chassis.turnToPoint(24.0, -24.0, 20000, {.forwards = false, .minSpeed = 127, .earlyExitRange = 20});

    releaseMogo();

    chassis.follow(psuedoSkillsPushFourthGoal_txt, 15, 20000);

    chassis.turnToPoint(48.0, 24.0, 20000, {.minSpeed = 127, .earlyExitRange = 20});

    chassis.follow(psuedoSkillsPushFifthGoal_txt, 15, 20000);
}

/* * * * * * * * * * * * * * 
* Goal Rushes
* * * * * * * */

void blueGoalRush() {

}

ASSET(ringRushGetMogo_txt);
ASSET(ringRushGetLineRings_txt);
ASSET(ringRushGetCornerRing_txt);
ASSET(ringRushGetUpperRings_txt);
ASSET(ringRushGetMidRingLadder_txt);

void redGoalRush() {
    clampActivated(false);
    setAutoMogo(true);

    chassis.setPose(-57.987, 23.622, 90);

    chassis.follow(ringRushGetMogo_txt, 15, 20000, false);

    chassis.turnToPoint(-19.694, 24.371, 20000, {.minSpeed = 127, .earlyExitRange = 20});

    setIntake(450);
    chassis.follow(ringRushGetLineRings_txt, 15, 20000);

    chassis.follow(ringRushGetUpperRings_txt, 15, 20000);

    chassis.follow(ringRushGetCornerRing_txt, 15, 20000);

    pros::delay(1000);

    chassis.follow(ringRushGetMidRingLadder_txt, 15, 20000);

}

/* * * * * * * * * * * * * * 
* Ring Rushes
* * * * * * * */

void blueRingRush() {
    
}

ASSET(goalRushLineGoal_txt);
ASSET(goalRushLowerRing_txt);
ASSET(goalRuhSecondGoal_txt);
ASSET(goalRushCorner_txt);

void redRingRush() {
    clampActivated(false);
    setAutoMogo(true);

    chassis.setPose(-52.121, -58.292, -90);

    chassis.follow(goalRushLineGoal_txt, 15, 20000, false);

    chassis.turnToPoint(-11.306, -50.841, 20000, {.minSpeed = 127, .earlyExitRange = 20});

    setIntake(450);

    chassis.follow(goalRushLowerRing_txt, 15, 20000);

    chassis.turnToPoint(-30.0, -50.0, 20000, {.forwards = false, .minSpeed = 127, .earlyExitRange = 20});

    releaseMogo();

    chassis.turnToPoint(-23.622, -43.016, 20000, {.forwards = false, .minSpeed = 127, .earlyExitRange = 20});

    chassis.follow(goalRuhSecondGoal_txt, 15, 20000, false);

    chassis.turnToPoint(-26.448, -20.693, 20000, {.minSpeed = 127, .earlyExitRange = 20});

    chassis.follow(goalRushCorner_txt, 15, 20000);
}