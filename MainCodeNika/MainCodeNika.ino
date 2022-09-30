#include <Servo.h>
#include <NewPing.h>
#include <SoftwareSerial.h>
using namespace std;

SoftwareSerial myB (13,12);//RX,TX//need to change any Serial. to myB.

int I1 = 3;
int R1 = 4;
int R2 = 2;
int I2 = 6;
int L1 = 7;
int L2 = 5;
int beep = 9;
int detect = 8;
int armUP = 10;
int armOPEN = 11;

Servo servoUP;
Servo servoOPEN;

void setup(){

    Serial.begin(9600);
    myB.begin(9600);
    //pinMode(rxd,INPUT);
    //pinMode(txd,INPUT);
    pinMode(I1,OUTPUT);
    pinMode(R1,OUTPUT);
    pinMode(R2,OUTPUT);
    pinMode(I2,OUTPUT);
    pinMode(L1,OUTPUT);
    pinMode(L2,OUTPUT);
    pinMode(beep,OUTPUT);
    pinMode(detect,INPUT);
    servoUP.attach(10);
    servoOPEN.attach(11);  
    //servoUP.write(90);
}

void Stop(){

    digitalWrite(R1, LOW);
    digitalWrite(L1, LOW);
    digitalWrite(R2, LOW);
    digitalWrite(L2, LOW);
}

void Forward(){

    digitalWrite(L1, HIGH);
    digitalWrite(R1, HIGH);
    digitalWrite(L2, LOW);
    digitalWrite(R2, LOW);
}

void Backward(){

    digitalWrite(L2, HIGH);
    digitalWrite(R2, HIGH);
    digitalWrite(L1, LOW);
    digitalWrite(R1, LOW);
}

void ManualRight(){

    digitalWrite(L1, HIGH);
    digitalWrite(R2, HIGH);
    digitalWrite(L2, LOW);
    digitalWrite(R1, LOW);
}

void ManualLeft(){

    digitalWrite(L2, HIGH);
    digitalWrite(R1, HIGH);
    digitalWrite(L1, LOW);
    digitalWrite(R2, LOW);
}


void loop(){

    digitalWrite(beep,LOW);
    analogWrite(I1, 255);
    analogWrite(I2, 255);
    //detect = digitalRead(7);
    while (myB.available() == 0)
    {
      Serial.print("Wait");
    }
    if (myB.available() > 0)// may delete it
    {
        char received = myB.read();
        Serial.println(received);
        if (received == '0')
        {
          servoUP.write(0);
        }
        else if  (received == '1')
        {
          servoUP.write(90);
        }
        else if (received == '2')
        {
          //detect???
          Forward();
        }
        else if (received == '3')
        {
          Backward();
        }
        else if (received == '4')
        {
          ManualRight();
        }
        else if (received == '5')
        {
          ManualLeft();
        }
        else if (received == '6')
        {
          Stop();
        }
        else if (received == '7')
        {
          servoOPEN.write(180);
        }
        else if (received == '8')
        {
          servoOPEN.write(50);
        }
        delay(100);
        /*if (myB.available() > 0)
        {
          received = myB.read();
          Serial.print("2nd");
          Serial.println(received);
        }*/
    }
}
