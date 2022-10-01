#include <Servo.h>
#include <NewPing.h>
#include <SoftwareSerial.h>
using namespace std;

SoftwareSerial myB (2,3);//RX,TX

int E1 = 9; //Enable for First motor
int R1 = 4; //Mode 1 for First motor (Forward Mode)
int R2 = 5; //Mode 2 for First motor (Backward Mode)
int E2 = 10;//Enable for Second motor
int L1 = 7; //Mode 1 for Second motor (Forward Mode)
int L2 = 6; //Mode 2 for Second motor (Backward Mode)

//Defining variables for motors' speed
int motorSpeedA = 0;
int motorSpeedB = 0;

//Defining pins of Infrared Radiation sensors and initializing them
const int IR1 = A0;
const int IR2 = A1;
int IR1Val = analogRead(IR1);
int IR2Val = analogRead(IR2); 

//Defining pins of the JoyStick
const int xJoy = A2;
const int yJoy = A3;

//Defining pins and other initial features of Ultrasonic sensors
#define Trig A4
#define Echo A5 
#define Max_Distance 200
int distance = 100;
NewPing sonar(Trig, Echo, Max_Distance); 

//Intitializing the Servo Motor
Servo servo_motor;

char received = '9';

void setup(){
    //Setting the data rate in bits per second (baud) for serial data transmission. 
    Serial.begin(9600);
    myB.begin(9600);
    //Configuration the specified pin to behave either as an input or an output
    pinMode(E1,OUTPUT);
    pinMode(R1,OUTPUT);
    pinMode(R2,OUTPUT);
    pinMode(E2,OUTPUT);
    pinMode(L1,OUTPUT);
    pinMode(L2,OUTPUT);
    //Specifying pin used for Servo motor signal (output) and initiate it 90 degrees (to be forward).
    servo_motor.attach(13);
    servo_motor.write(90);
    //Initializing the Ultrasonic sensor and read its first distance. 
    delay(2000);
    distance = readPing();
    delay(100);
    distance = readPing();
    delay(100);
    distance = readPing();
    delay(100);
    distance = readPing();
    delay(100);
}

int CheckRight(){  
  servo_motor.write(10);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(90);
  return distance;
}

int CheckLeft(){
  servo_motor.write(170);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(90);
  return distance;
  delay(100);
}

int readPing(){
  delay(70);
  int cm = sonar.ping_cm();
  if (cm == 0){
    cm = 250;
  }
  return cm;
}

void Forward() {
  analogWrite(E1, 100);
  analogWrite(E2, 100);
  digitalWrite(R1, HIGH);
  digitalWrite(R2, LOW);
  digitalWrite(L1, LOW);
  digitalWrite(L2, HIGH);
  
}

void Backward() {
  analogWrite(E1, 100);
  analogWrite(E2, 100);
  digitalWrite(R1, LOW);
  digitalWrite(R2, HIGH);
  digitalWrite(L1, HIGH);
  digitalWrite(L2, LOW);
  
}

void Right() {
  analogWrite(E1, 100);
  analogWrite(E2, 100);
  digitalWrite(R1, LOW);
  digitalWrite(R2, HIGH);
  digitalWrite(L1, LOW);
  digitalWrite(L2, HIGH);
  
}

void Left() {
  analogWrite(E1,100);
  analogWrite(E2, 100);
  digitalWrite(R1, HIGH);
  digitalWrite(R2, LOW);
  digitalWrite(L1, HIGH);
  digitalWrite(L2, LOW);
}

void Stop() {
  analogWrite(E1, 0);
  analogWrite(E2, 0);
  digitalWrite(R1, LOW);
  digitalWrite(R2, LOW);
  digitalWrite(L1, LOW);
  digitalWrite(L2, LOW);
}

void LineFollower(){
  while (received == '0')
  {
    if (analogRead(IR1)<200){
      digitalWrite(R1, HIGH);
      digitalWrite(R2, LOW);
      analogWrite(E1, 150);
    }
    else  {
      digitalWrite(R1, LOW);
      digitalWrite(R2, HIGH);
      analogWrite(E1, 150);
      digitalWrite(L1, HIGH);
      digitalWrite(L2, LOW);
      analogWrite(E2, 150);
    }
    if(analogRead(IR2)<200){
      digitalWrite(L1, HIGH);
      digitalWrite(L2, LOW);
      analogWrite(E2, 150);
    }
    else  {
      digitalWrite(R1, HIGH);
      digitalWrite(R2, LOW);
      analogWrite(E1, 150);
      digitalWrite(L1, LOW);
      digitalWrite(L2, HIGH);
      analogWrite(E2, 150);
    }
    Serial.print(analogRead(IR1));
    Serial.print(" ");
    Serial.println(analogRead(IR2));
    //Might need a delay(500); or something like that
    if (myB.available() > 0)// may delete it
    {
      received = myB.read();
    }
  }
}

