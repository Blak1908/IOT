#include <Servo.h>
#include <IRremote.h>        // thư viện hỗ trợ IR remote
const int receiverPin = 5;   // chân digital 5 dùng để đọc tín hiệu
IRrecv irrecv(receiverPin);  // tạo đối tượng IRrecv mới
decode_results results;      // lưu giữ kết quả giải mã tín hiệu
#define trigPin 7
#define echoPin 8

int in1 = 9;
int in2 = 10;
int in3 = 11;
int in4 = 12;
int distance_front;
int distance_left;
int distance_right;
Servo myservo;
int enB = 2;
int enA = 3;

int motorSpeedA = 10;
int motorSpeedB = 10;
int pos = 0;
void setup() {
  // put your setup code here, to run once:
  irrecv.enableIRIn();  // start the IR receiver
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  myservo.attach(6);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
}

void tien() {
  analogWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}
void lui() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(500);
  dung();
}
void dung() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void re_trai() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  delay(400);
  dung();
}

void re_phai() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(400);
  dung();
}

int cal_Distance() {
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

void servo_rotate_right() {
  myservo.write(0);
}


void servo_rotate_left() {
  myservo.write(180);
}

void servo_rotate_front() {
  myservo.write(90);
}

void translateIR() {
  switch (results.value) {
    case 4294967295:
      tien();
      break;
    case 16748655:
      re_phai();
      break;
    case 16750695:
      lui();
      break;
    case 16769055:
      re_trai();
      break;
    case 16754775:
      dung();
      break;
    case 16720605:
      Auto_Drive_Mode();
      break;
  }
}

void Auto_Drive_Mode() {
  boolean stops = false;
  while (stops = true) {
    servo_rotate_front();
    distance_front = cal_Distance();
    Serial.print("Khoang Cach truoc mat: ");
    Serial.print(distance_front);
    Serial.println(" cm");
    if (distance_front >= 10) {
      analogWrite(enA, motorSpeedA);  // Send PWM signal to motor A
      analogWrite(enB, motorSpeedB);  // Send PWM signal to motor B
      tien();
    } else {
      dung();
      servo_rotate_right();
      distance_right = cal_Distance();
      Serial.print("Khoang Cach phai: ");
      Serial.print(distance_right);
      Serial.println(" cm");
      delay(500);
      servo_rotate_left();
      distance_left = cal_Distance();
      Serial.print("Khoang Cach trai: ");
      Serial.print(distance_left);
      Serial.println(" cm");

      if (distance_right >= 7 && distance_right > distance_left) {
        re_phai();
        delay(500);
      } else if (distance_left >= 7) {
        re_trai();
        delay(500);
      } else {
        lui();
        delay(500);
      }
    }

    if (irrecv.decode(&results))  // nếu nhận được tín hiệu
    {
      if (results.value == 16754775) {
        servo_rotate_front();
        break;
      }
      Serial.println(results.value, DEC);
      delay(200);
      irrecv.resume();  // nhận giá trị tiếp theo
    }
  }
}



void loop() {
  servo_rotate_front();
  if (irrecv.decode(&results))  // nếu nhận được tín hiệu
  {
    translateIR();
    Serial.println(results.value, DEC);
    delay(200);
    irrecv.resume();  // nhận giá trị tiếp theo
  } else {
    dung();
  }
}