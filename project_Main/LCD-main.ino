#include <Wire.h> // Library for I2C communication
#include <LiquidCrystal_I2C.h> // Library for LCD
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11
#define Grove_Water_Sensor 13
DHT dht(DHTPIN, DHTTYPE);

// Wiring: SDA pin is connected to A4 and SCL pin to A5.
// Connect to LCD via I2C, default address 0x27 (A0-A2 not jumpered)
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2); // Change to (0x27,16,2) for 16x2 LCD.


void setup() {
  pinMode(Grove_Water_Sensor, 13);
  // Initiate the LCD:
  lcd.init();
  lcd.backlight();

  dht.begin();
}
void loop() {
  delay(2000);

  String h = (String)dht.readHumidity();
  String t = (String)dht.readTemperature();
  String w = digitalRead(Grove_Water_Sensor) == LOW ? "Yes water":"No water";
  
  lcd.setCursor(0, 0);
  lcd.print("Humid: " + h );
  lcd.setCursor(0, 1);
  lcd.print("Temp: "+ t);
}
