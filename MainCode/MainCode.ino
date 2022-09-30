#include <Servo.h>            //Library for Servo motor
#include <NewPing.h>          //Library for Ultrasonic sensor
#include <SoftwareSerial.h>   //Library for Bluetooth connection
using namespace std;

SoftwareSerial myB (6,7);//RX,TX//To set pins 6 and 7 to be the Rx and Tx; Receiver and transmitter of the signals 

// Following lines to define pins for motors 
const int L1 = 5; //Left motor Forward
const int L2 = 4; //Left motor Forward
const int R1 = 3; //Right motor Forward
const int R2 = 2; //Right motor Forward
const int I1 = 9; //Right motor Enable (Speed; full speed is 255)
const int I2 = 10;//Left motor Enable (Speed; full speed is 255)

// Following lines to define pins and some features for Ultrasonic sensor
#define trig A1
#define echo A2
#define maxDistance 200
NewPing sonar(trig, echo, maxDistance);

// Following lines to define pins and some features for Servo motor
Servo servo;

// Following lines to setup initial condition for the robot
int distanceo = 100;
double averageVelocity = 0.01;//This to set the velocity of the robot to calculte distances in time of motion needed
double x = 0.0;
double y = 0.0;
float coor [2] = {0.0,0.0};
bool manual;

// Following lines to initiate arrays (storages) to store robot motion.
char dirMem [100];    //To Store direction of motion
int disMem [100]={0}; //To store magnitude of motion
int index = 0;        //To set the pointer to the first element in the array

