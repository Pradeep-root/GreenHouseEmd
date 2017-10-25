
#include <dht.h>
#include <Servo.h>

dht DHT;

#define DHT11_PIN 7
#define fanPin 10
#define lightPin 11
#define pumpPin 12
#define fliperPin 3

String fanStatus;
String lightStatus;
String pumpStatus;
String fliperStatus;

String fullData;

int soilSensorPin = A0;
int soilSensorOutPut;

char data = 0;

Servo servoMtr;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  servoMtr.attach(fliperPin);
}

/**
 * servo motor angle
 */

void fliperOpenClose(char data){
  if(data == '0'){
      servoMtr.write(0);
    }else if(data == '1'){
      servoMtr.write(90);
    }
    Serial.println(servoMtr.read());
}

/**
 * Read soil sensor reading
 */
 void soilSensorData(){
    soilSensorOutPut = analogRead(soilSensorPin);
    soilSensorOutPut = constrain(soilSensorOutPut, 485, 1023);// reads the value of the potentiometer (value between 0 and 1023)
    soilSensorOutPut = map(soilSensorOutPut,485,1023,100,0);
    Serial.print(soilSensorOutPut);
    Serial.println("%");
    delay(1000);
}

/** 
 * Printing the switches pin status 
 */
void printSwitchStatus(){
    fanStatus = digitalRead(fanPin);
    lightStatus = digitalRead(lightPin);
    pumpStatus = digitalRead(pumpPin);
    fliperStatus = digitalRead(fliperPin);

    Serial.println("a"+fanStatus+lightStatus+pumpStatus+fliperStatus+"e");
    delay(2000);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0){
    data = Serial.read();
    fliperOpenClose(data);
  }

  soilSensorData();

 //  printSwitchStatus(); 

 
}
