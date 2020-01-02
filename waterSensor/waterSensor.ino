#define Grove_Water_Sensor 13

void setup(){
    pinMode(Grove_Water_Sensor, INPUT);
    Serial.begin(9600);
}

void loop(){
    if(digitalRead(Grove_Water_Sensor) == LOW){
        Serial.print("no water");
    }else{
        Serial.print("yes water");
    }
}
