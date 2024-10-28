

#include <arduino_encoder.h>
#include <PinChangeInterrupt.h>
#include <PinChangeInterruptBoards.h>
#include <PinChangeInterruptPins.h>
#include <PinChangeInterruptSettings.h>
#include <Arduino.h>
#include <header.h>

Encoder encL;
Encoder encR;

void initENC(){
  encL.setup(MOTOR_L_ENCODER_PIN1, MOTOR_L_ENCODER_PIN2);
  encR.setup(MOTOR_R_ENCODER_PIN1, MOTOR_R_ENCODER_PIN2);
  encL.reverse();
  encR.reverse();
}

long getEncoderL(){
long  value=encL.get();
//lcdShow(0, 0, value);
  return -value; // Энкодер выдает отрицательные значения при движении вперед, поэтому меняем знак

  
}

long getEncoderR(){
long  value=encR.get();
//lcdShow(1, 0, value);
  return value;
  
}

void clearEncoderL(){
   encL.clear(); 
}

void clearEncoderR(){
   encR.clear(); 
}
void clearEncoders(){
   clearEncoderL();
   clearEncoderR(); 
}