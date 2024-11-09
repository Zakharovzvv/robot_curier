
#include <Arduino.h>

void logInit()
{
    Serial.begin(9600); // Only using Serial when not debugging!
}

// Версия с одним набором параметров
void consoleLog(const char *text1, float value1, int interval = 500)
{
    Serial.print(text1);
    Serial.print(" : ");
    Serial.println(value1, 2);
}

// Версия с двумя наборами параметров
void consoleLog(const char *text1, float value1, const char *text2, float value2, int interval = 500)
{
    Serial.print(text1);
    Serial.print(" : ");
    Serial.print(value1, 2);
    Serial.print("  ");
    Serial.print(text2);
    Serial.print(" : ");
    Serial.println(value2, 2);
}

void consoleLog(const char *text1, float value1, const char *text2, float value2, const char *text3, float value3, int interval = 500)
{

    Serial.print(text1);
    Serial.print(" : ");
    Serial.print(value1,2);
    Serial.print("  ");
    Serial.print(text2);
    Serial.print(" : ");
    Serial.print(value2,2);
    Serial.print("  ");
    Serial.print(text3);
    Serial.print(" : ");
    Serial.println(value3,2);
}
void consoleLog(const char *text1, float value1, const char *text2, float value2, const char *text3, float value3, const char *text4, float value4,  int interval = 500)
{

    Serial.print(text1);
    Serial.print(" : ");
    Serial.print(value1,2);
    Serial.print("  ");
    Serial.print(text2);
    Serial.print(" : ");
    Serial.print(value2,2);
    Serial.print("  ");
    Serial.print(text3);
    Serial.print(" : ");
    Serial.print(value3,2);
    Serial.print("  ");
    Serial.print(text4);
    Serial.print(" : ");
    Serial.println(value4,2);
}