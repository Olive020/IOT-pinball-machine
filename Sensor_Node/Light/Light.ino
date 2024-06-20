#include <WiFi.h>
#include <PubSubClient.h>


// WiFi AP ssid / password here
static const char* ssid = "iot2.4g";  // Change this to your WiFi SSID
static const char* password = "12345678";  // Change this to your WiFi password

// MQTT Broker info
//IPAddress server(140, 127, 196, 119);
static char *server = "140.127.196.39";
int port = 18883;

#define TOPIC_Light  "lamy/Light1"

static char *client_id = "rehibfwilgbwubguiwlgv"; 
unsigned long light_time;


// Clients for MQTT
WiFiClient wifiClient;
PubSubClient client(wifiClient);
/*
 * Toggle LED ON/OFF by Light degree (Polling)
 * (by modifying example "Debounce")
*/
// constants won't change. They're used here to set pin numbers:   
const int lightPin0 = 17;  // ADC2_0
const int lightPin1 = 4 ; // ADC2_1 27
const int lightPin2 = 27; // ADC2_3 25
const int lightPin3 = 36;  // ADC2_4  5
const int lightPin4 = 25; // ADC2_5 36
const int lightPin5 = 5 ;  // ADC2_6 4
const int lightPin6 = 32;  // ADC2_7  
const int ledPin = LED_BUILTIN;    // the number of the LED pin


const char* mqtt_user = "iot2024";
const char* mqtt_password = "isuCSIE2024#";



// Variables will change:
int ledState = LOW;        // the current state of the output pin
int lightState;            // the current reading from the input pin
int lastLightState = HIGH;  // the previous reading from the input pin

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

void setup() {
  //Serial.begin(9600);
  Serial.begin(115200);
  client.setServer(server, port); // Setup Server address and port

  pinMode(lightPin0, INPUT_PULLUP);
  pinMode(lightPin1, INPUT_PULLUP);
  pinMode(lightPin2, INPUT_PULLUP);
  pinMode(lightPin3, INPUT_PULLUP);
  pinMode(lightPin4, INPUT_PULLUP);
  pinMode(lightPin5, INPUT_PULLUP);
  pinMode(lightPin6, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);

  // setup Wifi connection
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println();
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  light_time=millis();
  
}

void loop() {
  unsigned long current_time;

  // Check MQTT broker connection status
  // If it is disconnected, reconnect to the broker
  // if (!client.connected()) {
  //   reconnect();
  // }

  // Get temperature & humidity and publish them
  current_time = millis();
   
//  read the state of light sensor into a local variable:
//  int reading = analogRead(lightPin);
//  Serial.println("DATA:");
//  Serial.println(digitalRead(lightPin0));
//  Serial.println(digitalRead(lightPin1));
//  Serial.println(digitalRead(lightPin2));
//  Serial.println(digitalRead(lightPin3));
//  Serial.println(digitalRead(lightPin4));
//  Serial.println(digitalRead(lightPin5));
//  Serial.println(digitalRead(lightPin6));
//  Serial.println("/n");
    int light0 = digitalRead(lightPin0);
    int light1 = digitalRead(lightPin1);
    int light2 = digitalRead(lightPin2);
    int light3 = digitalRead(lightPin3);
    int light4 = digitalRead(lightPin4);
    int light5 = digitalRead(lightPin5);
    int light6 = digitalRead(lightPin6);
  
    // Convert light sensor values to strings
    char buf[8];
  
    if (!client.connected()) {
      reconnect();
    }
    
    // Publish each sensor value to the corresponding MQTT topic
    int index;
    if (light0 > 0) {
      index = 0;
      sprintf(buf, "%d", index);
      Serial.println(buf);
      client.publish(TOPIC_Light, buf); 
    }
    else if (light1 > 0) 
    {
      index = 1;
      sprintf(buf, "%d", index);
      Serial.println(buf);
      client.publish(TOPIC_Light, buf);
    }
    else if (light2 > 0) 
    {
      index = 2;
      sprintf(buf, "%d", index);
      Serial.println(buf);
      client.publish(TOPIC_Light, buf);
    }
    else if (light3 > 0) 
    {
      index = 3;
      sprintf(buf, "%d", index);
      Serial.println(buf);
      client.publish(TOPIC_Light, buf);
    }
    else if (light4 > 0) 
    {
      index = 4;
      sprintf(buf, "%d", index);
      Serial.println(buf);
      client.publish(TOPIC_Light, buf);
    }
    else if (light5 > 0) 
    {
      index = 5;
      sprintf(buf, "%d", index);
      Serial.println(buf);
      client.publish(TOPIC_Light, buf);
    }
    else if (light6 > 0) 
    {
      index = 6;
      sprintf(buf, "%d", index);
      Serial.println(buf);
      client.publish(TOPIC_Light, buf);
    }
    else 
    {
      //Serial.println( current_time);
//      Serial.println( light_time);
      if (current_time - light_time >= 3000)
      {
        index = 7;
        sprintf(buf, "%d", index);
        Serial.println(buf);
        client.publish(TOPIC_Light, buf);
        light_time = current_time;
      }
    }
      

    
  // Keep MQTT process on going
  client.loop();
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP32Client",mqtt_user,mqtt_password)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
