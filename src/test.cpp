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
        lcdShow(0, 0, getEncoderL());
        lcdShow(1, 0, getEncoderR());
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
        lcdShow(0, 0, result_f);
        lcdShow(1, 0, result_s);
    }
    if (logConsole)
    {
        consoleLog("USD_F", result_f, "USD_S", result_s);
    }
}

void testServo()
{
    closeServo();
    delay(BASE_DELAY);
    openServo();
}

void testIsOnBlack()
{
    int result_1 = isOnBlack(IR_SENSOR_L_PIN);
    int result_2 = isOnBlack(IR_SENSOR_M_PIN);
    int result_3 = isOnBlack(IR_SENSOR_R_PIN);
    if (logLCD)
    {
        lcdShow(0, 0, result_1);
        lcdShow(1, 0, result_2);
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
    int result_2 = getIRSensorValue(IR_SENSOR_M_PIN);
    int result_3 = getIRSensorValue(IR_SENSOR_R_PIN);
    if (logLCD)
    {
        lcdclear();
        lcdShow(0, 15, 2);
        lcdShow(0, 0, result_1);
        lcdShow(1, 0, result_2);
    };
    if (logConsole)
    {
        consoleLog("IR_SENSOR_L", result_1, "IR_SENSOR_M", result_2, "IR_SENSOR_R", result_3, testTime);
    };
    //    delay(BASE_DELAY);
}
void testIRSensorsAnalogRead()
{
    int result_1 = analogRead(IR_SENSOR_L_PIN);
    int result_2 = analogRead(IR_SENSOR_R_PIN);
    lcdShow(0, 0, result_1);
    lcdShow(1, 0, result_2);
    //    delay(BASE_DELAY);
}

void testIsOnCross()
{
    int result_1 = isOnCross();
    lcdShow(0, 0, result_1);
    //    delay(BASE_DELAY);
}

void testFullTurn()
{
    turn(4);
    turn(-4);
}

void testDrive(int sppedLeft, int sppedRight, unsigned long testTime)
{
    lcdShow(0, 15, 1);
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
                lcdShow(0, 0, sppedLeft);
                lcdShow(1, 0, sppedRight);
                lcdShow(0, 8, getEncoderL());
                lcdShow(1, 8, getEncoderR());
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

void test()
{

    // ########### 1 Оба колеса вперед  #####################
    testDrive(BASE_SPEED, BASE_SPEED, testTime);

    // ########### 2 Оба колеса назад  #####################
    testDrive(-BASE_SPEED, -BASE_SPEED, testTime);

    // // ########### 3 ИК сенсоры  #####################
    // lcdShow(0, 15, 3);
    // startTime = millis();
    // while (millis() - startTime < testTime)
    // {
    //     testIRSensors();
    // }
    // lcdclear();

    //     //########### 4 сервопривод  #####################
    // lcdShow(0, 15, 4);
    // startTime = millis();
    // while (millis() - startTime < testTime)
    // {
    //     testServo();
    // }
    // lcdclear();

    //   //########### 5 УЗ датчики  #####################
    // lcdShow(0, 15, 5);
    // startTime = millis();
    // while (millis() - startTime < testTime)
    // {
    //     testUZD();
    // }
    // lcdclear();
    //    //########### 6 На перекрестке #####################
    //         lcdShow(0, 15, 6);
    //         startTime = millis();
    //         while (millis() - startTime < testTime)
    //         {
    //             testIsOnCross();
    //         }
    //         lcdclear();
    //    //########### 7 На черной линии #####################
    //         lcdShow(0, 15, 7);
    //         startTime = millis();
    //         while (millis() - startTime < testTime)
    //         {
    //             testIsOnBlack();
    //         }
    //         lcdclear();
    //   ########### Энкодеры  #####################
    // lcdShow(0, 15, 8);
    // startTime = millis();
    // while (millis() - startTime < testTime)
    // {
    //     testEncoders();
    // }
    // lcdclear();

    // testFullTurn();
    //    testIRSensorsAnalogRead();
    //    testEncoders();
}