void setup(){

    // Following lines sets the data rate in bits per second (baud) for serial data transmission. 
    Serial.begin(9600);
    myB.begin(9600);
    
    // Following lines configures the specified pin to behave either as an input or an output. 
    pinMode(R1, OUTPUT);
    pinMode(R2, OUTPUT);
    pinMode(L1, OUTPUT);
    pinMode(L2, OUTPUT);
    
    // Following lines specifies pin used for Servo motor signal (output) and initiate it 90 degrees (to be forward). 
    servo.attach(11);
    servo.write(90);

    // Following lines setup Ultrasonic sensor and read first distance. 
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
// Following function takes 2 values from user to set the coordinates taking
// Also it reset storaging arrays to be empty and set the pointer to the first element of the arrays 
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
// This function commands the servo motor (hence the ultrasonic sensor) to rotate right and calcualte the distance 
// to robots right then rotate to front again. and it retuns the distance between robot and the wall
int CheckRight(){

    servo.write(0);
    delay(400);
    int dis = ReadPing();
    delay(100);
    servo.write(90);
    return dis;
}
// Similar to previous one
int CheckLeft(){

    servo.write(180);
    delay(500);
    int dis = ReadPing();
    delay(100);
    servo.write(90);
    return dis;
    delay(100);
}
// This function is built-in function for ultrasonic sensor and it calculate the distance till the closest wall in front of the sensor
int ReadPing(){

    delay(60);
    int dis = sonar.ping_cm();
    if (dis == 0)
    {
        dis = 250;
    }
    return dis;
}
// This function sets right and left motor to not move in either direction; forward or backward
void Stop(){

    digitalWrite(R1, LOW);
    digitalWrite(L1, LOW);
    digitalWrite(R2, LOW);
    digitalWrite(L2, LOW);
}
// This function sets both right and left motors to rotate in the normal direction(Forward)and sets reverse direction to 0 (no motion)
void Forward(){

    digitalWrite(L1, HIGH);
    digitalWrite(R1, HIGH);
    digitalWrite(L2, LOW);
    digitalWrite(R2, LOW);
}
// This function is the reverse of the previous one
void Backward(){

    digitalWrite(L2, HIGH);
    digitalWrite(R2, HIGH);
    digitalWrite(L1, LOW);
    digitalWrite(R1, LOW);
}
// This function sets right motor to move forward and left motor to move backward
// for 0.5 seconds and then move forward again (you can delete forward part)
// Note: you can remove last four lines from this function and it will not effect its functionality 
void Right(){

    digitalWrite(L1, HIGH);
    digitalWrite(R2, HIGH);
    digitalWrite(L2, LOW);
    digitalWrite(R1, LOW);
    delay(500);             //This value must be changed for different velocities
    digitalWrite(L1, HIGH);
    digitalWrite(R1, HIGH);
    digitalWrite(L2, LOW);
    digitalWrite(R2, LOW);
}
// This function sets left motor to move forward and right motor to move backward for 0.5 seconds
void Left(){

    digitalWrite(L2, HIGH);
    digitalWrite(R1, HIGH);
    digitalWrite(L1, LOW);
    digitalWrite(R2, LOW);
    delay(500);             //This value must be changed for different velocities
    digitalWrite(L1, HIGH);
    digitalWrite(R1, HIGH);
    digitalWrite(L2, LOW);
    digitalWrite(R2, LOW);
}
// This function sets left motor to move forward and right motor to move backward for 1 second which makes one full rotation if full speed is provided
void Reverse(){

    digitalWrite(L2, HIGH);
    digitalWrite(R1, HIGH);
    digitalWrite(L1, LOW);
    digitalWrite(R2, LOW);
    delay(1000);            //This value must be changed for different velocities
    digitalWrite(L1, HIGH);
    digitalWrite(R1, HIGH);
    digitalWrite(L2, LOW);
    digitalWrite(R2, LOW);
}
// This function is made without time limit to allow the robot to ratate as long as the user touches down the right button
void ManualRight(){

    digitalWrite(L1, HIGH);
    digitalWrite(R2, HIGH);
    digitalWrite(L2, LOW);
    digitalWrite(R1, LOW);
}
// This function is similar to the previous one
void ManualLeft(){

    digitalWrite(L2, HIGH);
    digitalWrite(R1, HIGH);
    digitalWrite(L1, LOW);
    digitalWrite(R2, LOW);
}
// This function is made to make the robot rotate for specified amount of time 
// Used for rotation for a specific angle as shown later in GetAngle () function
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
// This function is similar to the prevoius one
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
// This function is used to update robot's coordinates and to record its backward motion
// Note that the robot has corrdination of the final destination point (End point is the reference for robot's motion)
void FRecord(double Time){

    y = y - Time;
    if (dirMem[index-1] == 'F')//If last element in the array is forward, it doesn't record a new forward entry, Instead, it updates the last enerty time (magnitude)
    {
        disMem[index-1] = disMem[index-1] + Time;
    }
    else
    {
        dirMem[index]='F';
        disMem[index]=Time;
        index ++;
    }
}
// This function is used to update robot's coordinates and to record its backward motion
void BRecord(double Time){

    y = y + Time;
    if (dirMem[index-1] == 'B')
    {
        disMem[index-1] = disMem[index-1] + Time;
    }
    else
    {
        dirMem[index]='B';
        disMem[index]=Time;
        index ++;
    }
}
// This function is used to update robot's coordinates (by making x value the new y, and y value the new -x), and to record its left motion
void LRecord(){

    double temp = x;
    x = y;
    y = -1 * temp;
    dirMem[index]='L';
    disMem[index]=500;
    index ++;
}
// This function is used to update robot's coordinates (by making x value the new y, and y value the new x), and to record its right motion
void RRecord(){

    double temp = x;
    x = -1 * y;
    y = temp;
    dirMem[index]='R';
    disMem[index]=500;
    index ++;
}
// This function is used to update robot's coordinates, and to record its 180 rotation 
void VRecord(){

    x = -1 * x;
    y = -1 * y;
    dirMem[index]='V';
    disMem[index]=1000;
    index ++;
}
// This function is used to update robot's coordinates, and to record its rotation for specific angle
// Used only if the user choses Direct method which calculate the angle and faces the final point 
// so the whole distance in y-axis, and x = 0
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
    dirMem[index]='A';
    disMem[index]=Time;
    index ++;
}
// This function records maual right rotation for the elapsed time 
void MRRecord(double Time){

    if (dirMem[index-1] == 'r')//If last element in the array is manual right, it doesn't record a new MR entry, Instead, it updates the last enerty time (magnitude)
    {
        disMem[index-1] = disMem[index-1] + Time;
    }
    else
    {
        dirMem[index]='r';
        disMem[index]=Time;
        index ++;
    }
}
// This function is similar to the previous one 
void MLRecord(double Time){

    if (dirMem[index-1] == 'l')
    {
        disMem[index-1] = disMem[index-1] + Time;
    }
    else
    {
        dirMem[index]='l';
        disMem[index]=Time;
        index ++;
    }
}

