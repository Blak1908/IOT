#include "dc.h"

DC::DC(unsigned char d, unsigned char p){
    dir=d;
    pwm=p;
 }
 void DC::init(){
     pinMode(dir,1);
 }
 void DC::forward(unsigned char s){
   digitalWrite(dir,1);
   analogWrite(pwm,255-s);
 }
 void DC::backward(unsigned char s){
   digitalWrite(dir,0);
   analogWrite(pwm,s);
 }
