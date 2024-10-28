#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Arduino.h>
#include <header.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void initLCD()
{
  lcd.init();
  lcd.backlight();
  // lcd.setCursor(0, 0);        // Устанавливаем курсор на первую строку, первый символ
  // lcd.print("Hello, world!");
}

void lcdclear()
{
  lcd.clear();
}

void lcdShow(int x, int y, float number)
{
    lcd.setCursor(y, x);
    lcd.print(number);

}
