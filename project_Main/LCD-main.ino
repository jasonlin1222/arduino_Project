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


int encoder0PinA = 3;
int encoder0PinB = 4;
int encoder0Pos = 0;
int encoder0PinALast = LOW;
int n = LOW;

void setup() {
  pinMode(Grove_Water_Sensor, 13);
  pinMode (encoder0PinA, INPUT);
  pinMode (encoder0PinB, INPUT);
  // Initiate the LCD:
  lcd.init();
  lcd.backlight();

  dht.begin();
}
void loop() {
    delay(2000);
    n = digitalRead(encoder0PinA);
    if ((encoder0PinALast == LOW) && (n == HIGH)) {
        if (digitalRead(encoder0PinB) == LOW) 
            encoder0Pos--;
        else 
            encoder0Pos++;        
        encoder0PinALast = n;
    }

    int spin = encoder0Pos % 3;
    
    String h = (String)dht.readHumidity();
    String t = (String)dht.readTemperature();
    String w = digitalRead(Grove_Water_Sensor) == LOW ? "Yes water":"No water";

    switch(spin){
        case 0:
            lcd.setCursor(0, 0);
            lcd.print("Humid: " + h );
            lcd.setCursor(0, 1);
            lcd.print("Temp: "+ t);
        case 1:
            lcd.setCursor(0, 0);
            lcd.print("Water: " + w);
        case 2:
            lcd.setCursor(0, 0);
            lcd.print("press button for pump");
            if(button){
                //write relay high
                lcd.serCursor(0, 1);
                lcd print("starting......");
                delay(10000);
                digitalWrite(7, HIGH);
                delay(5000);
                digitalWrite(7,LOW);
                //write relay low
            }
}
