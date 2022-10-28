#include <Servo.h>
Servo myservo;
//khai báo dữ liệu cho cảm biến 
#define trigPin 7 
#define echoPin 8

// khai báo các chân kết nổi với module L289n
#define enA 4 
#define enB 5
int in1 = 9;
int in2 = 10;
int in3 = 11;
int in4 = 12;
int pwmOutput = 50; // set tốc độ xung mặc định cho module

//Các biến đo khoảng cách phía trước, bên trái, bên phải
float distance_front;
float distance_left;
float distance_right;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  myservo.attach(6);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}


void tien() {
  analogWrite(enA, pwmOutput);
  analogWrite(enA, pwmOutput);
  analogWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}
void lui() {
  analogWrite(enA, pwmOutput);
  analogWrite(enA, pwmOutput);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(500);
  dung();
}
void dung() {
  analogWrite(enA, pwmOutput);
  analogWrite(enA, pwmOutput);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void re_trai() {
  analogWrite(enA, pwmOutput);
  analogWrite(enA, pwmOutput);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  delay(400);
  dung();
}

void re_phai() {
  analogWrite(enA, pwmOutput);
  analogWrite(enA, pwmOutput);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(400);
  dung();
}
void servo_rotate_right() {
  myservo.write(0);
}

void servo_rotate_left() {
  myservo.write(180);
}

void servo_rotate_front() {
  myservo.write(90);
}


float cal_Distance() {
  // tính khoảng cách với dữ liệu thu được từ cảm biến 
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;
  return distance;
}

boolean isRightCanMove(int right, int left) {
  if (right > left) {
    return true;
  }
  return false;
}


void make_decision(int right, int left) {
  if (isRightCanMove(right, left)) {
    re_phai();
  } else {
    re_trai();
  }
}

void Auto_Drive_Mode() {
  servo_rotate_front();
  distance_front = cal_Distance();
  Serial.print("Khoang Cach truoc mat: ");
  Serial.print(distance_front);
  Serial.println(" cm");

  if (distance_front >= 7) {
    // khi phía trước không có vật cản 
    tien();
  } else {
    // phía trước có vật cản 
    dung();
    servo_rotate_right();
    distance_right = cal_Distance();  // đo khoảng cách bên phải 
    Serial.print("Khoang Cach phai: ");
    Serial.print(distance_right);
    Serial.println(" cm");
    delay(500);

    servo_rotate_left();
    distance_left = cal_Distance();  // đo khoảng cách bên trái
    Serial.print("Khoang Cach trai: ");
    Serial.print(distance_left);
    Serial.println(" cm");

    if (distance_right >= 10) {
      // Trường hợp bên phải không có vật cản 
      re_phai();
      delay(500);
    } else if (distance_left >= 10) {
      // Bên trái không có vật cản 
      re_trai();
      delay(500);
    } else {
      // Bên phải, bên trái và phía trước đều có vật cản 
      lui();
      dung();
      servo_rotate_right();
      distance_right = cal_Distance();  // đo khoảng cách bên phải 
      Serial.print("Khoang Cach phai: ");
      Serial.print(distance_right);
      Serial.println(" cm");
      delay(500);

      servo_rotate_left();
      distance_left = cal_Distance();  // đo khoảng cách bên trái
      Serial.print("Khoang Cach trai: ");
      Serial.print(distance_left);
      Serial.println(" cm");
      // Đưa ra quyết định rẻ trái hay phải
      make_decision(distance_right, distance_left);
      delay(500);
    }
  }
}
void loop() {
  // put your main code here, to run repeatedly:
}