// NodeMCU ESP8266 uses RX (GPIO3) and TX (GPIO1) pins for serial communication (UART)

#include <ESP8266WiFi.h>        // Include the Wi-Fi library

#include <ESP8266HTTPClient.h>    
//#include <WiFiClientSecure.h>   // If https
#include <WiFiClient.h>           // If http or local


const char* ssid     = "*****";         // The SSID (name) of the Wi-Fi network you want to connect to
const char* password = "*****";     // The password of the Wi-Fi network

//String serverName = "https://httpbin.org/anything";     // If https
String serverName = "http://192.168.0.7:5000/";           // If http or local

void setup() {
  Serial.begin(115200);         // Start the Serial communication to send messages to the computer
  delay(10);
  Serial.println('\n');
  
  WiFi.begin(ssid, password);             // Connect to the network
  Serial.print("Connecting to ");
  Serial.print(ssid); Serial.println(" ...");

  int i = 0;
  while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
    delay(1000);
    Serial.print(++i); Serial.print(' ');
  }

  Serial.println('\n');
  Serial.println("Connection established!");  
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());         // Send the IP address of the ESP8266 to the computer
}

void loop() {
  if(WiFi.status()== WL_CONNECTED){
      //WiFiClientSecure client;
      WiFiClient client;
      HTTPClient http;

      String serverPath = serverName;
      
      //client.setInsecure();

      // Your Domain name with URL path or IP address with path
      http.begin(client, serverPath.c_str());
        
      // Send HTTP GET request
      int httpResponseCode = http.GET();
      
      if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }

  delay(10000);
}