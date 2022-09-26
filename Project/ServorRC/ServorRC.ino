#include <Servo.h>     
Servo myservo; 

int pos = 0;

void setup() { 
    myservo.attach(9);
} 

void loop() {
     myservo.write(90);
    for(pos = 90; pos >= 45; pos -= 1){ 

        myservo.write(pos);
        delay(15);
    }
    delay(1000);
    
    for(pos = 45; pos < 180; pos+= 1) {                           
        myservo.write(pos);
        delay(15);
    }
    delay(1000);
}
