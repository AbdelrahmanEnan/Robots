# To be edited later
## Introduction
Robots are machines that are programmed to perform certain tasks either by obtaining an instant command from user (controlled remotely), or acting upon a predefined command (automated).

The physical layout of the robots were built in Solidworks software, the electrical connections were set and simulated using [TinkerCAD](https://www.tinkercad.com/circuits) software to verify the functionality and aesthetics of the design, and control code was written and uploaded using Arduino IDE software. The codes were uploaded to Arduino Uno microcontroller and ESP32-CAM, but it can be uploaded to any other Arduino boards (and some other boards, but the code might require further modifications.
> **Warning**
> Special attention must be given to pins if different than the one in the code

## Objectives (robots’ functionality)
### MainCode Robot
1. To move from its starting point to the end point
2. To collect digital materials while moving (record video while moving, and take pictures when ordered (when faces an obstacle in this case))
3. To collect physical materials (ex. rocks) using gripper
4. To achieve these functions, more supplementary functions must be provided. For example, in order for the robot to move towards the endpoint, it needs to know where the endpoint is, and for this the robot must be in contact with the user to get the coordinates or to get the direct command to move, so the function in this case it to establish a communication with the user’s mobile phone. The robot must also avoid any obstacles blocking its path by detecting them in the first place, and then then acting accordingly. After detecting the obstacle, the robot must stop and check the surroundings to decide in which direction it should keep moving (right or left), and for that the robot must have neck like tool. The robot must keep updating its position from the endpoint in order not to lose its track, as well it must store its movement information (its path) in order to use it to return to its home location.

most fundamental functions which is to move, to avoid obstacles, to record video, to take photos when ordered, and to broadcast the recorded video on a local network.
### MainCodeNika Robot

### MainCodeGreen

## Further Work 
It would be more advanced if a velocity sensor is added to monitor robot’s speed to avoid any miscalculations and to ensure that the robot moves the exact amount of time required, hence the exact desired distance.


- Write more about application and instructions of using it.
## Arduino Code
All Arduino codes are written in the Arduino IDE in C++ , and it mainly consists of three parts: Global part, Setup part, and Loop part. Global part is used to call the used libraries, and to declare the global variables used and to assign values to them if needed. In Setup part as the name implies, Arduino board is set up by setting pins mode, INPUT or OUTPUT, as well as variables initializing ("initial condition"). In Loop part, as the name implies, which is the main part, the code is repeated forever as long as there is a power for Arduino. Other than these three main functions, several functions were written to help Loop function to perform as desired.
- Add FlowChart of the code
- Add text about each robot functionality
# Robots
## Arduino Codes
[Main Code](https://github.com/AbdelrahmanEnan/Robots/tree/main/MainCode) is the Main code "I guess :sweat_smile:", in which comments and explainations are provided
But [Main Code 2](https://github.com/AbdelrahmanEnan/Robots/tree/main/MainCode2) is better written and the last version of the code.

The comments in the [Main Code](https://github.com/AbdelrahmanEnan/Robots/tree/main/MainCode) is good for [Main Code](https://github.com/AbdelrahmanEnan/Robots/tree/main/MainCode), [MainCode2](https://github.com/AbdelrahmanEnan/Robots/tree/main/MainCode2), and [MainCodeNika](https://github.com/AbdelrahmanEnan/Robots/tree/main/MainCodeNika).

[FlowChart](https://github.com/AbdelrahmanEnan/Robots/blob/main/FlowChart.jpg) file shows the flow chart of the [main code](https://github.com/AbdelrahmanEnan/Robots/tree/main/MainCode)

## ESP32-CAM
[This video](https://www.youtube.com/watch?v=q-KIpFIbRMk), and [this website](https://randomnerdtutorials.com/esp32-cam-video-streaming-face-recognition-arduino-ide/) contain enough instructions to stream live video to local IP adress.

While [this link](https://randomnerdtutorials.com/telegram-esp32-cam-photo-arduino/) has the instructions to capture and send photos to a telegram account.
The previous website has almost everything about ESP32-CAM.

## App Inventor
[App Inventor](https://github.com/AbdelrahmanEnan/Robots/blob/main/App%20Inventor.pdf) is a pdf file that has the instructions needed to access MIT App Inventor website, and create the apps needed to control the robots. 

[Robooot.aia](https://github.com/AbdelrahmanEnan/Robots/blob/main/Robooot.aia), [Nika.aia](https://github.com/AbdelrahmanEnan/Robots/blob/main/Nika.aia), and [RobotGreen.aia](https://github.com/AbdelrahmanEnan/Robots/blob/main/RobotGreen.aia) are the programs needed to be imported to App Inventor.

