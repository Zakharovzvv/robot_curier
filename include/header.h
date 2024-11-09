#ifndef HEADER_H
#define HEADER_H
// Устанавливаем номера пинов
extern const int IR_SENSOR_L_PIN;
extern const int IR_SENSOR_R_PIN;
extern const int IR_SENSOR_M_PIN;
extern const int MOTOR_L_DIRECTION_PIN;
extern const int MOTOR_L_SPEED_PIN;
extern const int MOTOR_R_DIRECTION_PIN;
extern const int MOTOR_R_SPEED_PIN;
extern const int SERVO_PIN;
extern const int MOTOR_L_ENCODER_PIN1;
extern const int MOTOR_L_ENCODER_PIN2;
extern const int MOTOR_R_ENCODER_PIN1;
extern const int MOTOR_R_ENCODER_PIN2;
extern const int UZF_TRIGGER_PIN;
extern const int UZF_ECHO_PIN;
extern const int UZS_TRIGGER_PIN;
extern const int UZS_ECHO_PIN;

extern const int MAX_MOTOR_SPEED;

extern const int BASE_SPEED;
extern const unsigned long BASE_DELAY;
extern int minIRL, minIRM,minIRR, maxIRL, maxIRM, maxIRR;

extern const int SERVO_OPEN_POSITION;
extern const int SERVO_CLOSE_POSITION;
extern const int BLACK_LIMIT;
extern unsigned long startTime;
extern const int DISTANCE_TO_PUT_BANKA;
extern const int DISTANCE_TO_TAKE_OBJECT;
extern const int DISTANCE_TO_CHECK_OBJECT;
extern int crossCount;
extern const int TIME_TO_DRIVE_CROSS;
extern bool haveBanka;
extern const int TIME_TO_DRIVE_FINISH;
extern int povorotDelay;
extern int povorotDelay2;
extern const int DISTANCE_TO_START_OBEZD;
extern int wallPosition;
extern int FINISH_CROSS_COUNT;
extern int finishcount;
extern unsigned long testTime;
extern int otezdDelay;
extern int banka;
extern int walldistance;
extern float pastUZDFValue;
extern float pastUZDSValue;
extern bool maze;
extern float Ei;
extern float Kp;  // пропорциональный
extern float Ki;   // интегральный
extern float Kd; // диференциальный
extern float Ep;
extern int wallDistance;
extern bool logLCD;
extern bool logConsole;
extern bool followTheLane;
extern const int CROSS_WIDTH;
extern bool findBankaThenTurn;
extern const int DISTANCE_TO_DRIVE_FINISH;
extern const unsigned long  DISPLAY_TIME;  
#endif