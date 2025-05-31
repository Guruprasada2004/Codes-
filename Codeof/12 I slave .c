#include <Wire.h>

String receivedMessage = "";

void setup() {
  // Start serial communication
  Serial.begin(115200);
  
  // Initialize I2C as a slave with address 8
  Wire.begin(8);
  
  // Register the function to handle received data
  Wire.onReceive(receiveData);
  
  Serial.println("Arduino is ready to receive messages from ESP32...");
}

void loop() {
  // Nothing to do here, just waiting for data from the ESP32
}

void receiveData(int byteCount) {
  receivedMessage = "";
  
  // Read each byte received over I2C
  while (Wire.available()) {
    char c = Wire.read();
    receivedMessage += c;
  }
  
  // Display the received message on the Serial Monitor
  Serial.print("Received message: ");
  Serial.println(receivedMessage);
}
