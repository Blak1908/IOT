/*Robot avoiding obstacles*/
/*Programming by Hshop.vn*/
/*
[Read Sensor][run forward] ----->  [detect obstacles <15cm] -----> [run backward for 0.5s] then [turn right 1s] and repeat
*/

#include "dc.h"
#include "UltraSonicDistanceSensor_hshop.h"

/*================== User config ==================*/
unsigned long timeRunBackward = 300;  // 500ms
unsigned long timeTurnRight = 300;  // 1000ms = 1s
int speedRobot = 200; // Min 0, max 255
/*------------------ End user config --------------*/

/*================== define PIN ===================*/
#define IN1             5
#define IN2             4
#define IN3             6
#define IN4             7
/*
OUT1----Left Black
OUT2----Left Red
OUT3----Right Black
OUT4----Right Red
*/

#define TRIGGER_PIN     9
#define ECHO_PIN        8
/*------------------ End define PIN ---------------*/

/*================== Variable declare =============*/
UltraSonicDistanceSensor_hshop  SRF05(TRIGGER_PIN,ECHO_PIN);  // SRF05(triggerPin, echoPin)

DC dcL(IN2, IN1);// dcL(dirPin, pwmPin)
DC dcR(IN4, IN3);

float distance = 0;     //unit cm
bool flagDetectObstacles = false;

/*------------------ End Variable declare ---------*/

void setup() {
  Serial.begin(9600);
  Serial.println(F("Hshop Robot avoiding obstacles start!"));
  dcL.init();
  dcR.init();
}

void loop() {
  readSensor();
  avoidObstacles();
}

void readSensor(){                        // [Read Sensor]
  distance = readUltrasonic();      //unit cm
  Serial.println(distance);
  delay(60);
}

void avoidObstacles(){                    // 
  if(distance <= 15){                     // [detect obstacles]
    flagDetectObstacles = true;
    runStop();                            // stop motor
    delay(100);
    RunBackward(speedRobot);
    delay(timeRunBackward);
    Rotright();
    delay(timeTurnRight);
  }else{
    if(flagDetectObstacles == true){
      flagDetectObstacles = false;        // reset flag
      runStop();                          // stop motor
      delay(100);
      RunForward(speedRobot);
    }else{
      RunForward(speedRobot);
    }
  }
}

void runStop(){
  dcL.forward(0);
  dcR.forward(0);
}

void RunForward(int _speed_) {
  dcL.forward(_speed_);
  dcR.forward(_speed_);
}

void RunBackward(int _speed_) {
  dcL.backward(_speed_);
  dcR.backward(_speed_);
}

void Rotright() {
  dcR.backward(speedRobot);
  dcL.forward(speedRobot);
}
void Rotleft() {
  dcL.backward(speedRobot);
  dcR.forward(speedRobot);
}

float readUltrasonic(){
  return SRF05.measureDistanceCm();
}
