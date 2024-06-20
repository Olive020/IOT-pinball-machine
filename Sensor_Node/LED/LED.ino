#include <WiFi.h>
#include <PubSubClient.h>


// WiFi credentials
const char* ssidList[] = {"iot2.4g", "3715"};
const char* passwordList[] = {"12345678", "12345678"};
const int numNetworks = sizeof(ssidList) / sizeof(ssidList[0]);

// MQTT Broker info
//IPAddress server(140, 127, 196, 119);
static char *server = "140.127.196.39";
int port = 18883;

#define TOPIC_LED   "lamy/LED"
#define Signal   "lamy/Signal"


static char *client_id = "jsdonicqe;nc;qn"; 
unsigned long light_time;


// Clients for MQTT
WiFiClient wifiClient;
PubSubClient client(wifiClient);

// Pin Assignment
const int LEDPin_0 = 4;
const int LEDPin_1 = 23;
const int LEDPin_2 = 27;
const int LEDPin_3 = 25;
const int LEDPin_4 = 22;
const int LEDPin_5 = 5;
const int LEDPin_6 = 17;


const char* mqtt_user = "iot2024";
const char* mqtt_password = "isuCSIE2024#";

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP32Clientgg",mqtt_user,mqtt_password)) {
      Serial.println("connected");
      
      client.subscribe(Signal);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
void connectToWiFi() {
  for (int i = 0; i < numNetworks; i++) {
    WiFi.begin(ssidList[i], passwordList[i]);
    Serial.print("Connecting to ");
    Serial.println(ssidList[i]);
    
    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 20) {  // Try for 10 seconds
      delay(500);
      Serial.print(".");
      attempts++;
    }

    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("Connected to WiFi");
      Serial.print("IP address: ");
      Serial.println(WiFi.localIP());
      break;
    } else {
      Serial.println("Failed to connect");
    }
  }

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Could not connect to any WiFi network");
  }
}



// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);
  connectToWiFi();
  client.setServer(server, port); // Setup Server address and port

  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LEDPin_0, OUTPUT);
  pinMode(LEDPin_1, OUTPUT);
  pinMode(LEDPin_2, OUTPUT);
  pinMode(LEDPin_3, OUTPUT);
  pinMode(LEDPin_4, OUTPUT);
  pinMode(LEDPin_5, OUTPUT);
  pinMode(LEDPin_6, OUTPUT);
  digitalWrite(LEDPin_0, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(LEDPin_1, HIGH);
  digitalWrite(LEDPin_2, LOW);
  digitalWrite(LEDPin_3, HIGH);
  digitalWrite(LEDPin_4, LOW);
  digitalWrite(LEDPin_5, HIGH);
  digitalWrite(LEDPin_6, LOW);
  client.publish(TOPIC_LED, "0101010");
  
  
  light_time=millis();

  // 設定 MQTT 伺服器和回調函數

  client.setCallback(callback);
}

// the loop function runs over and over again forever
void loop() {
  
  char buf[8];

  if (!client.connected()) {
    reconnect();
  }
  
    light_time=millis();

    client.loop();        
}

// MQTT 訊息回調函數
void callback(char* topic, byte* message, unsigned int length) 
{
  
  String messageTemp;
  
  //copy字串訊息
  for(int i=0; i < length; i++)
  {
    Serial.print((char)message[i]);
    messageTemp+=(char)message[i];   
  }
  //如果是lamy/Signal發送且字串為1

    if(messageTemp == "1")
    {
      Serial.println("1");
      if(light_time%3==0)
      {
        digitalWrite(LEDPin_0, LOW);   // turn the LED on (HIGH is the voltage level)
        digitalWrite(LEDPin_1, HIGH);
        digitalWrite(LEDPin_2, LOW);
        digitalWrite(LEDPin_3, HIGH);
        digitalWrite(LEDPin_4, LOW);
        digitalWrite(LEDPin_5, HIGH);
        digitalWrite(LEDPin_6, LOW);
    
        client.publish(TOPIC_LED, "0101010");
        Serial.println("模式1");
        
      }
      else  if(light_time%3==1)
      {
        digitalWrite(LEDPin_0, HIGH);   // turn the LED on (HIGH is the voltage level)
        digitalWrite(LEDPin_1, LOW);
        digitalWrite(LEDPin_2, HIGH);
        digitalWrite(LEDPin_3, LOW);
        digitalWrite(LEDPin_4, HIGH);
        digitalWrite(LEDPin_5, LOW);
        digitalWrite(LEDPin_6, HIGH);
    
        client.publish(TOPIC_LED, "1010101");
        Serial.println("模式2");
    
      }
      else  if(light_time%3==2)
      {
        digitalWrite(LEDPin_0, HIGH);   // turn the LED on (HIGH is the voltage level)
        digitalWrite(LEDPin_1, LOW);
        digitalWrite(LEDPin_2, LOW);
        digitalWrite(LEDPin_3, HIGH);
        digitalWrite(LEDPin_4, LOW);
        digitalWrite(LEDPin_5, LOW);
        digitalWrite(LEDPin_6, HIGH);
    
        client.publish(TOPIC_LED, "1001001");
        Serial.println("模式3");
      }
      
      
    }
  
}
