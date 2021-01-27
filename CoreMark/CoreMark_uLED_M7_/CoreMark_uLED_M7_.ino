// Original CoreMark code: https://github.com/eembc/coremark
// Original Author: Shay Gal-on

#include <Wire.h>  // Wire_lib for using I2C
#include <SFE_MicroOLED.h>  // Include SFE_MicroOLED library
#define PIN_RESET 9 
#define DC_JUMPER 1 

#include <stdarg.h>

MicroOLED oled(PIN_RESET, DC_JUMPER);    // I2C declaration
float disSpec;
// A way to call the C-only coremark function from Arduino's C++ environment
extern "C" int coremark_main(void);

void setup()
{
	Serial.begin(9600); 
	while (!Serial) ; // wait for Arduino Serial Monitor
	delay(500);
  Wire.begin();
  oled.begin();    // Initialize the OLED
  oled.clear(ALL); 
  oled.display();  
  delay(1000);     
  oled.clear(PAGE);
	
	Serial.println("CoreMark Performance Benchmark");
	Serial.println();
	Serial.println("CoreMark measures how quickly your processor can manage linked");
	Serial.println("lists, compute matrix multiply, and execute state machine code.");
	Serial.println();
	Serial.println("Iterations/Sec is the main benchmark result, higher numbers are better");
	Serial.println("Running.... (usually requires 12 to 20 seconds)");
	Serial.println();
	delay(250);
	coremark_main(); // Running the benchmark-tests.
  delay(100);
}

void loop()
{
  delay(200);
  int middleZ = (oled.getLCDWidth() / 2)-14;
  int middleX = oled.getLCDWidth() / 2;
  int middleY = oled.getLCDHeight() / 2;
  oled.clear(PAGE);
  oled.setCursor(middleZ - (oled.getFontWidth() * (2)),
                 middleY - (oled.getFontHeight() / 2)-14);
  oled.print("CoreMark");
  oled.setCursor(middleZ - (oled.getFontWidth() * (2)-12),
                 middleY - (oled.getFontHeight() / 2)-5);
  oled.print("(M7)");
  
  oled.setCursor(middleX - (oled.getFontWidth() * (2)+10),
                 middleY - (oled.getFontHeight() / 2)+13);
  oled.print(disSpec);
  oled.display();  
}

// CoreMark calls this function to print results.
extern "C" int ee_printf(const char *format, ...)
{
	va_list args;
	va_start(args, format);
	for (; *format; format++) {
		if (*format == '%') {
			bool islong = false;
			format++;
			if (*format == '%') { Serial.print(*format); continue; }
			if (*format == '-') format++; // ignore size
			while (*format >= '0' && *format <= '9') format++; // ignore size
			if (*format == 'l') { islong = true; format++; }
			if (*format == '\0') break;
			if (*format == 's') {
				Serial.print((char *)va_arg(args, int));
			} else if (*format == 'f') {
				Serial.print(va_arg(args, double));
			} else if (*format == 'd') {
				if (islong) Serial.print(va_arg(args, long));
				else Serial.print(va_arg(args, int));
			} else if (*format == 'u') {
				if (islong) Serial.print(va_arg(args, unsigned long));
				else Serial.print(va_arg(args, unsigned int));
			} else if (*format == 'x') {
				if (islong) Serial.print(va_arg(args, unsigned long), HEX);
				else Serial.print(va_arg(args, unsigned int), HEX);
			} else if (*format == 'c' ) {
				Serial.print(va_arg(args, int));
			}
		} else {
			if (*format == '\n') Serial.print('\r');
			Serial.print(*format);
		}
	}
	va_end(args);
	return 1;
}

// CoreMark calls this function to measure elapsed time
extern "C" uint32_t Arduino_millis(void)
{
	return millis();
} 
