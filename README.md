# IOT-pinball-machine

* ## Module Purpose
   The purpose of this module is to enable real-time score tracking via a mobile device by using light-sensitive sensors to detect the passage of the ball, determining scores in the backend, and transmitting the score and track information via MQTT.


* ## Materials Needed
   To build and operate this project, you will need the following materials:
    1. Node MCU32S *2
    2. Pinball machine with 7 tracks and steel balls
    3. Light-sensitive sensor modules *7
    4. Small LED lights *7
    5. Light strip (to be placed above all light-sensitive sensors for accurate detection) *1


* ## Program Functionality
  * Backend:
    * flows.json: The flows.json file is used to configure the flow within a Node-RED environment. This file contains detailed information about each node, including      node types, properties, connections, and deployment details. 
 
  * Sensor_Node:
    1. LED/LED.ino: The LED.ino file is used to control the LED lights. It illuminates the LEDs for scoreable tracks and turns off the LEDs for non-scoreable tracks. Each time a user scores, it receives a score signal via MQTT and randomly changes the scoreable track.
    2. Light/Light.ino:The Light.ino file is used to operate the light-sensitive sensor module. It detects the track traversed by a steel ball and uploads the track code to MQTT.
   

* ## Assembly Instructions
  Two Node MCU32S boards are used in this project, with one board connected to 7 light-sensitive sensors and the other connected to 7 LEDs. The light-sensitive sensors are positioned under the tracks, while the LEDs are placed above each track to indicate scoreable tracks to the user. Ensure that each LED and its corresponding light-sensitive sensor share the same numbering to avoid scoring errors.

  The programs used for this setup are Light/Light.ino and LED/LED.ino, which should be uploaded using the Arduino IDE.
  
  For backend operations, download Node-RED and import the "flows.json" file.

* ## Contributors

   A huge thank you to all the people who have contributed to this project!

   ### Core Team

   - [wadanono](https://github.com/wadanono) - **Hardware Debugging**
   - [ffaa0100aa](https://github.com/ffaa0100aa) - **Hardware Debugging**
   - [hhoowwaarrdd](https://github.com/hhoowwaarrdd) - **Assembly**
   - [Olive](https://github.com/Olive020) - **Backend Development**
   - [oath](https://github.com/aaaaa5455) - - **Firmware Development**
   - [hmes98318](https://github.com/hmes98318) - - **Firmware Development**
  ### Special Thanks
   - [hmes98318](https://github.com/hmes98318) - - **Backend Testing**

  Each member of the team has demonstrated exceptional dedication and expertise, contributing to the success of the project. Their collective efforts have been instrumental in achieving our project goals.


