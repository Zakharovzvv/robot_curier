#include <Arduino.h>
#include <NewPing.h>

#include <drive.h>
#include <middleware.h>
#include <UZD.h>
#include <header.h>
#include <servoMotor.h>
#include <log.h>
#include <test.h>


// // перемещение банки на другую сторону перекрестка
// void perekrestok()
// {
//   // crossCount++;
//   // finish();
//   // doezd();
//   right();

//   if (uzdF() < DISTANCE_TO_CHECK_OBJECT)
//   {
//   //  moveBankaTake();
//   // moveBankaPut();
//     right();
//   }
//   else
//   {
//     right();
//     right();
//     if (uzdF() < DISTANCE_TO_CHECK_OBJECT)
//     {
//    //   moveBankaTake();
//    //   moveBankaPut();
//       left();
//     }
//     else
//     {
//       right();
//     }
//   }
// }