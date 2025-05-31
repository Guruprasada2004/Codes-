#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>

const char* ssid = "YourWiFiSSID";
const char* password = "YourWiFiPassword";

WebServer server(80);

String message = "Hello from ESP32!";
bool messageChanged = false;

void handleRoot() {
  String html = "<!DOCTYPE html><html><head><title>ESP32 I2C Message</title>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
  html += "<style>body{font-family:Arial,sans-serif;max-width:800px;margin:0 auto;padding:20px;}";
  html += "input,button{padding:10px;font-size:16px;margin:5px 0;}</style></head><body>";
  html += "<h1>ESP32 to Arduino I2C Message</h1>";
  html += "<form action='/send' method='POST'>";
  html += "<input type='text' name='message' value='" + message + "' style='width:100%;'>";
  html += "<button type='submit'>Send to Arduino</button></form>";
  html += "<p>Current message on Arduino: " + message + "</p>";
  html += "</body></html>";
  
  server.send(200, "text/html", html);
}

void handleSend() {
  if (server.hasArg("message")) {
    message = server.arg("message");
    messageChanged = true;
  }
  server.sendHeader("Location", "/");
  server.send(303);
}

void setup() {
  Serial.begin(115200);
  Wire.begin();
  
  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Set up web server
  server.on("/", handleRoot);
  server.on("/send", handleSend);
  server.begin();
}

void loop() {
  server.handleClient();
  
  if (messageChanged) {
    // Send message to Arduino via I2C (character by character)
    Wire.beginTransmission(8); // Address of Arduino slave
    for (size_t i = 0; i < message.length(); i++) {
      Wire.write(message[i]); // Send each character individually
    }
    Wire.endTransmission();
    
    Serial.println("Message sent: " + message);
    messageChanged = false;
  }
  
  delay(100);
}
