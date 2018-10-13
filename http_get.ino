/*
  Connect ESP32 to AskSensors
 * Description:  This sketch connects to a website (https://asksensors.com) using an ESP32 Wifi module.
 *  Author: https://asksensors.com, 2018
 *  github: https://github.com/asksensors
 */
 
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>

WiFiMulti WiFiMulti;
HTTPClient ask;
// TODO: user config
const char* ssid     = "............."; //Wifi SSID
const char* password = "............."; //Wifi Password
String apiKeyIn = "............."; // API Key

const char* host = "asksensors.com";  // host
const int httpPort = 80;      // port
  
void setup(){
  
  // open serial
  Serial.begin(9600);
  Serial.println("*****************************************************");
  Serial.println("********** Program Start : Connect ESP32 to AskSensors.");
  Serial.println("Wait for WiFi... ");

  // connecting to the WiFi network
  WiFiMulti.addAP(ssid, password);
  while (WiFiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  // connected
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}


void loop(){

  // Use WiFiClient class to create TCP connections
  WiFiClient client;


  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }else {

    // Create a URL for the request
  String url = "https://asksensors.com/api.asksensors/write/";
  url += apiKeyIn;
  url += "?module1=";
  url += random(10, 100);
  
  Serial.print("********** requesting URL: ");
  Serial.println(url);
 
   // ask.begin("https://asksensors.com/api.asksensors/write/ONKMHCC38YT74K5NGT8JC1GF8B1O9QKT?module1=100"); //Specify the URL
   ask.begin(url); //Specify the URL
  
    //Check for the returning code
    int httpCode = ask.GET();          
 
    if (httpCode > 0) { 
 
        String payload = ask.getString();
        Serial.println(httpCode);
        Serial.println(payload);
      } else {
      Serial.println("Error on HTTP request");
    }
 
    ask.end(); //End 
    Serial.println("********** End ");
    Serial.println("*****************************************************");

  }

  client.stop();  // stop client
  
  delay(20000);    // delay
}


