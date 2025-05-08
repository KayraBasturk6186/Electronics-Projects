  ESP32 Sensor Monitoring Web Server
This project uses an ESP32 microcontroller to create a simple yet effective wireless sensor monitoring system. It reads environmental data from multiple sensors and hosts a lightweight web server, allowing users to view live sensor readings from any device on the same Wi-Fi network.

  Features:
Temperature & Humidity Monitoring via a DHT11 sensor
Light Level Detection using an analog photoresistor (LDR)
Temperature Approximation using an analog thermistor
Data is updated and displayed via a web page that auto-refreshes every 5 seconds
Designed for use with the Freenove ESP32-WROVER and an extension board
Sensor data also printed to the Serial Monitor for debugging

  How It Works:
The ESP32 connects to a specified Wi-Fi network.
It reads values from:
DHT11 (temperature, humidity)
Photoresistor (light level). 
Thermistor (raw temperature-related value).
It starts a web server at the assigned local IP address. 
Users can view sensor data by visiting this IP in any web browser on the same network.

  
  Hardware Connections:
DHT11:
VCC → 3.3V
GND → GND
Data → GPIO13 (with 10K pull-up resistor)

Photoresistor:
One leg → 3.3V
Other leg → GPIO34 and 10K resistor to GND

Thermistor:
One leg → 3.3V
Other leg → GPIO35 and 10K resistor to GND
