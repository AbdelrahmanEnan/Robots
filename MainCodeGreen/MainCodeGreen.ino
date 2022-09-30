#include <Servo.h>
#include <NewPing.h>
#include <SoftwareSerial.h>
using namespace std;
SoftwareSerial myB (2,3);//RX,TX
//Motor 1
const int enable1 = 6;  // enable for motor 1                                                               
const int motor11 = 4; // motor 1 moving forward 
const int motor12 = 5; // motor 1 moving backwards
//Motor 2
const int enable2 = 9; // enable for motor 2
const int motor21 = 8;  // motor 2 moving forward
const int motor22 = 7;  // motor 2 moving backward

int motorSpeedA = 0;
int motorSpeedB = 0;
//Defining variable for the speed of the motor
int motorSpeed = 0;
//Defining two of the ir sensors as ir1 and ir2
const int infraRed1 = A0;
const int infraRed2 = A1;
//Defining values from the two ir sensors
int infraRed1Val = analogRead(infraRed1);
int infraRed2Val = analogRead(infraRed2); 

const int xJoy = A2;
const int yJoy = A3;

#define Trig A4
#define Echo A5 
#define Max_Distance 200
int distance = 100;
NewPing sonar(Trig, Echo, Max_Distance); 

Servo servo_motor;

char received = '9';

char t;
char temp = '0';

