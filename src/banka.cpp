#include <Arduino.h>
#include <header.h>
#include <middleware.h>
#include <servoMotor.h>
#include <drive.h>
#include <uzd.h>

void moveToTakeObjectOnBlack()
{
  driveToObject();
  closeServo();        // закрываем сервопривод
  driveBackToCross();
  doezd();

  // while (!isOnCross()) // Едем вперед пока не доедем до перекрестка
  // {
  //   preg(BASE_SPEED);
  // }
  // go(0, 0, BASE_DELAY); // Ждем пока закончится импульс инерции
}

void moveToPutObjectOnBlack()
{
  driveSomeDistance(DISTANCE_TO_PUT_BANKA);
  openServo();
  driveBackToCross();
  doezd();
}

void moveObjectNextCross()
{
  while (getForwardDistance() > DISTANCE_TO_CHECK_OBJECT)
  {
    pid();
  }
  moveToTakeObjectOnBlack();
  doezd();
  turn(-1);
}

void MoveObject90grad()
{

  moveToTakeObjectOnBlack();
  turn();
  moveToPutObjectOnBlack();
  turn();
 
}
// перемещение банки на другую сторону перекрестка
void moveObjectFromCross()
{
  // crossCount++;
  // finish();
  // doezd();
  turn(-1);

  if (getForwardDistance() < DISTANCE_TO_CHECK_OBJECT)
  {
    //  moveBankaTake();
    // moveBankaPut();
    turn(2);
    while (getForwardDistance()> DISTANCE_TO_TAKE_OBJECT)
    {
      pid();
    }
    stop();
    driveSomeDistance(5,-BASE_SPEED);
    turn(-1);
    while (!isOnCross())
    {
      pid();
    }
    doezd();
    turn();
  }
  else
  {
    turn();
  }
}

void MoveBankaCross()
{
  turn(-1);
  if (getForwardDistance() < DISTANCE_TO_CHECK_OBJECT)
  {
    while (getForwardDistance() > DISTANCE_TO_TAKE_OBJECT)
    {
      pid(BASE_SPEED);
    }
    stop();
    closeServo();
    turn();
    while (!isOnCross())
    {
      pid(BASE_SPEED);
    }
    // doezd();
    driveSomeDistance(2);
    stop();
    openServo();
    driveSomeDistance(2,-BASE_SPEED);
    stop();
    turn();
    while (!isOnCross())
    {
      pid(BASE_SPEED);
    }
    turn();
  }
  else
  {
    turn();
    if (getForwardDistance() < DISTANCE_TO_CHECK_OBJECT)
    {
      while (getForwardDistance() > DISTANCE_TO_TAKE_OBJECT)
      {
        pid(BASE_SPEED);
      }
      stop();
      closeServo();
      turn();
      while (!isOnCross())
      {
        pid(BASE_SPEED);
      }
      // doezd();
      driveSomeDistance(2);
      stop();
      openServo();
      driveSomeDistance(2,-BASE_SPEED);
      stop();
      turn();
      while (!isOnCross())
      {
        pid(BASE_SPEED);
      }
      turn(-1);
    }
  }
}

bool checkBankaForward()
{
  return getForwardDistance() < DISTANCE_TO_CHECK_OBJECT;
}

bool checkBankaSide()
{
  return getSideDistance() < DISTANCE_TO_CHECK_OBJECT;
}