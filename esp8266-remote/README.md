# ESP8266 remote control

To add to the remote control abilities of our robot we use a cheap esp8266 module ([NodeMCU Mini D1](https://thegioiic.com/products/esp-12f-esp8266-thu-phat-wifi-mini-d1-nodemcu)) for 69.000 or 2.98 USD to create a web interface and WiFi server that any laptop or smartphone can connect with and control the robot.

The 5V are provided by the arduino over the 4-Pin Bluetooth connector. The serial port with 9600 Baud connects them both.

## Interface

That's how it looks like:



## Code for the esp8266

``` c
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
 delay(500);
 Serial.print(".");
}
Serial.println("");
Serial.println("WiFi connected");
 
// Start the server
server.begin();
Serial.println("Server started");
 
// Print the IP address
Serial.println(WiFi.localIP());
```
