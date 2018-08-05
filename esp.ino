#include<stdlib.h>
#include<string.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FS.h>
#include <WebSocketsServer.h>
ESP8266WebServer Hello(80);
WebSocketsServer webSocket = WebSocketsServer(81);
String getContentType(String filename);
bool handleFileRead(String path);
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length)
{
  switch(type) {
    case WStype_DISCONNECTED:
      Serial.printf("[%u] Disconnected!\r\n", num);
      break;
    case WStype_CONNECTED:
      {
        Serial.println("Connected.....\r\n");
      }
      break;
    case WStype_TEXT:
    {
    Serial.write((char*)payload);
  }
    
      break;
    case WStype_BIN:
      Serial.printf("[%u] get binary length: %u\r\n", num, length);
      hexdump(payload, length);

      // echo data back to browser
      webSocket.sendBIN(num, payload, length);
      break;
    default:
      Serial.printf("Invalid WStype [%d]\r\n", type);
      break;
  }
} 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(10);
  WiFi.mode(WIFI_AP);
  WiFi.softAP("Hello","12345678");
   Serial.println("HTTP server started");
   for(uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] BOOT WAIT %d...\r\n", t);
    Serial.flush();
    delay(1000);
}
  SPIFFS.begin();
   Hello.onNotFound([]() {                            
    if (!handleFileRead(Hello.uri()))                 
      Hello.send(404, "text/plain", "404: Not Found"); 
  });
  Hello.begin();                           
 webSocket.begin();
 webSocket.onEvent(webSocketEvent);
}


void loop() {
  // put your main code here, to run repeatedly:
   webSocket.loop();
   Hello.handleClient();
}
String getContentType(String filename) { // convert the file extension to the MIME type
  if (filename.endsWith(".html")) return "text/html";
  else if (filename.endsWith(".css")) return "text/css";
  else if (filename.endsWith(".js")) return "application/javascript";
  else if (filename.endsWith(".ico")) return "image/x-icon";
  return "text/plain";
}

bool handleFileRead(String path) { // send the right file to the client (if it exists)
  Serial.println("handleFileRead: " + path);
  if (path.endsWith("/")) path += "index.html";         // If a folder is requested, send the index file
  String contentType = getContentType(path);            // Get the MIME type
  if (SPIFFS.exists(path)) {                            // If the file exists
    File file = SPIFFS.open(path, "r");                 // Open it
    size_t sent = Hello.streamFile(file, contentType); // And send it to the client
    file.close();                                       // Then close the file again
    return true;
  }
  Serial.println("\tFile Not Found");
  return false;                                         // If the file doesn't exist, return false
}
