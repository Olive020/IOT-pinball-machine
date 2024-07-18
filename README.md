# IOT-pinball-machine

* ## Backend:
  * flows.json: The flows.json file is used to configure the flow within a Node-RED environment. This file contains detailed information about each node, including      node types, properties, connections, and deployment details. 

* ## Sensor_Node:
  1. LED/LED.ino: The LED.ino file is used to control the LED lights. It illuminates the LEDs for scoreable tracks and turns off the LEDs for non-scoreable tracks. Each time a user scores, it receives a score signal via MQTT and randomly changes the scoreable track.
  2. Light/Light.ino:The Light.ino file is used to operate the light-sensitive sensor module. It detects the track traversed by a steel ball and uploads the track code to MQTT.
