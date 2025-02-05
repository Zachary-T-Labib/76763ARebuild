#include "main.h"
#include "lemlib/api.hpp"

extern double BROWN_REST;
extern double BROWN_ACTIVE;
extern double BROWN_SCORE;
void setIntake(int intakePower);

extern bool intakeVoltageActive;
void activateIntakeVoltageControl(bool activated);
void intakeVoltage();

void stopIntake();
void clampActivated(bool activated);

void setBrown(int brownPower);
void brownWait();
void brownTask();
void setBrownTarget(double target);
extern lemlib::PID brownControl;
extern double brownError;

extern bool holdRingEnabled;
extern bool activeRingHolding;
void holdRing();

extern bool mogoSearchEnabled;
extern bool mogoRelease;
void autoMogo();
void setAutoMogo(bool activated);
void releaseMogo();
void activateRingHolding(bool activated);