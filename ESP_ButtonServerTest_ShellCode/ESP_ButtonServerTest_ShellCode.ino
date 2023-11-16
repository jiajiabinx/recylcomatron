/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp8266-nodemcu-client-server-wi-fi/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

// Import required libraries
#include <ESP8266WiFi.h>
#include "ESPAsyncWebServer.h"


// Set your access point network credentials
const char* ssid = "walle_wifi"; //create a server name (the wifi name you will connect to)
const char* password = "eva123456"; //create a unique password that you and your teammates know

// Create AsyncWebServer object on port 80
// In our case, we will use port 80, which is the default HTTP port. 
// Thus, since our client will be a web browser, 
// it will use port 80 by default and we don’t need to explicitly specify it. 
// In case we use a port different than 80, 
// we need to specify it when contacting the server using a web browser.
AsyncWebServer server(80); //asynchronous web server allows other things to happen after signal is sent

// update pins as needed for your particular configuration
// recall the pin numbers refer to the GPIO names, not to the names written on the board
int GreenButtonPin = 12;
int BlueButtonPin = 14;
int RedButtonPin = 4;
int YellowButtonPin = 5;

int GreenVal = 0;  
int BlueVal = 0;    
int RedVal = 0;
int YellowVal = 0;


String readBlueButton() {

  BlueVal = digitalRead(BlueButtonPin);
  Serial.print("Blue Val is: ");
  Serial.println(BlueVal);

  return String(BlueVal);

}

String readGreenButton() {
  
  GreenVal = digitalRead(GreenButtonPin);
  Serial.print("Green Val is: ");
  Serial.println(GreenVal);

  return String(GreenVal);

}

String readRedButton() {
  RedVal = digitalRead(RedButtonPin);
  Serial.print("Red Val is: ");
  Serial.println(RedVal);

  return String(RedVal);

}

String readYellowButton() {

  YellowVal = digitalRead(YellowButtonPin);
  Serial.print("Yellow Val is: ");
  Serial.println(YellowVal);

  return String(YellowVal);
}

void setup(){
  pinMode(GreenButtonPin,INPUT);
  pinMode(BlueButtonPin,INPUT);
  pinMode(RedButtonPin,INPUT);
  pinMode(YellowButtonPin,INPUT);   
  
  // Serial port for debugging purposes
  Serial.begin(115200);
  Serial.println();

  Serial.println("you are here");
  
  // Setting the ESP as an access point
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP); // Make sure to note down the IP address! 

  /*
   * Then, handle the routes where the ESP8266 will be listening for incoming requests.

    For example, when the ESP8266 server receives a request on the /bluebutton URL, 
    it sends the string returned by the blueButton() 
    function as a char (that’s why we use the c_str() method.
   */


  // server.on
  server.on("/bluebutton", HTTP_GET,[](AsyncWebServerRequest *request){
    request -> send_P(200, "text/plain", readBlueButton().c_str());
    });

   server.on("/greenbutton", HTTP_GET,[](AsyncWebServerRequest *request){
    request -> send_P(200, "text/plain", readGreenButton().c_str());
    });

   server.on("/yellowbutton", HTTP_GET,[](AsyncWebServerRequest *request){
    request -> send_P(200, "text/plain", readYellowButton().c_str());
    });
    
     server.on("/redbutton", HTTP_GET,[](AsyncWebServerRequest *request){
    request -> send_P(200, "text/plain", readRedButton().c_str());
    });
      
  // Start server
  server.begin();

}
 
void loop(){
  
}
