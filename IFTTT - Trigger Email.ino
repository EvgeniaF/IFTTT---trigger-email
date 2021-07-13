
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <DHT.h>

#define DHTTYPE DHT11

int sensePin=2;

DHT HT(sensePin, DHTTYPE);
HTTPClient http;

float humidity;
float temp;

WiFiClient client;

#ifndef STASSID
#define STASSID "" //network name
#define STAPSK  "" //network password
#endif

const char* ssid     = STASSID;
const char* password = STAPSK;

int status = WL_IDLE_STATUS;

String key = ""; //your webhooks key
String event_name = "temp_limit"; //your webhooks event name
String value1 = "triggered"; //value1 that you want to send when the event is triggered

void setup() {
  Serial.begin(115200);
  
  WiFi.begin(ssid, password); 
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Waiting to connect...");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  
  HT.begin();
  
  delay(500);
}

void loop() {
  
  humidity = HT.readHumidity();
  temp = HT.readTemperature();

  if (temp > 23.00){
    http.begin("http://maker.ifttt.com/trigger/"+event_name+"/with/key/"+key+"?value1="+value1);
    http.GET();
    http.end();
    Serial.println("Sent");
  }
    
  
  Serial.print("Humidity: ");
  Serial.println(humidity);
  Serial.print("Temperature: ");
  Serial.println(temp);
  
  // Wait a few seconds between measurements.
  delay(25000);
 
}
