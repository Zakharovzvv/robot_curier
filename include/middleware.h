#ifndef middleware_h
#define middleware_h


int getIRSensorValue(int sensor);
bool isOnCross();
bool isOnBlack(int sensor);
int getIRError();
int getWallError();
int getError();
int getEncoderError();

#endif