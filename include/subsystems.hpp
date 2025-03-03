#pragma once

#include "api.h"

// Your motors, sensors, etc. should go here.  Below are examples
inline pros::Optical colorSort(3);

inline pros::Motor intake(-5, pros::v5::MotorGears::blue);
inline pros::Motor intake5_5w(-20, pros::v5::MotorGears::green);
inline pros::Motor ladyBrown(4, pros::v5::MotorGears::green);

inline pros::Rotation brownAngle(9);
inline pros::Distance intakeOccupied(21);
inline pros::Distance topIntakeSensor(6);
inline pros::Distance mogoOccupied(11);

inline pros::adi::DigitalOut mogoClamp('A');

inline pros::Controller master(pros::E_CONTROLLER_MASTER);

// Create Drivetrain Motor Groupings (CLARIFY PORTS/DIRECTIONS)
inline pros::MotorGroup left_drive_motors({-2, -7, -8}, pros::MotorGearset::blue); // left motors on ports 1, 2, 3
inline pros::MotorGroup right_drive_motors({1, 16, 19}, pros::MotorGearset::blue); // right motors on ports 4, 5, 6

// create an imu on port 10 (CLARIFY PORT)
inline pros::Imu imu(18);

// (CLARIFY PORT)
inline pros::Rotation horizontal_sensor(-13);

// (CLARIFY PORT))
inline pros::Rotation vertical_sensor(-12);

// horizontal tracking wheel (CHANGE OFFSETS)
inline lemlib::TrackingWheel horizontal_tracking_wheel(&horizontal_sensor, 2, -2.17);
// vertical tracking wheel (CHANGE OFFSETS)
inline lemlib::TrackingWheel vertical_tracking_wheel(&vertical_sensor, 2, -0.03);

// drivetrain settings
inline lemlib::Drivetrain drivetrain(&left_drive_motors, // left motor group
                              &right_drive_motors,// right motor group
                              11.125, // 10 inch track width REPLACE WITH REAL ONE
                              lemlib::Omniwheel::NEW_325, // using new 4" omnis
                              450, // drivetrain rpm is 360
                              2 // horizontal drift is 2 (for now)
);

inline lemlib::OdomSensors sensors(&vertical_tracking_wheel, // vertical tracking wheel 1, set to null
                            nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                            &horizontal_tracking_wheel, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);

// lateral PID controller
inline lemlib::ControllerSettings lateral_controller(20, // proportional gain (kP) // old 10
                                              0, // integral gain (kI)
                                              200, // derivative gain (kD) // old 200
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              50 // maximum acceleration (slew)
);

// angular PID controller
inline lemlib::ControllerSettings angular_controller(4, // proportional gain (kP) // old 6
                                              0, // integral gain (kI)
                                              40, // derivative gain (kD) // old 60
                                              3, // anti windup
                                              1, // small error range, in degrees
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in degrees
                                              500, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

// input curve for throttle input during driver control
inline lemlib::ExpoDriveCurve throttle_curve(3, // joystick deadband out of 127
                                     10, // minimum output where drivetrain will move out of 127
                                     1.019 // expo curve gain
);

// input curve for steer input during driver control
inline lemlib::ExpoDriveCurve steer_curve(3, // joystick deadband out of 127
                                  10, // minimum output where drivetrain will move out of 127
                                  1.019 // expo curve gain
);

// create the chassis
inline lemlib::Chassis chassis(drivetrain, // drivetrain settings
                        lateral_controller, // lateral PID settings
                        angular_controller, // angular PID settings
                        sensors,
                        &throttle_curve, 
                        &steer_curve
);