void setup(){

    Serial.begin(9600);
    myB.begin(9600);
    pinMode(enable1, OUTPUT); // initialize ENA pin as an output
    pinMode(enable2, OUTPUT); // initialize ENB pin as an output
    pinMode(motor11, OUTPUT); // initialize MOTOR_A1 pin as an output
    pinMode(motor12, OUTPUT); // initialize MOTOR_A2 pin as an output
    pinMode(motor21, OUTPUT); // initialize MOTOR_B1 pin as an output
    pinMode(motor22, OUTPUT); // initialize MOTOR_B2 pin as an output
    servo_motor.attach(13);
    servo_motor.write(90);
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

int lookRight(){  
  servo_motor.write(10);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(90);
  return distance;
}

int lookLeft(){
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
  if (cm==0){
    cm=250;
  }
  return cm;
}

void Stop() {
  //analogWrite(enable1, 0);
  //analogWrite(enable2, 0);
  digitalWrite(motor11, LOW);
  digitalWrite(motor12, LOW);
  digitalWrite(motor21, LOW);
  digitalWrite(motor22, LOW);
}

void turnRight() {
  //analogWrite(enable1, 100);
  //analogWrite(enable2, 100);
  digitalWrite(motor11, LOW);
  digitalWrite(motor12, HIGH);
  digitalWrite(motor21, LOW);
  digitalWrite(motor22, HIGH);
  
}

void turnLeft() {
  //analogWrite(enable1,100);
  //analogWrite(enable2, 100);
  digitalWrite(motor11, HIGH);
  digitalWrite(motor12, LOW);
  digitalWrite(motor21, HIGH);
  digitalWrite(motor22, LOW);
}

void moveForward() {
  digitalWrite(motor11, HIGH);
  digitalWrite(motor12, LOW);
  digitalWrite(motor21, LOW);
  digitalWrite(motor22, HIGH);
  //analogWrite(enable1, 100);
  //analogWrite(enable2, 100);
  
}

void moveBackward() {
  //analogWrite(enable1, 100);
  //analogWrite(enable2, 100);
  digitalWrite(motor11, LOW);
  digitalWrite(motor12, HIGH);
  digitalWrite(motor21, HIGH);
  digitalWrite(motor22, LOW);
  
}

void turnAround() {
  digitalWrite(motor21, HIGH);
  digitalWrite(motor22, LOW);
  for (int fadeValue = 70; fadeValue <=200; fadeValue +=10) 
  {
    analogWrite(enable1, fadeValue);
    digitalWrite(motor11, LOW);
    digitalWrite(motor12, HIGH);
  }
  for (int fadeValue = 200; fadeValue >=70; fadeValue -=10) 
  {
    analogWrite(enable2, fadeValue);
    digitalWrite(motor11, LOW);
    digitalWrite(motor12, HIGH);
  }
}

void LineFollower(){
  while (received == '0')
  {
    if (analogRead(infraRed1)<200)
    {
      digitalWrite(motor11, HIGH);
      digitalWrite(motor12, LOW);
      analogWrite(enable1, 150);
    }    
    else  
    {
      digitalWrite(motor11, LOW);
      digitalWrite(motor12, HIGH);
      analogWrite(enable1, 150);
      digitalWrite(motor21, HIGH);
      digitalWrite(motor22, LOW);
      analogWrite(enable2, 150);
    }      
    if(analogRead(infraRed2)<200)
    {
      digitalWrite(motor21, HIGH);
      digitalWrite(motor22, LOW);
      analogWrite(enable2, 150);
    }
    else  
    {
      digitalWrite(motor11, HIGH);
      digitalWrite(motor12, LOW);
      analogWrite(enable1, 150);
      digitalWrite(motor21, LOW);
      digitalWrite(motor22, HIGH);
      analogWrite(enable2, 150);
    }
    Serial.print(analogRead(infraRed1));
    Serial.print(" ");
    Serial.println(analogRead(infraRed2));
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
    analogWrite(enable1, 255);
    analogWrite(enable2, 255);
    Serial.print("Still there ");
    int distanceRight = 0;
    int distanceLeft = 0;
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
      moveBackward();
      delay(500);
      Stop();
      delay(100);
      distanceRight = lookRight();
      delay(500);
      distanceLeft = lookLeft();
      delay(500);
      int tmpdist = distanceLeft - distanceRight;
      if (tmpdist >0 || distance >= distanceLeft)
      {     
        turnRight();
        delay (1000);
        moveForward();
      }
      else {
        turnLeft();
        delay(1000);
        moveForward();
      }
    }
    else{
      moveForward(); 
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
    if (yAxis < 470) 
    {
      // Set Motor A backward
      digitalWrite(motor11, HIGH);
      digitalWrite(motor12, LOW);
      // Set Motor B backward
      digitalWrite(motor21, HIGH);
      digitalWrite(motor22, LOW);
      // Convert the declining Y-axis readings for going backward from 470 to 0 into 0 to 255 value for the PWM signal for increasing the motor speed
      motorSpeedA = map(yAxis, 470, 0, 0, 255);
      motorSpeedB = map(yAxis, 470, 0, 0, 255);
    }
    else if (yAxis > 550) 
    {
      // Set Motor A forward
      digitalWrite(motor11, LOW);
      digitalWrite(motor12, HIGH);
      // Set Motor B forward
      digitalWrite(motor21, LOW);
      digitalWrite(motor22, HIGH);
      // Convert the increasing Y-axis readings for going forward from 550 to 1023 into 0 to 255 value for the PWM signal for increasing the motor speed
      motorSpeedA = map(yAxis, 550, 1023, 0, 255);
      motorSpeedB = map(yAxis, 550, 1023, 0, 255);
    }
    // If joystick stays in middle the motors are not moving
    else 
    {
      motorSpeedA = 0;
      motorSpeedB = 0;
    }
    // X-axis used for left and right control
    if (xAxis < 470) 
    {
      // Set Motor A forward
      digitalWrite(motor11, HIGH);
      digitalWrite(motor12, LOW);
      // Set Motor B backward
      digitalWrite(motor21, LOW);
      digitalWrite(motor22, HIGH);
      // Convert the declining Y-axis readings for going backward from 470 to 0 into 0 to 255 value for the PWM signal for increasing the motor speed
      motorSpeedA = map(yAxis, 470, 0, 0, 255);
      motorSpeedB = map(yAxis, 470, 0, 0, 255);
    }
    else if (xAxis > 550) 
    {
      // Set Motor A backward
      digitalWrite(motor11, LOW);
      digitalWrite(motor12, HIGH);
      // Set Motor B forward
      digitalWrite(motor21, HIGH);
      digitalWrite(motor22, LOW);
      // Convert the increasing Y-axis readings for going forward from 550 to 1023 into 0 to 255 value for the PWM signal for increasing the motor speed
      motorSpeedA = map(xAxis, 550, 1023, 0, 255);
      motorSpeedB = map(xAxis, 550, 1023, 0, 255);
    }
    analogWrite(enable1, motorSpeedA); // Send PWM signal to motor A
    analogWrite(enable2, motorSpeedB); // Send PWM signal to motor B
    if (myB.available() > 0)// may delete it
    {
      received = myB.read();
    }
  }
}

void Manual (){
  analogWrite(enable1, 255);
  analogWrite(enable2, 255);
  while ((received > 50) && (received < 56))
  {
    Serial.print("received: ");
    Serial.println(received);
    if (temp!=t)
    {
      digitalWrite(motor21,LOW);
      digitalWrite(motor22,LOW);
      digitalWrite(motor11,LOW);
      digitalWrite(motor12,LOW);
    }
    temp=t;
    Serial.println(t);
    delay(100);
    if (t=='3'){
      digitalWrite(motor21,LOW);
      digitalWrite(motor22,HIGH);
      digitalWrite(motor11,HIGH);
      digitalWrite(motor12,LOW);
    }
    if(t=='4'){    
      digitalWrite(motor21,HIGH);
      digitalWrite(motor22,LOW);
      digitalWrite(motor11,LOW);
      digitalWrite(motor12,HIGH);
    }
    if(t=='5'){
      digitalWrite(motor21,LOW);
      digitalWrite(motor22,HIGH);
      digitalWrite(motor11,LOW);
      digitalWrite(motor12,HIGH);
    }
    if(t=='6'){
      digitalWrite(motor21,HIGH);
      digitalWrite(motor22,LOW);
      digitalWrite(motor11,HIGH);
      digitalWrite(motor12,LOW);
    }
    if(t=='7'){
      digitalWrite(motor21,LOW);
      digitalWrite(motor22,LOW);
      digitalWrite(motor11,LOW);
      digitalWrite(motor12,LOW);
    }
    while (myB.available() > 0)// may delete it
    {
      received = myB.read();
      t = received;
    }
  }
}

void loop(){

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
