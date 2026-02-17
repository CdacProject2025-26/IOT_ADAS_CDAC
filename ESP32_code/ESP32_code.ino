#include <WiFi.h>
#include <HTTPClient.h>

// ===== WiFi Credentials =====
const char* ssid = "januu";
const char* password = "0123456788";

// ===== ThingSpeak Details =====
String apiKey = "6IIDO3KIWVZVBNWC";
const char* server = "http://api.thingspeak.com/update";

void setup() {
  Serial.begin(115200);
  delay(2000);

  Serial.println("ESP32 Starting...");
  
  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {

  // Generate dummy test value (replace with STM32 data later)
  int testValue = random(10, 100);

  if (WiFi.status() == WL_CONNECTED) {

    HTTPClient http;

    String url = String(server) + "?api_key=" + apiKey + "&field1=" + String(testValue);

    http.begin(url);
    int httpResponseCode = http.GET();

    Serial.print("Sent Value: ");
    Serial.println(testValue);

    Serial.print("HTTP Response Code: ");
    Serial.println(httpResponseCode);

    http.end();
  }
  else {
    Serial.println("WiFi Disconnected!");
  }

  delay(15000);   // ThingSpeak requires minimum 15 seconds
}
