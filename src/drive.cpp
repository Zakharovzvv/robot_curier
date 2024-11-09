#include <Arduino.h>
#include <header.h>
#include <middleware.h>
#include <UZD.h>
#include <servoMotor.h>
#include <LCD.h>
#include <banka.h>
#include <encoder.h>
#include <log.h>

void go(int L, int R)
{
  digitalWrite(MOTOR_L_DIRECTION_PIN, L > 0 ? HIGH : LOW); // Управляем направлением левого мотора
  analogWrite(MOTOR_L_SPEED_PIN, abs(L));                  // Управляем скоростью левого мотора
  digitalWrite(MOTOR_R_DIRECTION_PIN, R > 0 ? HIGH : LOW); // Управляем направлением правого мотора
  analogWrite(MOTOR_R_SPEED_PIN, abs(R));                  // Управляем скоростью правого мотора

  // lcdShow(0, 5, L);
  // lcdShow(1, 5, R);
  // if (logConsole)
  // {
  //  consoleLog("EncL", getEncoderL(), "EncR", getEncoderR());
  // }
}

void pid(int speed = BASE_SPEED)
{

  if (maze == true)
  {
    Kp = 10; // пропорциональный
    Ki = 0;  // интегральный
    Kd = 10; // диференциальный
  }

  Ep = getError();

  int Ed = Ep - Ei;
  int U = Ep * Kp + Ei * Ki + Ed * Kd;

  // if (isOnBlack(IR_SENSOR_M_PIN))
  // {
  //   U = -U;
  // }

  int M1 = speed + U;
  M1 = constrain(M1, -MAX_MOTOR_SPEED, MAX_MOTOR_SPEED);
  int M2 = speed - U;
  M2 = constrain(M2, -MAX_MOTOR_SPEED, MAX_MOTOR_SPEED);

  go(M1, M2);

  Ei = Ei * 0.7 + Ep * 0.3;

  // if (logLCD) {
  //     lcdShow(0, 0,"M1", M1);
  //     lcdShow(1, 0, "M2",M2);
  //      lcdShow(0, 0, "Ep",Ep);

  //  };
  // if (logConsole)
  // {
  //   consoleLog("Ep", Ep, "U", U);
  //   consoleLog("Speed L", M1, "Speed R", M2);
  // };
}

void stop(unsigned long execute = BASE_DELAY)
{
  // for (int i = 0; i < 40; i++)
  // {
  //   go(BASE_SPEED, BASE_SPEED);
  //   go(-BASE_SPEED, -BASE_SPEED);
  // }

  go(0, 0);
  startTime = millis();
  while (millis() - startTime < execute)
  {
  } // Ждем пока закончится импульс инерции
}

void turnEnc(int angle, int speed = BASE_SPEED)
{
  int direction;
  Kp = 2; // пропорциональный

  int A = map(abs(angle), 0, 360, 0, 6200);

  if (angle > 0)
    direction = 1; // лево
  else
    direction = -1; // право

  clearEncoders();

  while (abs(getEncoderL()) < A || abs(getEncoderR()) < A)
  {
    int E = getEncoderError();
    int U = E * Kp;
    float M1 = direction * (speed + U);
    M1 = constrain(M1, -MAX_MOTOR_SPEED, MAX_MOTOR_SPEED);
    float M2 = -direction * (speed - U);
    M2 = constrain(M2, -MAX_MOTOR_SPEED, MAX_MOTOR_SPEED);

    go(M1, M2);

    if (findBankaThenTurn && checkBankaForward()) // Если увидели банку останавливаем поворот
    {
      stop();
      return; // Выход из функции
    }
  }
  clearEncoders();
  stop();
}

void turnSomeTime(unsigned long timeToTurn, int speedL = BASE_SPEED, int speedR = BASE_SPEED)
{

  startTime = millis();                     // Считываем текущее время
  while (millis() - startTime < timeToTurn) // Пока текущее время - время старта таймера меньше заданного интервала
  {
    go(speedL, speedR);
  }

  stop();
}

void turn(int count = 1)
{
  int direction, sensor;

  if (count > 0)
  {
    direction = 1; // лево
    sensor = IR_SENSOR_R_PIN;
  }
  else
  {
    direction = -1; // право
    sensor = IR_SENSOR_R_PIN;
  }
  int speedL = direction * BASE_SPEED;
  int speedR = -direction * BASE_SPEED;

  for (int i = 0; i < count - 1; i++)
  {
    turnSomeTime(povorotDelay, speedL, speedR); // Поворачиваем так, чтобы правый ИК датчик сместился с белого на черную линию

    //  go(0, 0, BASE_DELAY);
    while (isOnBlack(sensor)) // Поворачиваем пока правый ИК датчик на черной линии
    {
      go(speedL, speedR);
    }

    turnSomeTime(povorotDelay2, speedL, speedR); // Поворачиваем так, чтобы правый ИК датчик сместился с черной линии на белое поле

    //  go(0, 0, BASE_DELAY);
    while (!isOnBlack(sensor)) // Поворачиваем пока правый ИК датчик на белом поле
    {
      go(speedL, speedR);

      if (findBankaThenTurn && checkBankaForward()) // Если увидели банку останавливаем поворот
      {
        stop();
        return; // Выход из функции
      }
    }

    // fixPositionAfterTurn();

    stop();
  }
}

