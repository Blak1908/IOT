//khai báo dữ liệu cho cảm biến
#define trigPin 7
#define echoPin 8

// khai báo các chân kết nổi với module L289n

int in1 = 9;
int in2 = 10;
int in3 = 11;
int in4 = 12;


//Biến đo khoảng cách phía trước

float distance_front;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);  // Trig sensor
  pinMode(echoPin, INPUT);   // Echo sensor
  // setup chân điều khiển bánh xe 2 bên trái phải
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

// Chức năng cho xe đi thẳng
void tien() {
  Serial.println("tien");
  digitalWrite(in1, LOW);
  analogWrite(in2, 100+70);
  digitalWrite(in3, LOW);
  analogWrite(in4,100-70);
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
  delay(300);
  dung();
}

// Chức năng cho xe rẽ phải
void re_phai(){
  Serial.println("re phai");
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(300);
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

// Tiến về phía trước và chỉ rẻ phải khi có vật cản
void tien_co_kiem_soat_phai() {
  while (true) {
    Serial.println("tien");
    tien();
    delay(300);
    distance_front = cal_Distance();
    if (distance_front <= 3) {
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
    if (distance_front <= 3) {
      dung();
      delay(500);
      re_trai();
      break;
    }
  }
}



// Chức năng cho xe đi theo quỹ đạo tọa độ (10,10) đến (110,110)
void Auto_Drive_Mode1() {

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

// Chức năng cho xe đi theo quỹ đạo tọa độ (10,10) đến (10,110)
void Auto_Drive_Mode2() {

  // Nhấn nút reset trên arduino UNO R3 để reset quá trình chạy theo quỹ đạo tại điểm bắt đầu

  // Lộ trình bắt đầu
  tien_co_kiem_soat_phai();
  delay(400);
  tien();
  re_trai();
  tien_co_kiem_soat_trai();
  tien();
  dung(); 
  delay(50000);
}

// Chức năng cho xe đi theo quỹ đạo tọa độ (10,10) đến (110,10)
void Auto_Drive_Mode3() {

  // Nhấn nút reset trên arduino UNO R3 để reset quá trình chạy theo quỹ đạo tại điểm bắt đầu

  // Lộ trình bắt đầu
  re_phai();
  tien_co_kiem_soat_trai();
  delay(400);
  tien();
  tien();
  tien();
  tien();
  re_phai();
  tien();
  tien();
  tien();
  tien_co_kiem_soat_trai();
  dung();
  delay(50000);
}




void loop() {
  // Nhấn nút reset trên arduino UNO R3 để reset quá trình chạy theo quỹ đạo tại điểm bắt đầu
  // put your main code here, to run repeatedly:

}

