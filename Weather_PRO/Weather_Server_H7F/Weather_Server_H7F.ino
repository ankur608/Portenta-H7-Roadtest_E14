#include <WiFi.h>

#include <Wire.h>
#include "SparkFunBME280.h"
#include <SparkFunCCS811.h>
#define CCS811_ADDR 0x5B //Default I2C Address
#define PIN_NOT_WAKE 5

//Global sensor objects
CCS811 myCCS811(CCS811_ADDR);
BME280 mySensor;
const char* ssid     = "Portenta H7" // SSID
const char* password = "STM32H747XI" // PASS
int keyIndex = 0;             // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;
WiFiServer server(80);

#define SEALEVELPRESSURE_HPA (1013.25)

//Adafruit_BME280 bme; // I2C

// Variable to store the HTTP request
String header;

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

void setup() {
  Serial.begin(115200);
  bool status;
  Serial.println("Reading basic values from BME280");
  Wire.begin();
  if (mySensor.beginI2C() == false) //Begin communication over I2C
  {
    Serial.println("The sensor did not respond. Please check wiring.");
    while(1); //Freeze
  }
  CCS811Core::status returnCode = myCCS811.begin();
  
  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop(){
  WiFiClient client = server.available();   // Listen for incoming clients
  //Calling this function updates the global tVOC and eCO2 variables
  myCCS811.readAlgorithmResults();
  getSensors();
  if (client) {                             // If a new client connects,
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected() && currentTime - previousTime <= timeoutTime) {  // loop while the client's connected
      currentTime = millis();
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the table 
            client.println("<style>body { text-align: center; font-family: \"Trebuchet MS\", Cambria; background-color: #404040; color: #b2f71b;}");
            client.println("table { border-collapse: collapse; width:100%; margin-left:auto; margin-right:auto; }");
            client.println("th { padding: 12px; background-color: #f09930; color: #1f1d1d; }");
            client.println("tr { border: 1px solid #404040; padding: 12px; }");
            client.println("tr:hover { background-color: #4b4c57; }");
            client.println("td { border: none; padding: 12px; }");
            client.println(".sensor { color:white; font-weight: bold; background-color: #404040; padding: 1px; }");
            client.println("table { border-collapse: collapse; width:40%; margin-left:auto; margin-right:auto; }");
            client.println("th { padding: 12px; background-color: #e6c730; color: #0b0b0d; }");
            
            // Web Page Heading
            client.println("</style></head><body><h1>WEATHER PRO</h1>");
            client.println("<table><tr><th>PARAMETER</th><th>VALUE</th></tr>");
            client.println("<tr><td>Temperature (C)</td><td><span class=\"sensor\">");
            //client.println(bme.readTemperature());
            client.println(mySensor.readTempC());
            client.println(" *C</span></td></tr>");  
            client.println("<tr><td>Temperature (F)</td><td><span class=\"sensor\">");
            //client.println(1.8 * bme.readTemperature() + 32);
            client.println(mySensor.readTempF());
            client.println(" *F</span></td></tr>");       
            client.println("<tr><td>Pressure</td><td><span class=\"sensor\">");
            //client.println(bme.readPressure() / 100.0F);
            client.println(mySensor.readFloatPressure());
            client.println(" hPa</span></td></tr>");
            client.println("<tr><td>Altitude</td><td><span class=\"sensor\">");
            //client.println(bme.readAltitude(SEALEVELPRESSURE_HPA));
            client.println(mySensor.readFloatAltitudeMeters());
            client.println(" m</span></td></tr>"); 
            client.println("<tr><td>Humidity</td><td><span class=\"sensor\">");
            //client.println(bme.readHumidity());
            client.println(mySensor.readFloatHumidity());
            client.println(" %</span></td></tr>");           
            client.println("<table><tr><th>Air-Quality</th><th>[CCS811]</th></tr>");
            client.println("<tr><td>CO2 Concentration</td><td><span class=\"sensor\">");
            client.println(myCCS811.getCO2());
            client.println(" ppm</span></td></tr>");
            client.println("<tr><td>TVOC Concentration</td><td><span class=\"sensor\">");
            client.println(myCCS811.getTVOC());
            client.println(" ppb</span></td></tr>");
            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}

void getSensors()
{
  Serial.print("Humidity: ");
  Serial.print(mySensor.readFloatHumidity(), 0);

  Serial.print(" Pressure: ");
  Serial.print(mySensor.readFloatPressure(), 0);

  Serial.print(" Altitude: ");
  Serial.print(mySensor.readFloatAltitudeMeters(), 1);
  //Serial.print(mySensor.readFloatAltitudeFeet(), 1);

  Serial.print(" Temperature: ");
  Serial.print(mySensor.readTempC(), 2);
  Serial.print(mySensor.readTempF(), 2);

  //getCO2() gets the previously read data from the library
  Serial.println("CCS811 data:");
  Serial.print(" CO2 concentration : ");
  Serial.print(myCCS811.getCO2());
  Serial.println(" ppm");

  //getTVOC() gets the previously read data from the library
  Serial.print(" TVOC concentration : ");
  Serial.print(myCCS811.getTVOC());
  Serial.println(" ppb");
  
  Serial.println();

  delay(1000);
}
