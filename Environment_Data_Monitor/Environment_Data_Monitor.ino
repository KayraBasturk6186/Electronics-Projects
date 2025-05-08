#include <WiFi.h>
#include <DHT.h>

// Pin configuration
#define DHTPIN 13
#define DHTTYPE DHT11
#define LDRPIN 34
#define THERMISTORPIN 35

// Wi-Fi credentials
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// Web server on port 80
WiFiServer server(80);

// DHT sensor setup
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  delay(1000);  // Allow serial to stabilize
  dht.begin();

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
  Serial.print("ESP32 IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("Client connected!");
    String request = client.readStringUntil('\r');
    Serial.println(request);
    client.flush();

    // Read sensor data
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();
    int lightLevel = analogRead(LDRPIN);
    int thermistorRaw = analogRead(THERMISTORPIN);

    // Send HTTP response
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("Connection: close");
    client.println();

    // HTML content
    client.println("<!DOCTYPE html><html><head>");
    client.println("<title>ESP32 Sensor Monitor</title>");
    client.println("<meta http-equiv='refresh' content='5'>");
    client.println("<style>body{font-family:sans-serif;text-align:center;padding:20px;}h1{color:#0077cc;}p{font-size:18px;}</style>");
    client.println("</head><body>");
    client.println("<h1>ESP32 Sensor Readings</h1>");
    client.println("<p><strong>Temperature:</strong> " + String(temperature) + " °C</p>");
    client.println("<p><strong>Humidity:</strong> " + String(humidity) + " %</p>");
    client.println("<p><strong>Light Level:</strong> " + String(lightLevel) + " (Raw)</p>");
    client.println("<p><strong>Thermistor Reading:</strong> " + String(thermistorRaw) + " (Raw)</p>");
    client.println("<p><em>Page refreshes every 5 seconds</em></p>");
    client.println("</body></html>");

    client.stop();
    Serial.println("Client disconnected");
  }
}
