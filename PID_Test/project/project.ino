//https://www.teachmemicro.com/arduino-pid-control-tutorial/
#include <PID_v1.h>
#include "PinChangeInt.h"  // Thanks to Brett Beauregard for his nice PID library

#define M1 9               // PWM outputs to L298N H-Bridge motor driver module
#define M2 10
#define M3 11  // PWM outputs to L298N H-Bridge motor driver module
#define M4 12
#define enA 3
#define enB 4

int motorSpeedA;  // set tốc độ xung mặc định cho chân enA
int motorSpeedB; // set tốc độ xung mặc định cho chân enB

double Setpoint, Input, Output;
double pwm = 0;
//Specify the links and initial tuning parameters
double Kp = 2, Ki = 5, Kd = 1;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

void setup() {
  Input = analogRead(A0);
  Setpoint = 100;

  myPID.SetMode(AUTOMATIC);
  Serial.begin(9600);
}
void loop() {
  Input = analogRead(A0);
  Serial.println(Input);
  myPID.Compute();
  cal_pwm(Output);
}



void cal_pwm(int out) {  // to H-Bridge board
  motorSpeedA = out;
  motorSpeedB = out;
  analogWrite(enA, motorSpeedA); // set tốc độ cho chân enA
  analogWrite(enB, motorSpeedB); // set tốc độ cho chân enB
  if (out > 0) {
    digitalWrite(M1, HIGH);  // drive motor CW
    digitalWrite(M2, LOW);
    digitalWrite(M3, HIGH);  // drive motor CW
    digitalWrite(M4, LOW);
  } else {
    digitalWrite(M1, LOW);  // drive motor CW
    digitalWrite(M2, LOW);
    digitalWrite(M3, LOW);  // drive motor CW
    digitalWrite(M4, LOW);
  }
}

void Stop(){
  analogWrite(M1, 0);  
  analogWrite(M2, 0);
  analogWrite(M3, 0);  
  analogWrite(M4, 0);
}

void run_forward() {
  analogWrite(M1, 0);  
  analogWrite(M2, pwm);
  analogWrite(M3, 0);  
  analogWrite(M4, pwm);
}

void run_back(){
  analogWrite(M1, pwm);  
  analogWrite(M2, 0);
  analogWrite(M3, pwm);  
  analogWrite(M4, 0);
}

void run_left(){
  analogWrite(M1, pwm);  
  analogWrite(M2, 0);
  analogWrite(M3, 0);  
  analogWrite(M4, pwm);
}

void run_right(){
  analogWrite(M1, 0);  
  analogWrite(M2, pwm);
  analogWrite(M3, pwm);  
  analogWrite(M4, 0);
}
