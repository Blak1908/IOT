/**********************************************************************************
 *  Code for ESP8266 (ESP01). (Smart Relay V5)
 *  TITLE: Arduino ESP8266 control Relay Module with Blynk, IR remote, Manual Switch, DHT11 Sensor and LDR| Real-Time Feedback
 *  Click on the following links to learn more. 
 *  YouTube Video: https://youtu.be/mZrQpLq0KMk
 *  Related Blog : https://easyelectronicsproject.com/projects/arduino-projects/
 *  by Tech StudyCell
 **********************************************************************************/
/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

 *************************************************************
  Note: This requires ESP8266 support package:
    https://github.com/esp8266/Arduino

  Please be sure to select the right ESP8266 module
  in the Tools -> Board menu!

  Change WiFi ssid, pass, and Blynk auth token to run :)
 *************************************************************/

/* Comment this out to disable prints and save space */
//#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

int pinState = 0; 

#define VPIN_BUTTON_1    V1 
#define VPIN_BUTTON_2    V2
#define VPIN_BUTTON_3    V3 
#define VPIN_BUTTON_4    V4
#define VPIN_BUTTON_5    V5
#define VPIN_BUTTON_6    V6
#define VPIN_TEMPERATURE V7
#define VPIN_HUMIDITY    V8

// You should get Auth Token in the Blynk App.
char auth[] = "AUTH TOKEN";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "WIFI NAME";
char pass[] = "WIFI PASSWORD";

bool connectedFlag = false;
String pinStatus ;

// When App button is pushed - switch the state
BLYNK_WRITE(VPIN_BUTTON_1) {  
  pinState = param.asInt();
  if(pinState == 1){
    Serial.write('A');
  }
  else if(pinState == 0){
    Serial.write('a');
  }   
}

BLYNK_WRITE(VPIN_BUTTON_2) {  
  pinState = param.asInt();
  if(pinState == 1){
    Serial.write('B');
  }
  else if(pinState == 0){
    Serial.write('b');
  }  
}

BLYNK_WRITE(VPIN_BUTTON_3) {  
  pinState = param.asInt();
  if(pinState == 1){
    Serial.write('C');
  }
  else if(pinState == 0){
    Serial.write('c');
  }  
}

BLYNK_WRITE(VPIN_BUTTON_4) {  
  pinState = param.asInt();
  if(pinState == 1){
    Serial.write('D');
  }
  else if(pinState == 0){
    Serial.write('d');
  }  
}
BLYNK_WRITE(VPIN_BUTTON_5) {  
  pinState = param.asInt();
  if(pinState == 1){
    Serial.write('E');
  }
  else if(pinState == 0){
    Serial.write('e');
  }  
}

void updateState(String state){
  if (state.substring(0,1) == "A"){
    Blynk.virtualWrite(VPIN_BUTTON_1, HIGH);
  }
  else{
    Blynk.virtualWrite(VPIN_BUTTON_1, LOW);
  }

  if (state.substring(1,2) == "B"){
    Blynk.virtualWrite(VPIN_BUTTON_2, HIGH);
  }
  else{
    Blynk.virtualWrite(VPIN_BUTTON_2, LOW);
  }

  if (state.substring(2,3) == "C"){
    Blynk.virtualWrite(VPIN_BUTTON_3, HIGH);
  }
  else{
    Blynk.virtualWrite(VPIN_BUTTON_3, LOW);
  }
  
  if (state.substring(3,4) == "D"){
    Blynk.virtualWrite(VPIN_BUTTON_4, HIGH);
  }
  else{
    Blynk.virtualWrite(VPIN_BUTTON_4, LOW);
  }
  if (state.substring(4,5) == "E"){
    Blynk.virtualWrite(VPIN_BUTTON_5, HIGH);
  }
  else{
    Blynk.virtualWrite(VPIN_BUTTON_5, LOW);
  }
  if (state.substring(5,6) == "1"){
    Blynk.virtualWrite(VPIN_BUTTON_6, HIGH);
  }
  else{
    Blynk.virtualWrite(VPIN_BUTTON_6, LOW);
  }
  
  Blynk.virtualWrite(VPIN_TEMPERATURE, state.substring(6,11));
  Blynk.virtualWrite(VPIN_HUMIDITY, state.substring(11,16));
}

void setup()
{
  // Debug console
  Serial.begin(9600);
  
  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  while(Serial.available()) 
  {
    pinStatus = Serial.readString();
    updateState(pinStatus);
    connectedFlag = true;
  }
  if (connectedFlag){  
    Blynk.run();
  }
}

