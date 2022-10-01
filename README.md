# Table of Contents
1. [Introduction](#Introduction)
2. [Objectives](#Objectives)
   - [MainCode Robot](#MainCode Robot)
   - [MainCodeNika Robot](#MainCodeNika%20Robot)
   - [MainCodeGreen1 Robot](#MainCodeGreen1%20Robot)
   - [MainCodeAws Robot](#MainCodeAws%20Robot)
3. [Materials and Equibments](#Materials%20and%20Equibments)
4. [Physical Layout](#Physical%20Layout)
5. [Electerical Connections](#Electerical%20Connections)
6. [Software](#Software)
   - [Arduino Codes](#Arduino%20Codes)
   - [ESP32-CAM](#ESP32-CAM)
   - [App Inventor](#App%20Inventor)
   - [Mobile Application](#Mobile%20Application)
7. [Further Work](#Further%20Work)
# Introduction
Robots are machines that are programmed to perform certain tasks either by obtaining an instant command from user (controlled remotely), or acting upon a predefined command (automated).

The physical layout of the robots were built in Solidworks software, the electrical connections were set and simulated using [TinkerCAD](https://www.tinkercad.com/circuits) software to verify the functionality and aesthetics of the design, and software code was written and uploaded using Arduino IDE software. The codes were uploaded to Arduino Uno microcontroller and ESP32-CAM, but it can be uploaded to any other Arduino boards (and some other boards, but the code might require further modifications.
> **Warning**
> Special attention must be given to pins when making hardware connections.

# Objectives
This section is to state robots’ functionality for the different versions of code
## MainCode Robot
1. To move from its starting point to the end point
2. To collect digital materials while moving (record video while moving, and take pictures when ordered (when faces an obstacle in this case)) ** Which is done using [ESP32-CAM chip](https://randomnerdtutorials.com/telegram-esp32-cam-photo-arduino/)**
3. To achieve these functions, more supplementary functions must be provided. For example, in order for the robot to move towards the endpoint, it needs to know where the endpoint is, and for this the robot must be in contact with the user to get the coordinates or to get the direct command to move, so the function in this case it ***to establish a communication with the user’s mobile phone.*** The robot must also ***avoid any obstacles blocking its path by detecting them in the first place, and then then acting accordingly.*** After detecting the obstacle, the robot must stop and check the surroundings to decide in which direction it should keep moving (right or left), and for that the robot must have neck like tool. ***The robot must keep updating its position from the endpoint*** in order not to lose its track, as well ***it must store its movement information (its path)*** in order to use it to return to its home location.
4. To be controlled directly by the user by receiving commands from users controller (Mobile Phone).

## MainCodeNika Robot
To be controlled directly by the user by receiving commands from users controller (Mobile Phone); to move and to collect physical materials (ex. rocks) using the gripper.
## MainCodeGreen1 Robot
It has four different modes which are:
1. Line Follower: using Infrared Radiation sensor
2. Obsatcle Avoiding: using UltraSonic sensor
3. JoyStick: controlled by user (for educational purposes)
4. Manual: controlled directly by the user by receiving commands from users controller (Mobile Phone)
## MainCodeAws Robot
To establish a communication between the user and the one robot (the Master), and allow the Master to calculate the distances to the destination, and order the closest robot (either himself or the Slave - the closest -) to move towards it.

# Materials and Equibments
In this section, the most important equibments that were used to build the robot will be stated.
- Arduino UNO.
- ESP32-CAM.
- DC Motor Driver (L293D).
- Bluetooth module HC05.
- Ultrasonic sensor.
- Infrared Radiation sensor
- JoyStick
- DC Gearbox Motor.
- Servo Motor.
- Batteries.
- Cables.
- Tires.
- body
- Gripper

# Physical Layout
The following Figure shows the physical layout of the [MainCode](https://github.com/AbdelrahmanEnan/Robots/tree/main/MainCode) Robot using SolidWorks software.

![](https://github.com/AbdelrahmanEnan/Robots/blob/main/Isometric%20view%20of%20the%20assembly.png)
# Electerical Connections
> **Note**
> The main focus of this document is in the software part of the robots (Not the hardware), but a general picture of the hardware is given as well.
The following diagram shows the electrical connections of all components for the [MainCode](https://github.com/AbdelrahmanEnan/Robots/tree/main/MainCode) Robot

![](https://github.com/AbdelrahmanEnan/Robots/blob/main/All%20electrical%20connections.png)

While the following diagram shows the connection between the Bluetooth chip and Arduino.

![](https://github.com/AbdelrahmanEnan/Robots/blob/main/bluetooth_stKw11hoiw.jpg)
# Software
All Arduino (and ESP32-CAM) codes were written in the Arduino IDE in C++ , and it mainly consists of three parts: Global part, Setup part, and Loop part. Global part is used to call the used libraries, and to declare the global variables used and to assign values to them if needed. In Setup part as the name implies, Arduino board is set up by setting pins mode, INPUT or OUTPUT, as well as variables initializing ("initial condition"). In Loop part, as the name implies, which is the main part, the code is repeated forever as long as there is a power for Arduino. Other than these three main functions, several functions were written to help Loop function to perform as desired.
## Arduino Codes
[Main Code](https://github.com/AbdelrahmanEnan/Robots/tree/main/MainCode) is the Main code "I guess :sweat_smile:", in which comments and explainations are provided
But [MainCode2](https://github.com/AbdelrahmanEnan/Robots/tree/main/MainCode2) is better written and the last version of the code.

The comments in the [MainCode](https://github.com/AbdelrahmanEnan/Robots/tree/main/MainCode) is good for [MainCode2](https://github.com/AbdelrahmanEnan/Robots/tree/main/MainCode2), and [MainCodeNika](https://github.com/AbdelrahmanEnan/Robots/tree/main/MainCodeNika) as well.

![FlowChart](https://github.com/AbdelrahmanEnan/Robots/blob/main/FlowChart.jpg) The following image illustrates flow chart of the [main code](https://github.com/AbdelrahmanEnan/Robots/tree/main/MainCode)

## ESP32-CAM
[This video](https://www.youtube.com/watch?v=q-KIpFIbRMk), and [this website](https://randomnerdtutorials.com/esp32-cam-video-streaming-face-recognition-arduino-ide/) contain enough instructions to stream live video to local IP adress.

While [this link](https://randomnerdtutorials.com/telegram-esp32-cam-photo-arduino/) has the instructions to capture and send photos to a telegram account.
The previous website has almost everything about ESP32-CAM.

## App Inventor
[App Inventor](https://github.com/AbdelrahmanEnan/Robots/blob/main/App%20Inventor.pdf) is a pdf file that has the instructions needed to access MIT App Inventor website, and create the apps needed to control the robots. 

[Robooot.aia](https://github.com/AbdelrahmanEnan/Robots/blob/main/Robooot.aia), [Nika.aia](https://github.com/AbdelrahmanEnan/Robots/blob/main/Nika.aia), and [RobotGreen.aia](https://github.com/AbdelrahmanEnan/Robots/blob/main/RobotGreen.aia) are the programs needed to be imported to App Inventor.

## Mobile Application
![](https://github.com/AbdelrahmanEnan/Robots/blob/main/Interface.png).

Previous figure shows the user interface of the mobile application.

Starting from making Bluetooth module connected to the Arduino by letting the user to choose Bluetooth name from a list of available devices. Before a Bluetooth connection is made, every item in the app is invisible except for the Bluetooth menu. When Bluetooth is connected, a “Choose_Method_List” menu appears containing different methods form which the user chooses the desired one. If the user chooses “Manual”, the manual block will appear, otherwise if the user chooses “Coordinates”, the coordinate block will appear.

In Manual block there are 7 buttons which are: Forward, Backward, Right, Left, Stop, Home, and Restart. First four buttons when touched down, the application sends a special character for each to Arduino using Bluetooth to perform the desired action, but when touched up the application sends a character to Stop. When “Stop” button is clicked, the application sends a character to Stop. The last two buttons when clicked, the application also sends a character to Arduino to perform the desired action, and the application makes “Manual” block invisible again (takes the user to Choose method list).

In "Coordinates" block there are two buttons for selecting the method in the first row, followed by two text boxes, followed by "Confirm" button. As with the manual buttons, the two buttons in the first row when clicked the application sends a special character for each to Arduino to set the desired method. The text boxes in the next row takes user’s input for the desired coordinated. When “Confirm” button in the last row is clicked, the application checks whether the text boxes contain data or not, if it does the application sends the coordinates to Arduino, otherwise if not the application does not send anything to Arduino and changes the text under each text box to “Enter the Coordinates”.

# Further Work 
It would be more advanced if a velocity sensor is added to monitor robot’s speed to avoid any miscalculations and to ensure that the robot moves the exact amount of time required, hence the exact desired distance.
