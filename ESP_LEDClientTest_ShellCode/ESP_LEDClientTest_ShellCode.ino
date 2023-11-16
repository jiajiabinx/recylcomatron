/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp8266-client-server-wi-fi/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

#include <ESP8266WiFiMulti.h>
ESP8266WiFiMulti WiFiMulti;

const char* ssid = "walle_wifi";
const char* password = "eva123456";

//Your IP address or domain name with URL path
const char* serverNameBlue = "http://192.168.4.1/bluebutton";
const char* serverNameGreen = "http://192.168.4.1/greenbutton";
const char* serverNameRed = "http://192.168.4.1/redbutton";
const char* serverNameYellow = "http://192.168.4.1/yellowbutton";

String BlueValString;
int BlueVal;
String GreenValString;
int GreenVal;
String RedValString;
int RedVal;
String YellowValString;
int YellowVal;

unsigned long previousMillis = 0;
const long interval = 5000; 


int BlueLEDPin = 12;
int GreenLEDPin = 14;
int RedLEDPin = 4;
int YellowLEDPin = 5;

void setup() {
  pinMode(BlueLEDPin,OUTPUT);
  pinMode(GreenLEDPin,OUTPUT);
  pinMode(RedLEDPin,OUTPUT);
  pinMode(YellowLEDPin,OUTPUT);
  
  Serial.begin(115200);
  Serial.println();
 
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Connected to WiFi");
}

void loop() {
  unsigned long currentMillis = millis();
  
  //if(currentMillis - previousMillis >= interval) {
     // Check WiFi connection status
    if ((WiFiMulti.run() == WL_CONNECTED)) {
      BlueValString = httpGETRequest(serverNameBlue);     
      BlueVal = BlueValString.toInt();
      digitalWrite(BlueLEDPin,BlueVal);

      GreenValString = httpGETRequest(serverNameGreen);     
      GreenVal = GreenValString.toInt();
      digitalWrite(GreenLEDPin,GreenVal);

      RedValString = httpGETRequest(serverNameRed);  
      RedVal = RedValString.toInt();
      digitalWrite(RedLEDPin,RedVal);

      YellowValString = httpGETRequest(serverNameYellow);          
      YellowVal = YellowValString.toInt();
      digitalWrite(YellowLEDPin,YellowVal);      

      Serial.println("Blue Button Val is: " + BlueValString + " | GreenButton Val is: " + GreenValString + " | Red Button Val is: " + RedValString + " | Yellow Button Val is: " + YellowValString);       
      
      // save the last HTTP GET Request
      //previousMillis = currentMillis;
    }
    else {
      Serial.println("WiFi Disconnected");
    }
  //}
}

String httpGETRequest(const char* serverName) {
  WiFiClient client;
  HTTPClient http;
    
  // Your IP address with path or Domain name with URL path 
  http.begin(client, serverName);
  
  // Send HTTP POST request
  int httpResponseCode = http.GET();
  
  String payload = "--"; 
  
  if (httpResponseCode>0) {
//    Serial.print("HTTP Response code: ");
//    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}
