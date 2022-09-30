#include <Servo.h>
#include <NewPing.h>
#include <SoftwareSerial.h>
using namespace std;

SoftwareSerial myB (6,7);//RX,TX//need to change any Serial. to myB.

const int L1 = 5;
const int L2 = 4;
const int R1 = 3;
const int R2 = 2;
const int I1 = 9;
const int I2 = 10;

#define trig A1
#define echo A2
#define maxDistance 200
NewPing sonar(trig, echo, maxDistance);

Servo servo;

int distanceo = 100;
double averageVelocity = 0.01;
double RotTime = 5/averageVelocity;
double x = 0.0;
double y = 0.0;
float coor [2] = {0.0,0.0};
char received = '.';

char dirMem [100];
int disMem [100]={0};
int index = 0;

void setup(){

    Serial.begin(9600);
    myB.begin(9600);
    pinMode(R1, OUTPUT);
    pinMode(R2, OUTPUT);
    pinMode(L1, OUTPUT);
    pinMode(L2, OUTPUT);
    servo.attach(11);
    servo.write(90);
    delay(2000);
    distanceo = ReadPing();
    delay(100);
    distanceo = ReadPing();
    delay(100);
    distanceo = ReadPing();
    delay(100);
    distanceo = ReadPing();
    delay(100);
    distanceo = ReadPing();
    delay(100);
}

void SetCoord (double dX, double dY){

    x = dX / averageVelocity;
    y = dY / averageVelocity;
    for (int i = 0; i < 100; i++)
    {
      dirMem[i] = 'h';
      disMem[i] = 0;
    }
    index = 0;
}

int CheckRight(){

    servo.write(0);
    delay(400);
    int dis = ReadPing();
    delay(100);
    servo.write(90);
    return dis;
}

int CheckLeft(){

    servo.write(180);
    delay(500);
    int dis = ReadPing();
    delay(100);
    servo.write(90);
    return dis;
    delay(100);
}

