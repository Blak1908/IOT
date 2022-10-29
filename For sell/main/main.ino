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
int motorSpeedA = 225;  // set tốc độ xung mặc định cho module
int motorSpeedB = 225;
//Các biến đo khoảng cách phía trước, bên trái, bên phải
float distance_front;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);  // Trig sensor
  pinMode(echoPin, INPUT);   // Echo sensor
  pinMode(enA, OUTPUT);      // Output chân enA
  pinMode(enB, OUTPUT);      // Output chân enB
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
  delay(300);  // giới hạn thời gian cho xe đi thẳng
  dung();
}

// Chức năng cho xe đi lùi
void lui() {
  Serial.println("lui");
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(300);  // giới hạn thời gian cho xe đi lùi
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
  delay(450);
  dung();
}

// Chức năng cho xe rẽ phải
void re_phai() {
  Serial.println("re phai");
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(450);
  dung();
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

void tien_co_kiem_soat_phai() {
  while (true) {
    Serial.println("tien");
    tien();
    delay(300);
    distance_front = cal_Distance();
    if (distance_front <= 10) {
      dung();
      delay(500);
      re_phai();
      break;
    }
  }
}
void tien_co_kiem_soat_trai() {
  while (true) {
    Serial.println("tien");
    tien();
    delay(300);
    distance_front = cal_Distance();
    if (distance_front <= 10) {
      dung();
      delay(500);
      re_trai();
      break;
    }
  }
}

// Chức năng xe tự động dò đường và tránh vật cản
void Auto_Drive_Mode() {
  analogWrite(enA, motorSpeedA);
  analogWrite(enB, motorSpeedB);
  tien_co_kiem_soat_phai();
  delay(300);
  tien_co_kiem_soat_trai();
  delay(300);
  tien();
  delay(300);
  tien();
  delay(300);
  re_phai();
  delay(300);
  tien_co_kiem_soat_trai();
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
void loop() {
  // put your main code here, to run repeatedly:
  // Giới hạn xung truyền đến cho L289n từ 128 - 225 (Điều chính tốc độ của bánh xe)
  Auto_Drive_Mode();
}