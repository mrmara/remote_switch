#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// WiFi credentials
const char *ssid = "VodafoneMrMara";
const char *password = "AntoAleVodafone";

// Define the GPIO pin to control (D1 = GPIO5)
const int controlPin = 3;

// Create a web server on port 8000
ESP8266WebServer server(8000);

// Handler to show the current pin status
void handleRoot()
{
  String status = digitalRead(controlPin) == HIGH ? "HIGH" : "LOW";
  server.send(200, "text/plain", "Pin status: " + status);
}

// Handler to set pin HIGH
void handleSetHigh()
{
  digitalWrite(controlPin, HIGH);
  server.send(200, "text/plain", "Pin set to HIGH");
}

// Handler to set pin LOW
void handleSetLow()
{
  digitalWrite(controlPin, LOW);
  server.send(200, "text/plain", "Pin set to LOW");
}

void setup()
{
  Serial.begin(115200);
  delay(100);

  // Connect to WiFi
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected.");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Route handlers
  server.on("/", HTTP_GET, handleRoot);
  server.on("/setHigh", HTTP_GET, handleSetHigh);
  server.on("/setLow", HTTP_GET, handleSetLow);

  // Start the server
  server.begin();
  Serial.println("Server started on port 8000");
  // Set pin mode and initial state
  Serial.println("Setting pin mode and initial state to LOW");
  pinMode(controlPin, OUTPUT);
  digitalWrite(controlPin, LOW); // default LOW
}

void loop()
{
  server.handleClient();
}
