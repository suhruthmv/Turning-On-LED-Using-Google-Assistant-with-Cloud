#include <ThingSpeak.h>
#include <ESP8266WiFi.h>


// Network Parameters
const char* ssid     = "Testing";
const char* password = "123456789";

// ThingSpeak information
char* server = "api.thingspeak.com";
unsigned long channelID =1034726;
char* readAPIKey = "AATMXQYC0HYLS9UD";
unsigned int dataFieldOne = 1;// Field to write temperature data

// Global variables
// These constants are device specific.  You need to get them from the manufacturer or determine them yourself.
float  received_data;
WiFiClient client;

void setup() {
  pinMode(D0,OUTPUT);

  Serial.begin(115200);
  Serial.println("Start");
  connectWiFi();
  

  // Read the constants at startup.
  received_data = readTSData( channelID, dataFieldOne );
  //Serial.println(aConst);
  delay(1000);
}

void loop() {

  delay(10000);
  Serial.println("Waiting...");
  //reading data from thing speak
  received_data = readTSData( channelID, dataFieldOne );
  Serial.println(received_data);
  if(received_data==1)
  {
     Serial.println("Turning On...");
    digitalWrite(D0,HIGH);
  }
  if(received_data==0)
  {
    Serial.println("Turning Off...");
    digitalWrite(D0,LOW);
  }


}

int connectWiFi() {
  WiFi.begin( ssid, password );
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println( "Connected" );
  ThingSpeak.begin( client );
}

float readTSData( long TSChannel, unsigned int TSField ) {

  float data =  ThingSpeak.readFloatField( TSChannel, TSField, readAPIKey );
  Serial.println( " Data read from ThingSpeak: " + String( data, 9 ) );
  return data;

}
