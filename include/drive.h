#include "header.h" 

#ifndef drive_h
#define drive_h

void turn(int count=1);
void start();
void finish();
void doezd();
void driveToObject(int distanceToStop=DISTANCE_TO_TAKE_OBJECT);
void driveBackToCross(int speed=-BASE_SPEED);
void turnGCross();
void stop(unsigned long execute = BASE_DELAY);
void pid(int speed=BASE_SPEED);
void turnEnc(int angle,int speed=BASE_SPEED);
void driveSomeTime(unsigned long timeToMove, int speed=BASE_SPEED);
void driveSomeDistance(int distnce, int speed=BASE_SPEED);
void go(int L, int R);
void obezdObject(int distanceToStartObezd, int moveSide,int moveForward);


#endif