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


int lastChanged = 0;
int encoder0PinA = 5;
int encoder0PinB = 4;
int encoder0Pos = 1;
int previousState = digitalRead(encoder0PinA);
int spin = encoder0Pos % 3;
int previousSpin = 5;
bool changed = false;
String h; 
String t;
String w;

void setup() {
  Serial.begin(9600);
  pinMode(Grove_Water_Sensor, 13);
  pinMode (encoder0PinA, INPUT);
  pinMode (encoder0PinB, INPUT);
  // Initiate the LCD:
  lcd.init();
  lcd.backlight();
  previousState = digitalRead(encoder0PinA);
  dht.begin();
}
void loop() {
    //delay(000);
    lastChanged--;
    if(digitalRead(encoder0PinA) != previousState){
      if(lastChanged <= 0){
        if (digitalRead(encoder0PinB) != digitalRead(encoder0PinA)){
            encoder0Pos--;
            //to make sure that the encoder0Pos does not go below 0 because the spin = (encoder0Pos % 3) which will break the switch statements
            if(encoder0Pos <= 0){
              encoder0Pos = 3;
            }
        }
        else {
            encoder0Pos++;
        }
        //to make sure that when the rotary encoder sends too turning messages but I only turned once, it will only register once
        lastChanged = 100;
        Serial.println(encoder0Pos);
      }
      previousState = digitalRead(encoder0PinA);
    }

    
    //bool button = digitalRead(3);
    spin = encoder0Pos % 3;

    //to put in a variable that is true if the screen needs updates
    changed = false;
    if((String)dht.readHumidity() != h){
      changed = true;
      h = (String)dht.readHumidity();
    }
    if((String)dht.readTemperature() != t){
      changed = true;
      t = (String)dht.readTemperature();
    }
    if((String)(digitalRead(Grove_Water_Sensor) == LOW ? "Yes water":"No water") != w){
      changed = true;
      w = (digitalRead(Grove_Water_Sensor) == LOW ? "Yes water":"No water");
    }

    //to print out the things to the LCD
    switch(spin){
        case 0:
        //to make sure to only update the screen when needed because lcd.print takes a lot of time
        if(previousSpin != 0){
          Serial.println("humid");
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Humid: " + h );
          lcd.setCursor(0, 1);
          lcd.print("Temp: "+ t);
        }else if(changed == true){
          lcd.setCursor(7, 1);
          lcd.print(t);
          lcd.setCursor(6, 1);
          lcd.print(t);
        }
        break;
        
        case 1:
        if(previousSpin != 1){
          Serial.println("water");
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Water: " + w);
        }else if(changed == true){
          lcd.setCursor(7, 0);
          lcd.print(w);
        }
        break;
        
        case 2:
        if(previousSpin != 2){
          Serial.println("button");
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("press button for pump");
        }else if(changed == true){

        }
        
            //button does not work as intended. Don't know what is going on with the input from the button, it flashes true when i touch the rotary encoder but didn't press it.
            /*if(button){
                //write relay high
                lcd.setCursor(0, 1);
                lcd.print("starting......");
                delay(10000);
                digitalWrite(7, HIGH);
                delay(5000);
                digitalWrite(7,LOW);
                //write relay low
            }*/
        break;
    }
    previousSpin = spin;
}
