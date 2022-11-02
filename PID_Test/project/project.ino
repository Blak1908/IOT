//https://www.teachmemicro.com/arduino-pid-control-tutorial/
#include <PID_v1.h>
#include "PinChangeInt.h"  // Thanks to Brett Beauregard for his nice PID library
#define M1 9               // PWM outputs to L298N H-Bridge motor driver module
#define M2 10
#define M3 11  // PWM outputs to L298N H-Bridge motor driver module
#define M4 12

double Setpoint, Input, Output;
 
//Specify the links and initial tuning parameters
double Kp=2, Ki=5, Kd=1;
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
  pwmOut(Output);
}
void pwmOut(int out) {  // to H-Bridge board
  if (out > 0) {
    analogWrite(M1, out);  // drive motor CW
    analogWrite(M2, 0);
    analogWrite(M3, out);  // drive motor CW
    analogWrite(M4, 0);
  } else {
    analogWrite(M1, 0);
    analogWrite(M2, abs(out));
    analogWrite(M3, 0);
    analogWrite(M4, abs(out));  // drive motor CCW
  }
}
