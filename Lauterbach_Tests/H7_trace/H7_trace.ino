#include <ThreadDebug.h>
USBSerial              SerialUSB1(false, "DebugPort");
UsbDebugCommInterface  debugComm(&SerialUSB1);
//ThreadDebug            threadDebug(&debugComm, DEBUG_BREAK_IN_SETUP);
ThreadDebug            threadDebug(&debugComm, DEBUG_NO_BREAK_IN_SETUP);

bool debugTrace = false;
int var = 0;
// the setup function runs once when you press reset or power the board

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LEDB, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  var += 1;
  digitalWrite(LEDB, LOW);              // turn the Portenta Blue LED on 
  Serial.println("InitialSeq");
  delay(100);                          
  digitalWrite(LEDB, HIGH);             // turn the Portenta Blue LED off 
  delay(100);                       
  Serial.println("BreakSeq");
  if (debugTrace){debugBreak();}           // if debugTrace is true, code stops
}
