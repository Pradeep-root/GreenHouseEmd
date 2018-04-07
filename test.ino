
#include <dht.h>
#include <VarSpeedServo.h> 
 
VarSpeedServo myservo; 


dht DHT;

#define DHT11_PIN 7
#define fanPin 8
#define lightPin 9
#define pumpPin 11
#define fliperPin 4

String fanStatus;
String lightStatus;
String pumpStatus;
String fliperStatus;

String fullData;

int soilSensorPin = A0;
int soilSensorOutPut;

String data;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.setTimeout(100);
  pinMode(fanPin, OUTPUT);
  pinMode(lightPin, OUTPUT);
  pinMode(pumpPin, OUTPUT);
  pinMode(fliperPin, OUTPUT);
  digitalWrite(fanPin, HIGH);
  digitalWrite(lightPin, HIGH);
  digitalWrite(pumpPin, HIGH);
  myservo.attach(fliperPin);
  myservo.write(0, 30, true); 
  myservo.detach();
}

/**
 * servo motor angle
 */

void fliperOpenClose(char data){
  myservo.attach(fliperPin);
  if(data == '0'){
     // servoMtr.write(0);
     myservo.write(0, 30, true);
    }else if(data == '1'){
     // servoMtr.write(180);
      myservo.write(180, 30, true);
    }
   // delay(3000);
    myservo.detach();
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
    
    if(myservo.read()== 0){
      fliperStatus = '0';
    }else{
      fliperStatus = '1';
    }
    Serial.println("a"+fliperStatus+lightStatus+fanStatus+pumpStatus+"e");
    delay(2000);
  
}

/**
 * Read soil sensor reading
 */
 String soilSensorData(){
    soilSensorOutPut = analogRead(soilSensorPin);
    soilSensorOutPut = constrain(soilSensorOutPut, 485, 1023);// reads the value of the potentiometer (value between 0 and 1023)
    soilSensorOutPut = map(soilSensorOutPut,485,1023,100,0);
    return String(soilSensorOutPut);
}

/**
 * Humidity and temprature reading
 * 
 */
String getDht11Data(){
  int chk = DHT.read11(DHT11_PIN);
  String humidity = String(DHT.humidity,1);
  String temprature = String(DHT.temperature,1);
 /* Serial.print(DHT.humidity, 1);
  Serial.print(DHT.temperature, 1);
  delay(2000);*/
   return ","+humidity+","+temprature;
}

String concatSensorsData(){
  delay(1000);
  return "s"+soilSensorData()+getDht11Data();
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0){
    data = Serial.readString();
    if(data.charAt(0) == 'w'){
      fliperOpenClose(data.charAt(1));
      lightOnOff(data.charAt(2));
      fanOnOff(data.charAt(3));
      pumpOnOff(data.charAt(4));
      printSwitchStatus();
    } else if(data.charAt(0) == '*'){
       printSwitchStatus();
    }
  }
  Serial.println(concatSensorsData()); 

}
