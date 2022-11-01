#include "PinChangeInt.h"
#include<PID_v1.h>
#define encodPinA1 2
#define encodPinB1 8 
#define M1 9
#define M2 10

double kp = 5, ki = 1, kd =   0.01, input =0, output= 0, setpoint =0;
long temp;
volatile long encoderPos =0;

PID myPID (&input,&output, &setpoint, kp, ki, kd, DIRECT);

void setup() {
  // put your setup code here, to run once:
  pinMode(encodPinA1, INPUT_PULLUP);
  pinMode(encodPinB1, INPUT_PULLUP);
  attachInterrupt(0, encoder, FALLING);
  myPID.SetMode(AUTOMATIC);
  myPID.SetSampleTime(1);
  myPID.SetOutputLimits(-225,225);
}

void loop() {
  // put your main code here, to run repeatedly:
  temp += analogRead(0);
  if (temp<0) {
    encoderPos =0;
    temp = 0;
  }

  setpoint = temp / 500;
  input = encoderPos;
  myPID.Compute();
  pwmOut(output);

}
void pwmOut(int out){
  if (out >0 )  {
    analogWrite(M1, out);
    analogWrite(M2, 0);
    
  } else {
    analogWrite(M1, 0);
    analogWrite(M2, out);
    }
}
void encoder(){
  if (PINB & 0b00000001) encoderPos++;
  else encoderPos--;
}