void driveSomeTime(unsigned long timeToMove, int speed = BASE_SPEED)
{
  clearEncoders();
  startTime = millis();                     // Считываем текущее время
  while (millis() - startTime < timeToMove) // Пока текущее время - время старта таймера меньше заданного интервала
  {
    pid(speed);
  }
  clearEncoders();
  stop();
}

void driveSomeDistance(int distance, int speed = BASE_SPEED)
{
  clearEncoders();
  while (getEncoderL() < distance) // Пока рассстояние пройденное машиной меньше distance
  {
    pid(speed);
  }
  clearEncoders();
  stop();
}

void start()
{
  followTheLane = false;
  // Едем вперед пока не увидим поперечную черную линию
  while (!isOnCross())
  {
    pid();
  }
  driveSomeDistance(CROSS_WIDTH); // проезжаем поперечную черную линию пока черная линия трассы не окажется между датчиками

  stop();

  followTheLane = true;
}

void finish()
{
  // if (crossCount == FINISH_CROSS_COUNT)
  //{
  driveSomeDistance(DISTANCE_TO_DRIVE_FINISH);
  stop();
  while (true)
    ;
  //}
}

void doezd()
{
  driveSomeDistance(CROSS_WIDTH);
  stop();
}

void driveToObject(int distanceToStop = DISTANCE_TO_TAKE_OBJECT)
{
  while (getForwardDistance() > distanceToStop) // едем вперед на preg() пока расстояние до банки не будет меньше  DISTANCE_TO_TAKE_OBJECT
  {
    pid();
  }
  stop();
}

// едем пока не увидим линию перекрестка
void driveBackToCross(int speed = -BASE_SPEED)
{
  // followTheLane = false; False - Едем по экодерам, True (по умолчанию) - Едем по ИК датчикам
  while (!isOnCross())
  {
    pid(speed);
  }
  // followTheLane = true;
  stop();
}

void turnGCross()

{
  // если мы попали на резкий поворот то мы проверяем находятся ли правый и центральный датчик на черном и поворачиваем
  if (isOnBlack(IR_SENSOR_R_PIN) && isOnBlack(IR_SENSOR_M_PIN) && crossCount == 8)
  {
    // doezd();
    turn();
    // driveSomeTime(300);
  }
  else if (isOnBlack(IR_SENSOR_L_PIN) && isOnBlack(IR_SENSOR_M_PIN) && crossCount == 8)
  {
    // doezd();
    turn(-1);
    // driveSomeTime(300);
  }
}

void obezdObject(int distanceToStartObezd, int moveSide, int moveForward)
{
  driveToObject(distanceToStartObezd); // едем вперед пока не увидим банку
  followTheLane = false;
  turnEnc(-45);                // поворачиваем влево пока мы на линии с банкой
  driveSomeDistance(moveSide); // едем вперед, чтобы уйти с линии где банка
  turnEnc(45);
  driveSomeDistance(moveForward);       // едем вперед секунду чтобы уйти с линии где банка
  turnEnc(45);                          // поворачиваем влево
  while (IR_SENSOR_R_PIN > BLACK_LIMIT) // едем пока не вернемся на линию
  {
    pid();
  }
  stop();
  followTheLane = true;
}

// ##### Legacy #########################################################################################################

void preg(int speed)
{
  // float p_gain = (speed == 0) ? KOEF_ERROR * gainCoeff : KOEF_ERROR;

  int E = getIRError(); /**/

  int uprvozd = E * Kp;

  int M1 = speed + uprvozd;
  M1 = constrain(M1, -MAX_MOTOR_SPEED, MAX_MOTOR_SPEED);
  int M2 = speed - uprvozd;
  M2 = constrain(M2, -MAX_MOTOR_SPEED, MAX_MOTOR_SPEED);

  //   lcdShow(0, 0, M1);
  //   lcdShow(1, 0, M2);
  //   lcdShow(1, 8, E);
  //   lcdShow(1, 8, uprvozd);
  //   delay(500);
  // lcdclear();

  go(M1, M2);
}

// float k = 0.5;
// void WhitePreg(int speed)
// {

//   int E = analogRead(A0) - analogRead(A1);
//   int uprvozd = E * k;

//   int M1 = speed - uprvozd;
//   M1 = constrain(M1, -250, 250);
//   int M2 = speed + uprvozd;
//   M2 = constrain(M2, -250, 250);

//   go(M1, M2);
// }
// void fixPositionAfterTurn()
// {
//   // Выравниваем робота после поворота пока ошибка(разность показаний левого и правого ИК датчика) не будет меньше maxErrorTurnFix
//   while (getIRError() < maxErrorTurnFix)
//   {
//     preg(0);
//   }
//   // if (fixPosition) // Корректируем положение машины относительно черной линии
//   // {
//   //   go(0, 0, BASE_DELAY / 3);                         // Ждем пока закончится импульс инерции при повороте
//   //   startTime = millis();                            // Считываем текущее время
//   //   while (millis() - startTime < timeToMoveBanka) // Пока текущее время - время старта таймера меньше интервала выравнивания едем по preg()
//   //   {
//   //     preg();
//   //   }
//   //   go(0, 0, BASE_DELAY / 3);                           // Ждем пока закончится импульс инерции
//   //   go(-BASE_SPEED, -BASE_SPEED, timeToMoveBanka); // Едем назад,чтобы вернуться на перекресток
//   // }
// }