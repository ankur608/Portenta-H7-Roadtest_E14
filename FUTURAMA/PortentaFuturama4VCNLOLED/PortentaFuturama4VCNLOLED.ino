#include <Wire.h>
#include <SFE_MicroOLED.h>  // Include the SFE_MicroOLED library
#include "bitmaps.h"
#define PIN_RESET 9  
#define DC_JUMPER 1

#include "SparkFun_VCNL4040_Arduino_Library.h"
VCNL4040 proximitySensor;
MicroOLED oled(PIN_RESET, DC_JUMPER);    // I2C declaration

void drawLila();
void drawBender();
void drawAmy();
void drawZoid();
void drawProf();
void drawPhil();
void drawBanner();

void setup()
{
  delay(100);
  Serial.begin(115200);
  Wire.begin();
  proximitySensor.begin();
  oled.begin();    // Initialize the OLED
  oled.clear(ALL);
  oled.display();
  delay(2000);
  oled.clear(PAGE); // Clear the buffer.
}


void loop()
{
    unsigned int proxVal = proximitySensor.getProximity(); 
    if (proxVal>=10000)
    {
      drawProf();
    }
    if (proxVal<10000 && proxVal>=5000)
    {
      drawLila();
    }
    if (proxVal<5000 && proxVal>=1000)
    {
      drawBender();
    }
    if (proxVal<1000 && proxVal>=500)
    {
      drawAmy();
    }
    if (proxVal<500 && proxVal>=100)
    {
      drawZoid();
    }
    if (proxVal<100 && proxVal>=10)
    {
      drawPhil();
    }
    if (proxVal<10)
    {
      drawBanner();
    }    
}
