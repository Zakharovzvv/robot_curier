#include <Arduino.h>
#include <header.h>
#include <drive.h>
#include <uzd.h>
#include <LCD.h>
#include <encoder.h>
#include <log.h>

// Функция для нормализации значений, которые выдает ИК датчик
int getIRSensorValue(int sensor)
{
  int result;
  int irValue = analogRead(sensor); // Читаем значение датчика

  if (sensor == IR_SENSOR_L_PIN)
  {
    minIRL = min(minIRL, irValue); // Обновляем минимальные и максимальные значения
    maxIRL = max(maxIRL, irValue); // Обновляем минимальные и максимальные значения
    result = map(irValue, minIRL, maxIRL, 0, 1024); // Преобразовываем значения датчиков
//    consoleLog("minIRL", minIRL,"maxIRL", maxIRL,"irValue", irValue,"result", result);
  }
  else if (sensor == IR_SENSOR_R_PIN)
  {
    minIRR = min(minIRR, irValue);                  // Обновляем минимальные и максимальные значения
    maxIRR = max(maxIRR, irValue);                  // Обновляем минимальные и максимальные значения
    result = map(irValue, minIRR, maxIRR, 0, 1024); // Преобразовываем значения датчиков
 //   consoleLog("minIRR", minIRR,"maxIRR", maxIRR,"irValue", irValue,"result", result);
  }
   else if (sensor == IR_SENSOR_M_PIN)
  {
    minIRM = min(minIRM, irValue);                  // Обновляем минимальные и максимальные значения
    maxIRM = max(maxIRM, irValue);                  // Обновляем минимальные и максимальные значения
    result = map(irValue, minIRM, maxIRM, 0, 1024); // Преобразовываем значения датчиков
  };
  //  consoleLog("minIRL", minIRL, "minIRM", minIRM, "minIRR", minIRR, testTime);
  //  consoleLog("maxIRL", maxIRL, "maxIRM", maxIRM, "maxIRR", maxIRR, testTime);
  return result;
}

// Функция возвращает значение ошибки между показаниями левого и правого ИК датчика
int getIRError()
{
  int x = getIRSensorValue(IR_SENSOR_L_PIN);
  int y = getIRSensorValue(IR_SENSOR_R_PIN);
  // if (logLCD)
  // {
  //   lcdShow(0, 8,"IRL", x);
  //   lcdShow(1, 8, "IRR",y);
  // }
  return y - x;
}

int getEncoderError()
{
  int x = getEncoderL();
  int y = getEncoderR();
  // if (logLCD)
  // {
  //   lcdShow(0, 8, "EncL",x);
  //   lcdShow(1, 8, "EncR",y);
  // }
  return y - x;
}

int getWallError()
{
  return getSideDistance() - walldistance;
}

int getError()
{
  return maze ? getWallError() : followTheLane ? getIRError()
                                               : getEncoderError();
}

bool isOnBlack(int sensor)
{
  bool result = false;
  if (getIRSensorValue(sensor) < BLACK_LIMIT)
  {
    result = true;
  }
  return result;
}

// находятся ли датчики на черной линии
bool isOnCross()
{
  bool result = false;
  if (isOnBlack(IR_SENSOR_L_PIN) && isOnBlack(IR_SENSOR_R_PIN))
  {
    result = true;
  }
  return result;
}
