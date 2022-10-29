// Khai báo thư viện cho servo 
#include <Servo.h>
Servo myservo;
//khai báo dữ liệu cho cảm biến
#define trigPin 7
#define echoPin 8

// khai báo các chân kết nổi với module L289n
#define enA 3
#define enB 4
int in1 = 9;
int in2 = 10;
int in3 = 11;
int in4 = 12;
int motorSpeedA = 128;  // set tốc độ xung mặc định cho module
int motorSpeedB = 128;
//Các biến đo khoảng cách phía trước, bên trái, bên phải
float distance_front;
float distance_left;
float distance_right;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT); // Trig sensor
  pinMode(echoPin, INPUT); // Echo sensor
  myservo.attach(6);
  pinMode(enA, OUTPUT); // Output chân enA
  pinMode(enB, OUTPUT); // Output chân enB
  // setup chân điều khiển bánh xe 2 bên trái phải 
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

// Chức năng cho xe đi thẳng
void tien() {
  Serial.println("tien");
  analogWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  delay(300); // giới hạn thời gian cho xe đi thẳng 
  dung();
}

// Chức năng cho xe đi lùi
void lui() {
  Serial.println("lui");
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(300);// giới hạn thời gian cho xe đi lùi 
  dung();
}

// Chức năng cho xe dừng lại
void dung() {
  Serial.println("dung");
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

// Chức năng cho xe rẽ trái
void re_trai() {
  Serial.println("re trai");
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  delay(400);
  dung();
}

// Chức năng cho xe rẽ phải
void re_phai() {
  Serial.println("re phai");
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(400);
  dung();
}

// Servo quay phải
void servo_rotate_right() {
  myservo.write(0);
}

// Servo quay trái
void servo_rotate_left() {
  myservo.write(180);
}

// Servo quay về phía trước 
void servo_rotate_front() {
  myservo.write(90);
}


// Tính khoảng cách với dữ liệu thu được từ cảm biến
float cal_Distance() {
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


// Chức năng xe tự động dò đường và tránh vật cản
void Auto_Drive_Mode() {
  //Đo khoảng cách phía trước
  servo_rotate_front();
  distance_front = cal_Distance();
  Serial.print("Khoang Cach truoc mat: ");
  Serial.print(distance_front);
  Serial.println(" cm");

  if (distance_front >= 15) {
    // Khi phía trước không có vật cản
    tien();
    delay(500);
  } else {
    // Phía trước có vật cản
    dung();
    servo_rotate_right();
    distance_right = cal_Distance();  // Đo khoảng cách bên phải
    Serial.print("Khoang Cach phai: ");
    Serial.print(distance_right);
    Serial.println(" cm");
    delay(500);

    servo_rotate_left();
    distance_left = cal_Distance();  // Đo khoảng cách bên trái
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
    }
  }
}
void loop() {
  // put your main code here, to run repeatedly:
  // Giới hạn xung truyền đến cho L289n từ 128 - 225 (Điều chính tốc độ của bánh xe)
  if (motorSpeedA < 128) {
    motorSpeedA = 0;
  }
  if (motorSpeedB < 128) {
    motorSpeedB = 0;
  }
    if (motorSpeedA > 225) {
    motorSpeedA = 225;
  }
  if (motorSpeedB > 225) {
    motorSpeedB = 225;
  }
  analogWrite(enA, motorSpeedA);
  analogWrite(enB, motorSpeedB);
  Auto_Drive_Mode();
}