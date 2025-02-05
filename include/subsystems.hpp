#pragma once

#include "api.h"

// Your motors, sensors, etc. should go here.  Below are examples

inline pros::Motor intake(-1, pros::v5::MotorGears::blue);
inline pros::Motor intake5_5w(4, pros::v5::MotorGears::green);
inline pros::Motor ladyBrown(-8, pros::v5::MotorGears::green);

inline pros::Rotation brownAngle(14);
inline pros::Distance intakeOccupied(19);
inline pros::Distance mogoOccupied(13);

inline pros::ADIDigitalOut mogoClamp('G');

inline pros::Controller master;