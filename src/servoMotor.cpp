
#include <Arduino.h>
#include <header.h>
#include <Servo.h>

Servo servo;

void initServo(){
  servo.attach(SERVO_PIN);
  servo.write(SERVO_OPEN_POSITION);
}

void closeServo()
{
  for (int i = SERVO_OPEN_POSITION; i < SERVO_CLOSE_POSITION; i++)
  {
    servo.write(i);
    delay(20);
  }
  delay(BASE_DELAY);
}

void openServo()
{
  for (int i = SERVO_CLOSE_POSITION; i > SERVO_OPEN_POSITION; i--)
  {
    servo.write(i);
    delay(20);
  }
  delay(BASE_DELAY);
  //servo.write(SERVO_OPEN_POSITION);
}