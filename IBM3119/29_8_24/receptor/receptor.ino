// Include Libraries
#include <esp_now.h>
#include <WiFi.h>

// Define a data structure
typedef struct struct_message {
  char a[32];
  int b;
  float c;
  bool d;
} struct_message;

// Create a structured object
struct_message myData;

// Callback function executed when data is received
void OnDataRecv(const esp_now_recv_info *info, const uint8_t *incomingData, int len) {
  Serial.print("Bytes received: ");
  Serial.println(len);

  if (len == sizeof(myData)) {
    memcpy(&myData, incomingData, sizeof(myData));
    Serial.print("Character Value: ");
    Serial.println(myData.a);
    Serial.print("Integer Value: ");
    Serial.println(myData.b);
    Serial.print("Float Value: ");
    Serial.println(myData.c);
    Serial.print("Boolean Value: ");
    Serial.println(myData.d);
    Serial.println();
  } else {
    Serial.println("Received data size does not match expected size.");
  }
}

void setup() {
  // Set up Serial Monitor
  Serial.begin(115200);
  
  // Set ESP32 as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Initialize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Register callback function
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  // Keep the loop empty as all work is done in the callback
}
