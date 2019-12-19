#include "dht.h"
#define dht_apin A0

dht DHT;
int humid = 0;
int temp = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  DHT.read11(dht_apin);
  humid = DHT.humidity;
  temp = DHT.temperature;
  Serial.print(humid);
  Serial.print(" ");
  Serial.print(temp);
  delay(5000);
}
