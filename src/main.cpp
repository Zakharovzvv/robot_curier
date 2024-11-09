#include <Wire.h>
#include <Arduino.h>
#include <NewPing.h>

#include <drive.h>
#include <middleware.h>
#include <uzd.h>
#include <header.h>
#include <servoMotor.h>
#include <banka.h>
#include <LCD.h>
#include <encoder.h>

#include <log.h>
#include <test.h>


// ################### Настройка пинов #############

const int MOTOR_L_DIRECTION_PIN = 2;
const int MOTOR_L_SPEED_PIN = 3;
const int MOTOR_R_DIRECTION_PIN = 4;
const int MOTOR_R_SPEED_PIN = 5;
const int UZS_TRIGGER_PIN = 6;
const int UZS_ECHO_PIN = 7;
const int MOTOR_L_ENCODER_PIN1 = 8;
const int MOTOR_L_ENCODER_PIN2 = 9;
const int MOTOR_R_ENCODER_PIN1 = 10;
const int MOTOR_R_ENCODER_PIN2 = 11;
const int SERVO_PIN = 12;
const int IR_SENSOR_L_PIN = A0;
const int IR_SENSOR_R_PIN = A1;
const int UZF_TRIGGER_PIN = A2;
const int UZF_ECHO_PIN = A3;
const int LCD_SDA_PIN = A4;
const int LCD_SCL_PIN = A5;
const int IR_SENSOR_M_PIN = A7;
// ################### Настройки программы ############

const int MAX_MOTOR_SPEED = 250;

// ############## Переменные ####################

// Базовые параметры
const int BASE_SPEED = 170; // базовая скорость
const unsigned long BASE_DELAY = 500;         // задержка между действиями

int minIRL = 200, minIRM = 200,minIRR = 200, maxIRL = 600, maxIRM = 600, maxIRR = 600;
unsigned long startTime = 0; // Время начала таймера
bool followTheLane = true;   // true - следуем по линии или false - едем прямо

// UZD
float pastUZDFValue; // предыдущее значение переднего датчика 
float pastUZDSValue; // предыдущее значение бокового датчика

// П регулятор
int const BLACK_LIMIT = 700; //   все что ниже-черная линия 
int walldistance = 8;     // расстояние до стены
bool maze = false;         // едем в лабиринте
float Ei = 0;
float Ep;
float Kp=0.6; // пропорциональный
float Ki=0; // интегральный
float Kd=0; // диференциальный

// Сервопривод
int const SERVO_OPEN_POSITION = 30;   // градус открытого серво
int const SERVO_CLOSE_POSITION = 90; // градус закытого серво

// Перекрестки
int crossCount = 0;        // количество перекрестков
int const TIME_TO_DRIVE_CROSS = 300;      // время за которое робот проезжает перекресток (ширину черной линии)
int const CROSS_WIDTH = 2;      // ширина перекрестка

// Работа с банкой
int timeToMoveBackWithBanka = 1000;  // время, которое робот едет назад с банкой
int const DISTANCE_TO_PUT_BANKA = 4; // Расстояние на котором должна стоять банка от перекрестка
int const DISTANCE_TO_TAKE_OBJECT = 6;   // расстояние на котром надо взять банку
int const DISTANCE_TO_CHECK_OBJECT = 20; // расстояние на котром ищем банку
bool haveBanka = false;        // Флаг обнаружения банки -есть или нет банки на по направлению движения

// Поворот
int maxErrorTurnFix = 10; // Макисмальная ошибка до которой идет выравнивание после поворота
int povorotDelay = 400;  // время, за которое ИК датчик робота гарантированно сместится с белого поля на черную линию при начале поворота
int povorotDelay2 = 200; // время, за которое ИК датчик робота гарантированно сместится с черной линии на белое поле при после того как он увидел начало белого поля
bool findBankaThenTurn = false; // Искать банку при повороте. Если нашли поворот прекратится.

// Финиш
int FINISH_CROSS_COUNT = 21; // номер перекрестка на которам надо финишировать
int finishcount = 0;         // увеличиваем crosscount при случае если надо финишировать на определенном перекрестке
int const TIME_TO_DRIVE_FINISH = 600;       // задержка при финишировании
int const DISTANCE_TO_DRIVE_FINISH = 15;       // сколько сантиметров надо проехать для заезда в финишную зону

// Логгирование
bool logLCD = true;
bool logConsole = true;
unsigned long  testTime = 2000;         // время для тестирования функции
const unsigned long  DISPLAY_TIME = 200;         // время для отображения информации на LCD дисплее

void setup()
{

  pinMode(MOTOR_L_DIRECTION_PIN, OUTPUT); // напр. мотора лев.
  pinMode(MOTOR_L_SPEED_PIN, OUTPUT);     // скор. мотора лев.
  pinMode(MOTOR_R_DIRECTION_PIN, OUTPUT); // напр. мотора прав.
  pinMode(MOTOR_R_SPEED_PIN, OUTPUT);     // скор. мотора прав.
  pinMode(UZF_TRIGGER_PIN, OUTPUT);       // пинок дальномера uzdF - фронтального
  pinMode(UZF_ECHO_PIN, INPUT);           // эхо-прием дальномера uzdF - фронтального
  pinMode(UZS_TRIGGER_PIN, OUTPUT);       // пинок дальномера uzdS - бокового
  pinMode(UZS_ECHO_PIN, INPUT);           // эхо-прием дальномера uzdS - бокового
  pinMode(IR_SENSOR_L_PIN, INPUT);        // пин левого датчика ИК
  pinMode(IR_SENSOR_R_PIN, INPUT);        // пин правого датчика ИК
  pinMode(IR_SENSOR_M_PIN, INPUT);        // пин правого датчика ИК
  pinMode(SERVO_PIN, OUTPUT);             // серво привод
  pinMode(LCD_SDA_PIN, OUTPUT);           // LCD
  pinMode(LCD_SCL_PIN, OUTPUT);           // LCD

  initLCD();
  initENC();
  initServo();
  logInit();
  // start();
}

void loop()
{
  // ##### Тесты Начало ######
   test();
  // ##### Тесты Конец ######
 //pid();
//driveSomeTime(1000);
//driveSomeTime(1000,-BASE_SPEED);
//  obezdObject(30,20,40);

}
