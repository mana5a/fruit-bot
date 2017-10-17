#include <Servo.h>
Servo myservo;  
int pos = 0;  
int x,y;
int ma1=2,ma2=3,mb1=4,mb2=5;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(ma1,OUTPUT);
pinMode(ma2,OUTPUT);
pinMode(mb1,OUTPUT);
pinMode(mb2,OUTPUT);
pinMode(8,OUTPUT);
pinMode(11,OUTPUT);
digitalWrite(11,LOW);
digitalWrite(8,HIGH);
myservo.attach(9);  
}
void hit() 
{
   for (pos = 90; pos <= 290; pos += 1) { 
    myservo.write(pos);              
    delay(5);                       
  }
  delay(500);
   for (pos = 290; pos >= 90; pos -= 1) { 
    myservo.write(pos);              
    delay(5);                       
  }
  delay(2000);
 
}
void loop() {
  // put your main code here, to run repeatedly:
if (Serial.available() > 0) 
{
    x=Serial.read();
    Serial.println(x);
    switch(x)
    {
      case 's':digitalWrite(ma1,LOW);
               digitalWrite(ma2,LOW);
               digitalWrite(mb1,LOW);
               digitalWrite(mb2,LOW);
               delay(100);
               hit();
               break;
               
      /*case 'R': digitalWrite(ma1,LOW);
               digitalWrite(ma2,HIGH);
               digitalWrite(mb1,LOW);
               digitalWrite(mb2,HIGH);
               delay(10);
               digitalWrite(ma1,HIGH);
               digitalWrite(ma2,LOW);
               digitalWrite(mb1,LOW);
               digitalWrite(mb2,HIGH);
               //delay(10);
               break;
      case 'L':digitalWrite(ma1,LOW);
               digitalWrite(ma2,HIGH);
               digitalWrite(mb1,LOW);
               digitalWrite(mb2,HIGH);
               delay(10);
               digitalWrite(ma1,LOW);
               digitalWrite(ma2,HIGH);
               digitalWrite(mb1,HIGH);
               digitalWrite(mb2,LOW);
               //delay(10);
               break;*/
      case 'r':digitalWrite(ma1,HIGH);
               digitalWrite(ma2,LOW);
               digitalWrite(mb1,LOW);
               digitalWrite(mb2,HIGH);
               //delay(10);
               break;
      case 'l':digitalWrite(ma1,LOW);
               digitalWrite(ma2,HIGH);
               digitalWrite(mb1,HIGH);
               digitalWrite(mb2,LOW);
               //delay(10);
               break;
      case 'f': digitalWrite(ma1,LOW);
               digitalWrite(ma2,HIGH);
               digitalWrite(mb1,LOW);
               digitalWrite(mb2,HIGH);
               //delay(10);
               break;
     case 'b': digitalWrite(ma1,HIGH);
               digitalWrite(ma2,LOW);
               digitalWrite(mb1,HIGH);
               digitalWrite(mb2,LOW);
               break;
       default:digitalWrite(ma1,LOW);
               digitalWrite(ma2,LOW);
               digitalWrite(mb1,LOW);
               digitalWrite(mb2,LOW);
               delay(10);
               break;
    }
  }

}
     

