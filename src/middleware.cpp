#include <Arduino.h>
#include <header.h>
#include <drive.h>
#include <uzd.h>
#include <LCD.h>
#include <encoder.h>

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
  }
  else
  {
    minIRR = min(minIRR, irValue);                  // Обновляем минимальные и максимальные значения
    maxIRR = max(maxIRR, irValue);                  // Обновляем минимальные и максимальные значения
    result = map(irValue, minIRR, maxIRR, 0, 1024); // Преобразовываем значения датчиков
  };
  // return IS_IR_SENSORS_REVERS? 1024-result:result;
  return result;
}

// Функция возвращает значение ошибки между показаниями левого и правого ИК датчика
int getIRError()
{
  int x = getIRSensorValue(IR_SENSOR_L_PIN);
  int y = getIRSensorValue(IR_SENSOR_R_PIN);
  // lcdShow(0, 0, x);
  // lcdShow(1, 0, y);
  return y - x;
}

int getEncoderError()
{
  int x = getEncoderL();
  int y = getEncoderR();
  // lcdShow(0, 0, x);
  // lcdShow(1, 0, y);
  return y - x;
}

int getWallError()
{
  return getSideDistance()- walldistance;
}

int getError()
{
  return maze? getWallError() : followTheLane? getIRError() : getEncoderError();
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


