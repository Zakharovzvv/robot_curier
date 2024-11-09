#include <Arduino.h>
#include <drive.h>
#include <middleware.h>
#include <UZD.h>
#include <header.h>
#include <servoMotor.h>
#include <LCD.h>
#include <encoder.h>
#include <log.h>

void testEncoders()
{
    if (logLCD)
    {
        lcdclear();
        lcdShow(0, 8,"EncL", getEncoderL());
        lcdShow(1, 8, "EncR",getEncoderR());
    }
    //  delay(BASE_DELAY);
    if (logConsole)
    {
        consoleLog("EncL", getEncoderL(), "EncR", getEncoderR());
    }
}

void testUZD()
{

    int result_f = getForwardDistance();
    int result_s = getSideDistance();

    if (logLCD)
    {
        lcdclear();
        lcdShow(0, 0, "UZ_F",result_f);
        lcdShow(1, 0, "UZ_S",result_s);
    }
    if (logConsole)
    {
        consoleLog("USD_F", result_f, "USD_S", result_s);
    }
}

void testServo()
{
    lcdShow(0, 10,"Servo");
    closeServo();
    delay(BASE_DELAY);
    openServo();
    lcdclear();
}

void testIsOnBlack()
{
    int result_1 = isOnBlack(IR_SENSOR_L_PIN);
    int result_2 = isOnBlack(IR_SENSOR_M_PIN);
    int result_3 = isOnBlack(IR_SENSOR_R_PIN);
    if (logLCD)
    {
        lcdclear();
        lcdShow(0, 10,"IsOnBlack");
        lcdShow(0, 0, "IR_L",result_1);
        lcdShow(1, 0, "IR_M",result_2);
        lcdShow(1, 8, "IR_R",result_3);
    }
    if (logConsole)
    {
        consoleLog("IR_SENSOR_L", result_1, "IR_SENSOR_M", result_2, "IR_SENSOR_R", result_3, testTime);
    };
    //    delay(BASE_DELAY);
}

void testIRSensors()
{
    int result_1 = getIRSensorValue(IR_SENSOR_L_PIN);
    int result_2 = getIRSensorValue(IR_SENSOR_M_PIN);//getIRSensorValue
    int result_3 = getIRSensorValue(IR_SENSOR_R_PIN);
    if (logLCD)
    {
        lcdclear();
        lcdShow(0, 10,"IR");
        lcdShow(0, 0, "IR_L",result_1);
        lcdShow(1, 0, "IR_M",result_2);
        lcdShow(1, 8, "IR_R",result_3);
    };
    if (logConsole)
    {
    //    consoleLog("IR_SENSOR_L", result_1, "IR_SENSOR_M", result_2, "IR_SENSOR_R", result_3, testTime);
    };
        delay(100);
}

bool testIsOnCross()
{
    int result = isOnCross();
    lcdclear();
    lcdShow(0, 0,"isOnCross", result);
    //    delay(BASE_DELAY);
    return result;
}

void testFullTurn()
{
    turn(4);
    turn(-4);
}

void testGo(int sppedLeft, int sppedRight, unsigned long testTime, const char *text)
{
    lcdShow(0, 10, text);
    startTime = millis();
    unsigned long displayStartTime = 220;
    while (millis() - startTime < testTime)
    {
        go(sppedLeft, sppedRight);
        if (logLCD)
        {
            if (millis() - displayStartTime > DISPLAY_TIME)
            {
                displayStartTime = millis();
                lcdclear();
                lcdShow(0, 0, "sppedL",sppedLeft);
                lcdShow(1, 0, "sppedR",sppedRight);
                testEncoders();
            }
        };
        if (logConsole)
        {
            consoleLog("Speed L", sppedLeft, "Speed R", sppedRight, testTime);
            consoleLog("EncL", getEncoderL(), "EncR", getEncoderR());
        };
    }
    stop();
    lcdclear();
    clearEncoders();
}


void tesDriveWithoutLine(int speed, unsigned long testTime, const char *text)
{
    lcdShow(0, 10, text);
    startTime = millis();
    unsigned long displayStartTime = 220;
    bool temp=followTheLane;
    followTheLane=false;
    while (millis() - startTime < testTime)
    {
        pid(speed);
        if (logLCD)
        {
            if (millis() - displayStartTime > DISPLAY_TIME)
            {
                displayStartTime = millis();
               lcdclear();
            }
        };
        if (logConsole)
        {
            consoleLog("EncL", getEncoderL(), "EncR", getEncoderR());
        };
    }
    stop();
  //  lcdclear();
    clearEncoders();
    followTheLane=temp;
}

void test()
{

    // // ########### 1 Оба колеса вперед  #####################
    // testGo(BASE_SPEED, BASE_SPEED, testTime,"go forward");

    // // ########### 2 Оба колеса назад  #####################
    //  testGo(-BASE_SPEED, -BASE_SPEED, testTime,"go backward");
    // // // ########### 2 Вперед по энкодерам  #####################
    //  tesDriveWithoutLine(BASE_SPEED, testTime,"pid forward");
    // // // ########### 2 Назад по энкодерам  #####################
    //  tesDriveWithoutLine(-BASE_SPEED, testTime,"pid backward");
    // // // ########### 3 ИК сенсоры  #####################
    // startTime = millis();
    // while (millis() - startTime < testTime)
    // {
    //     testIRSensors();
    // }

    //     //########### 4 сервопривод  #####################
    // startTime = millis();
    // while (millis() - startTime < testTime)
    // {
    //     testServo();
    // }

    //   //########### 5 УЗ датчики  #####################
    startTime = millis();
    while (millis() - startTime < testTime)
    {
        testUZD();
    }

    //    //########### 6 На перекрестке #####################
    //         startTime = millis();
    //         while (millis() - startTime < testTime)
    //         {
    //             testIsOnCross();
    //         }
    //         lcdclear();
    //    //########### 7 На черной линии #####################
    //         startTime = millis();
    //         while (millis() - startTime < testTime)
    //         {
    //             testIsOnBlack();
    //         }
    //         lcdclear();
    //   ########### Энкодеры  #####################
    // startTime = millis();
    // while (millis() - startTime < testTime)
    // {
    //     testEncoders();
    // }
    // lcdclear();

    // testFullTurn();
}