//The following five function are used for "Coordiantes" method 
//The following function commands the robot to move forward (by calling move() function) in y direction as long as y > 0 (the end point) 
//is in front of it, once that condition is no more satisfied the robot either turn right or left 
//Note that after turning right or left, the coordinates flips so y-axis is now x-axis and vice versa
//The function will loop until it reaches the end point where x = 0 and y = 0
void GoTo(){

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
// This function is to check if robot faces obstacle and to avoid it by calling Avoid() function
// It calls ReadPing() to calculate distance in front of it and if it is greater than 20 cm it will move forward and record that 
// id no then it will call Avoid() function
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
// This function makes robot stops as there is an obstacle in front of it, then check its surrondings to decide in which direction it should rotate
// once it rotates it calls Anti-Rotation-function which is either BackLeft()or BackRight() functions
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
// The next two functions let the robot to return to its original path after avoiding the obstacle detected previously on its path
// they do so by checking the direction they detected an obstacle on previously, and if there's no more obstacle it turns back to that direction
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

// The next two function is used for Direct method, in which the robot calcualte the angle to the end point
// and rotate, so the end point is on its y-axis; and x = 0
// This function is used to set the robot so that the end point is located on its first quartile (where it has y > 0 and x > 0)
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
// This function calculates the angle to the end point and calls RotClocW(GetTime) function 
// to rotate the robot, so it faces the end point
void GetAngle (){

    AllPositive();
    double theta = atan(x / y);
    theta = theta * 57.2957795;
    double GetTime = theta * 500.0 / 90.0;
    RotClocW(GetTime);
    Stop();
    ARecord(GetTime);
}
// This function makes the robot able to go to its starting point my first rotation for 180 degree
// then traverse the array from last to the first and move accordingly
// after traversing array from end to start, it resets the coordinates, x and y values (by calling SetCoord(0,0) function).
void Home(){

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

void loop(){

    analogWrite(I1, 255);// This line to set full speed for motor's rotation
    analogWrite(I2, 255);// This line to set full speed for motor's rotation
    while (myB.available() == 0) // This function is just to disable the code until it receives a signal from the user (App)
    if (myB.available() > 0)// Once it receives a signal
    {
        char received = myB.read();// Signal is read and saved to act upon it
        if ((received == '0') || (received == '1')) // For Non-manual methods (Direct and X-Y Coordinates methods)
        {
            while (myB.available() == 0)//To disable the code until it receives a signal contains the desired coordinates from the user (App)
            {
              delay(100);
            }
            if (myB.available() > 0) //Once it receives a signal it reads the signal and store the coordinates in an array and calls SetCoord() function
            {
                coor [0] = myB.read();
                coor [1] = myB.read();
                SetCoord(coor[0],coor[1]);
            }
            if (received == '0')// For X-Y Coordinates method
            {
                GoTo();
                delay(5000);
                Home();
            }
            else                //For X-Y Coordinates method
            {
                GetAngle ();
                GoTo();
                delay(5000);
                Home();
            }
        }
        else if ((received > 49) && (received < 56))// For manual mode if it recevies value between 2 and 8
        {
            manual = true; // To keep inside the loop as long as it is manual comand to save time and memory
            while (manual == true)
            {
                if (received == '2') // Forward if distance is enough otherwise it will stop
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
                    }
                }
                else if (received == '3')//Backward
                {
                    Backward();
                    BRecord(100);
                }
                else if (received == '4')//Right
                {
                    ManualRight();
                    MRRecord(100);
                }
                else if (received == '5')//Left
                {
                    ManualLeft();
                    MLRecord(100);
                }
                else if (received == '6')//Stop
                {
                    Stop();
                }
                else if (received == '7')//Home fumction and exist from manual mode
                {
                    Home();
                    manual = false;
                }
                else if (received == '8')//reset and exist from manual mode
                {
                    Stop();
                    SetCoord (0.0,0.0);
                    manual = false;
                }
                delay(100);
                if (myB.available() > 0)
                {
                    received = myB.read();
                }
            }
        }
        while (myB.available() > 0)//To remove any disturbing signal 
        {
            myB.read();
        }
    }
}
