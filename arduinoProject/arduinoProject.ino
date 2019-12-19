#include <Wire.h>

#include "LCD.h" // For LCD
#include "LiquidCrystal_I2C.h" // Added library*
//Set the pins on the I2C chip used for LCD connections
//ADDR,EN,R/W,RS,D4,D5,D6,D7
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7); // 0x27 is the default I2C bus address of the backpack-see article
void setup()
{
   // Set off LCD module
   lcd.begin (16,2); // 16 x 2 LCD module
   lcd.setBacklightPin(9,POSITIVE); // BL, BL_POL
   lcd.setBacklight(HIGH);
}
void loop()
{
   lcd.home (); // Set cursor to 0,0
   lcd.print("protolabz"); // Custom text
   lcd.setCursor (0,1); // Go to home of 2nd line
   lcd.print(millis());
   delay(1000); // Blinks of backlight
   lcd.setBacklight(LOW); // Backlight off
   delay(500);
   lcd.setBacklight(HIGH); // Backlight on
   delay(1000);
}
