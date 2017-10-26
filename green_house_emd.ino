
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

String data;

Servo servoMtr;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.setTimeout(100);
  pinMode(fanPin, OUTPUT);
  pinMode(lightPin, OUTPUT);
  pinMode(pumpPin, OUTPUT);
  pinMode(fliperPin, OUTPUT);
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
   // Serial.println(servoMtr.read());
}

/**
 * light on/off
 */
void lightOnOff(char data){
  if(data == '0'){
    digitalWrite(lightPin, LOW);
  }else if(data == '1'){
    digitalWrite(lightPin, HIGH);
  }
}

/**
 * fan on/off
 */
void fanOnOff(char data){
  if(data == '0'){
    digitalWrite(fanPin, LOW);
  }else if(data == '1'){
    digitalWrite(fanPin, HIGH);
  }
}

/**
 * pump on/off
 */
 void pumpOnOff(char data){
  if(data == '0'){
    digitalWrite(pumpPin, LOW);
  }else if(data == '1'){
    digitalWrite(pumpPin, HIGH);
  }
}

/** 
 * Printing the switches pin status 
 */
void printSwitchStatus(){
    fanStatus = digitalRead(fanPin);
    lightStatus = digitalRead(lightPin);
    pumpStatus = digitalRead(pumpPin);
    if(servoMtr.read()== 0){
      fliperStatus = '0';
    }else{
      fliperStatus = '1';
    }
    
    Serial.println("s"+fliperStatus+lightStatus+fanStatus+pumpStatus+"e");
    delay(2000);
  
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
    delay(2000);
}

/**
 * Humidity and temprature reading
 * 
 */
void getDht11Data(){
  int chk = DHT.read11(DHT11_PIN);
  Serial.println("Humidity: " );
  Serial.print(DHT.humidity, 1);
  Serial.println("Temparature: ");
  Serial.print(DHT.temperature, 1);
  delay(2000); 
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0){
    data = Serial.readString();
    if(data.charAt(0) == 'w' || data.charAt(0) == '*'){
      fliperOpenClose(data.charAt(1));
      lightOnOff(data.charAt(2));
      fanOnOff(data.charAt(3));
      pumpOnOff(data.charAt(4));
      printSwitchStatus();
    } 
  }
 // getDht11Data(); 

 // soilSensorData();
 
}
