#include<Servo.h>
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
String reading;
int t=90;
void limit(int x){
  if(x>180){x=180;}
  else if(x<0){x=0;}
  servo3.write(x);
  };
void setup() {
  // put your setup code here, to run once:
servo1.attach(2);
servo2.attach(3);
servo3.attach(12);
servo4.attach(13);
servo1.write(90);
servo2.write(90);
servo3.write(90);
servo4.write(180);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()>0){
    reading=Serial.readString();
    if(reading=="L"){servo1.write(107);}
    else if(reading=="R"){servo1.write(76);}
    else if(reading=="U"){servo2.write(60);}
    else if(reading=="D"){servo2.write(102);}
    else if(reading=="stop"){servo1.write(90);servo2.write(90);}
    else if(reading=="AU"){t=t+10;limit(t);}
    else if(reading=="AD"){t=t-10;limit(t);}
    else if(reading=="open"){servo4.write(180);}
    else if(reading=="close"){servo4.write(0);}
    }

}
