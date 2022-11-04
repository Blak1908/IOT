//https://www.teachmemicro.com/arduino-pid-control-tutorial/
#include <PID_v1.h>
#include "PinChangeInt.h"  // Thanks to Brett Beauregard for his nice PID library
#define M1 9               // PWM outputs to L298N H-Bridge motor driver module
#define M2 10
#define M3 11  // PWM outputs to L298N H-Bridge motor driver module
#define M4 12

double Setpoint, Input, Output;
pwm = 0;
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

double computePID(double inp){     
        currentTime = millis();                //get current time
        elapsedTime = (double)(currentTime - previousTime);        //compute time elapsed from previous computation
        
        error = Setpoint - inp;                                // determine error
        cumError += error * elapsedTime;                // compute integral
        rateError = (error - lastError)/elapsedTime;   // compute derivative
 
        double out = kp*error + ki*cumError + kd*rateError;                //PID output               
 
        lastError = error;                                //remember current error
        previousTime = currentTime;                        //remember current time
 
        return out;                                        //have function return the PID output
}


void cal_pwm(int out) {  // to H-Bridge board
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


void Auto_Drive_Mode() {

  // Nhấn nút reset trên arduino UNO R3 để reset quá trình chạy theo quỹ đạo tại điểm bắt đầu

  // Lộ trình bắt đầu
  // Xe quay phải 45 độ để bắt đầu lộ trình
  //re phai
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(150);
  dung();
  tien();
  tien();
  delay(300);
  Serial.println("re trai");
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  delay(50);
  dung();
  tien();
  delay(300);
  tien();
  delay(300);
  tien();
  delay(300);
  tien();
  delay(300);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(300);
  dung();
  tien();
  delay(300);
  tien();
  delay(300);
  tien();
  delay(300);
  tien();
  delay(300);
  tien();
  delay(300);
  dung();
  delay(50000);
}