void ObsatcleAvoiding(){
  while (received == '1')
  {
    Serial.print("Still there ");
    int disRight  = 0;
    int disLeft  = 0;
    delay(1000);
    int distance = sonar.ping_cm();
    Serial.println(distance);
    if (distance == 0) {
      distance = 30;
    }
    if(distance <=25) {
      Serial.println("<25 ");
      Stop();
      delay(300);
      Backward();
      delay(500);
      Stop();
      delay(100);
      disRight  = CheckRight();
      delay(500);
      disLeft  = CheckLeft();
      delay(500);
      int tmpdist = disLeft  - disRight ;
      if (tmpdist >0 || distance >= disLeft )
      {     
        Right();
        delay (1000);
        Forward();
      }
      else {
        Left();
        delay(1000);
        Forward();
      }
    }
    else{
      Forward(); 
      Serial.println("10000000 ");
    }
    distance = readPing();
    if (myB.available() > 0)// may delete it
    {
      received = myB.read();
    }
  }
}

void JoyStick(){
  Serial.println("JoyStick");
  while (received == '2')
  {
    int xAxis = analogRead(xJoy);
    Serial.print("x: ");
    Serial.println(xAxis);
    int yAxis = analogRead(yJoy);
    Serial.print("y: ");
    Serial.println(yAxis);
    // Y-axis used for forward and backward control
    if (yAxis < 470) {
      // Set Motors backward
      digitalWrite(R1, HIGH);
      digitalWrite(R2, LOW);
      digitalWrite(L1, HIGH);
      digitalWrite(L2, LOW);
      // Convert the declining Y-axis readings for going backward from 470 to 0 into 0 to 255 value for the PWM signal for increasing the motor speed
      motorSpeedA = map(yAxis, 470, 0, 0, 255);
      motorSpeedB = map(yAxis, 470, 0, 0, 255);
    }
    else if (yAxis > 550) {
      // Set Motors forward
      digitalWrite(R1, LOW);
      digitalWrite(R2, HIGH);
      digitalWrite(L1, LOW);
      digitalWrite(L2, HIGH);
      // Convert the increasing Y-axis readings for going forward from 550 to 1023 into 0 to 255 value for the PWM signal for increasing the motor speed
      motorSpeedA = map(yAxis, 550, 1023, 0, 255);
      motorSpeedB = map(yAxis, 550, 1023, 0, 255);
    }
    // If joystick stays in middle the motors are not moving
    else {
      motorSpeedA = 0;
      motorSpeedB = 0;
    }
    // X-axis used for left and right control
    if (xAxis < 470) {
      // Set Motor A forward
      digitalWrite(R1, HIGH);
      digitalWrite(R2, LOW);
      // Set Motor B backward
      digitalWrite(L1, LOW);
      digitalWrite(L2, HIGH);
      // Convert the declining Y-axis readings for going backward from 470 to 0 into 0 to 255 value for the PWM signal for increasing the motor speed
      motorSpeedA = map(yAxis, 470, 0, 0, 255);
      motorSpeedB = map(yAxis, 470, 0, 0, 255);
    }
    else if (xAxis > 550) {
      // Set Motor A backward
      digitalWrite(R1, LOW);
      digitalWrite(R2, HIGH);
      // Set Motor B forward
      digitalWrite(L1, HIGH);
      digitalWrite(L2, LOW);
      // Convert the increasing Y-axis readings for going forward from 550 to 1023 into 0 to 255 value for the PWM signal for increasing the motor speed
      motorSpeedA = map(xAxis, 550, 1023, 0, 255);
      motorSpeedB = map(xAxis, 550, 1023, 0, 255);
    }
    analogWrite(E1, motorSpeedA); // Send PWM signal to motor A
    analogWrite(E2, motorSpeedB); // Send PWM signal to motor B
    //Might need delay(1000); or something like that
    if (myB.available() > 0)// may delete it
    {
      received = myB.read();
    }
  }
}

void Manual (){
  while ((received > 50) && (received < 56))
  {
    if (received == '3')
    {
     Forward();
     Serial.print("F");
    }
    else if (received == '4')
    {
      Backward();
    }
    else if (received == '5')
    {
      Right();
    }
    else if (received == '6')
    {
      Left();
    }
    else if (received == '7')
    {
      Stop();
    }
    delay(100);
    Serial.println(received);
    if (myB.available() > 0)
    {
      received = myB.read();
    }
  }
}

void loop(){

    analogWrite(E1, 255);
    analogWrite(E2, 255);
    while (myB.available() == 0)
    {
      Serial.print("Wait");
      Serial.println(received);
    }
    Serial.println("Out");
    if (myB.available() > 0)// may delete it
    {
        received = myB.read();
        Serial.println(received);
        if (received == '0')
        {
          LineFollower();
        }
        else if  (received == '1')
        {
          ObsatcleAvoiding();
        }
        else if (received == '2')
        {
          JoyStick();
        }
        else if ((received > 50) && (received < 56))
        {
          Manual();
        }
        delay(100);
        Serial.println("After loop");
        /*if (myB.available() > 0)
        {
          received = myB.read();
          Serial.print("2nd");
          Serial.println(received);
        }*/
    }
}