int ReadPing(){

    delay(60);
    int dis = sonar.ping_cm();
    if (dis == 0)
    {
        dis = 250;
    }
    return dis;
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

void Right(){

    digitalWrite(L1, HIGH);
    digitalWrite(R2, HIGH);
    digitalWrite(L2, LOW);
    digitalWrite(R1, LOW);
    delay(RotTime);
    digitalWrite(L1, HIGH);
    digitalWrite(R1, HIGH);
    digitalWrite(L2, LOW);
    digitalWrite(R2, LOW);
}

void Left(){

    digitalWrite(L2, HIGH);
    digitalWrite(R1, HIGH);
    digitalWrite(L1, LOW);
    digitalWrite(R2, LOW);
    delay(RotTime);
    digitalWrite(L1, HIGH);
    digitalWrite(R1, HIGH);
    digitalWrite(L2, LOW);
    digitalWrite(R2, LOW);
}

void Reverse(){

    digitalWrite(L2, HIGH);
    digitalWrite(R1, HIGH);
    digitalWrite(L1, LOW);
    digitalWrite(R2, LOW);
    delay(2*RotTime);
    digitalWrite(L1, HIGH);
    digitalWrite(R1, HIGH);
    digitalWrite(L2, LOW);
    digitalWrite(R2, LOW);
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

void RotClocW(double Time){

    digitalWrite(L1, HIGH);
    digitalWrite(R2, HIGH);
    digitalWrite(L2, LOW);
    digitalWrite(R1, LOW);
    delay(Time);
    digitalWrite(L1, HIGH);
    digitalWrite(R1, HIGH);
    digitalWrite(L2, LOW);
    digitalWrite(R2, LOW);
}

void RotAntiCW(double Time){

    digitalWrite(L2, HIGH);
    digitalWrite(R1, HIGH);
    digitalWrite(L1, LOW);
    digitalWrite(R2, LOW);
    delay(Time);
    digitalWrite(L1, HIGH);
    digitalWrite(R1, HIGH);
    digitalWrite(L2, LOW);
    digitalWrite(R2, LOW);
}

void FRecord(double Time){

    y = y - Time;
    if (dirMem[index-1] == 'F')
    {
        disMem[index-1] = disMem[index-1] + Time;
    }
    else
    {
        dirMem[index] = 'F';
        disMem[index] = Time;
        index ++;
    }
}

void BRecord(double Time){

    y = y + Time;
    if (dirMem[index-1] == 'B')
    {
        disMem[index-1] = disMem[index-1] + Time;
    }
    else
    {
        dirMem[index] = 'B';
        disMem[index] = Time;
        index ++;
    }
}

void LRecord(){

    double temp = x;
    x = y;
    y = -1 * temp;
    dirMem[index] = 'L';
    disMem[index] = RotTime;
    index ++;
}

void RRecord(){

    double temp = x;
    x = -1 * y;
    y = temp;
    dirMem[index] = 'R';
    disMem[index] = RotTime;
    index ++;
}

void VRecord(){

    x = -1 * x;
    y = -1 * y;
    dirMem[index] = 'V';
    disMem[index] = 2 * RotTime;
    index ++;
}

void ARecord(double Time){

    y = sqrt(pow(x,2.0)*1.0 + pow(y,2.0)*1.0);
    int h = y;
    if (h%100 < 50)
    {
      y = (h - h%100);
    }
    else 
    {
      y = (h - h%100)+100;
    }
    x = 0;
    dirMem[index] = 'A';
    disMem[index] = Time;
    index ++;
}

void MLRecord(double Time){

    if (dirMem[index-1] == 'l')
    {
        disMem[index-1] = disMem[index-1] + Time;
    }
    else
    {
        dirMem[index] = 'l';
        disMem[index] = Time;
        index ++;
    }
}

void MRRecord(double Time){

    if (dirMem[index-1] == 'r')
    {
        disMem[index-1] = disMem[index-1] + Time;
    }
    else
    {
        dirMem[index] = 'r';
        disMem[index] = Time;
        index ++;
    }
}

void BackRight(){

    int disRight = 0;
    do
    {
        Move();
        delay(100);
        Stop();
        disRight = CheckRight();
        delay(300);
    }while (disRight < 20);
    Right();
    Stop();
    RRecord();
}

void BackLeft(){

    int disLeft = 0;
    do
    {
        Move();
        delay(100);
        Stop();
        disLeft = CheckLeft();
        delay(300);
    }while (disLeft < 20);
    Left();
    Stop();
    LRecord();
}

void Avoid(){
    Stop();
    delay(300);
    int disRight = CheckRight();
    delay(300);
    int disLeft = CheckLeft();
    delay(300);
    if (disRight > disLeft)
    {
        Right();
        Stop();
        RRecord();
        BackLeft();
    }
    else if (disRight < disLeft)
    {
        Left();
        Stop();
        LRecord();
        BackRight();
    }
    else
    {
        if (x < 0)
        {
            Left();
            Stop();
            LRecord();
            BackRight();
        }
        else
        {
            Right();
            Stop();
            RRecord();
            BackLeft();
        }
    }
}

void Move(){

    distanceo = ReadPing();
    if (distanceo > 20)
    {
        Forward();
        FRecord(100);
    }
    else
    {
        Avoid();
    }
}

void GoTo(){
    Serial.println("GoTo function");
    while ((x != 0)||(y != 0))
    {
        delay (100);
        if (y > 0)
        {
            Move();
        }
        else if (x > 0)
        {
            Right();
            Stop();
            RRecord();
        }
        else if (x < 0)
        {
            Left();
            Stop();
            LRecord();
        }
        else 
        {
            Reverse();
            Stop();
            VRecord();
        }
        //distanceo = ReadPing();
    }
    Stop();
}

void AllPositive(){

    if ((x >= 0) && (y < 0))
    {
        Right();
        Stop();
        RRecord();
    }
    else if ((y >= 0) && (x < 0))
    {
        Left();
        Stop();
        LRecord();
    }
    else
    {
        Reverse();
        Stop();
        VRecord();
    }
}

void GetAngle (){

    AllPositive();
    double theta = atan(x / y);
    theta = theta * 57.2957795;
    double GetTime = theta * RotTime / 90.0;
    RotClocW(GetTime);
    Stop();
    ARecord(GetTime);
}

void Home(){
    Serial.println("Home function");
    int i = index;
    if (i > 0)
    {
        Reverse();
        for (i; i > -1; i--)
        {
            if (dirMem[i] == 'R')
            {
                Left();
            }
            else if (dirMem[i] == 'L')
            {
                Right();
            }
            else if (dirMem[i] == 'V')
            {
                Reverse();
            }
            else if (dirMem[i] == 'F')
            {
                Forward();
                delay(disMem[i]);
            }
            else if (dirMem[i] == 'B')
            {
                Backward();
                delay(disMem[i]);
            }
            else if (dirMem[i] == 'A')
            {
                RotAntiCW(disMem[i]);
            }
            else if (dirMem[i] == 'r')
            {
                RotAntiCW(disMem[i]);
            }
            else if (dirMem[i] == 'l')
            {
                RotClocW(disMem[i]);
            }
            Stop();
            delay(100);
        }
        SetCoord (0.0,0.0);
    }
}

void Manual(){
    while ((received > 49) && (received < 56))
    {
        if (received == '2')
        {
            distanceo = ReadPing();
            if (distanceo > 20)
            {
                Forward();
                FRecord(100);
            }
            else
            {
                Stop();
                myB.print('1');
                delay(300);
                int disRight = CheckRight();
                delay(300);
                int disLeft = CheckLeft();
                delay(300);
                if (disRight > disLeft)
                {
                    myB.print('2');
                }
                else if (disLeft > disRight)
                {
                    myB.print('3');
                }
            }
        }
        else if (received == '3')
        {
            Backward();
            BRecord(100);
        }
        else if (received == '4')
        {
            ManualRight();
            MRRecord(100);
        }
        else if (received == '5')
        {
            ManualLeft();
            MLRecord(100);
        }
        else if (received == '6')
        {
            Stop();
        }
        else if (received == '7')
        {
            Home();
            received = '.';
        }
        else if (received == '8')
        {
            Stop();
            received = '.';
            SetCoord (0.0,0.0);
        }
        delay(100);
        if (myB.available() > 0)
        {
            received = myB.read();
        }
    }
}

void loop(){
    Serial.println("Loop");
    analogWrite(I1, 255);
    analogWrite(I2, 255);
    while (myB.available() == 0) 
    {
      Serial.print("Wait ");
    }
    if (myB.available() > 0)// may delete it
    {
        received = myB.read();
        Serial.println(received);
        if ((received == '0') || (received == '1'))
        {
            Serial.println("Coor");
            while (myB.available() == 0)
            {
              delay(100);
            }
            if (myB.available() > 0)
            {
                delay(400);//Is it necessary?
                coor [0] = myB.read();
                coor [1] = myB.read();
                SetCoord(coor[0],coor[1]);
                Serial.println("Got it ");
            }
            if (received == '0')
            {
                Serial.println("xy");
                GoTo();
                delay(5000);
                Home();
            }
            else
            {
                GetAngle ();
                GoTo();
                delay(5000);
                Home();
            }
        }
        else if ((received > 49) && (received < 56))
        {
            Manual();
        }
        while (myB.available() > 0)
        {
            myB.read();
        }
    }
}
