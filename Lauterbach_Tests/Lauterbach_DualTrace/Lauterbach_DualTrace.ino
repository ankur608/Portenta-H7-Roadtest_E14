/*
#ifdef CORE_CM7             // Start.M7 
#include "RPC_internal.h"

#include <ThreadDebug.h>
 
USBSerial              SerialUSB1(false, "DebugPort");
UsbDebugCommInterface  debugComm(&SerialUSB1);
ThreadDebug            threadDebug(&debugComm, DEBUG_NO_BREAK_IN_SETUP);

int dbgLED; 

void setup() {
   bootM4(); 
   Serial.begin(115200);
   RPC1.begin();
   dbgLED = LEDB; // on-board blue LED
   pinMode(dbgLED, OUTPUT);
}

void loop() {
  
   Serial.println("[M7call]");
   while (RPC1.available()) {
      Serial.write(RPC1.read()); 
   }  
   digitalWrite(dbgLED, LOW); 
   delay(200); 
   digitalWrite(dbgLED, HIGH); 
   delay( rand() % 5000 + 1000); 
}

#endif              // End.M7

*/

#ifdef CORE_CM4             // Start.M4
#include "RPC_internal.h" 
#define Serial RPC1       

#include <ThreadDebug.h>

UartDebugCommInterface debugComm(SERIAL1_TX, SERIAL1_RX, 230400);
ThreadDebug            threadDebug(&debugComm, DEBUG_NO_BREAK_IN_SETUP);  

int myLED; 
  
void setup() {   
   randomSeed(analogRead(A0));
   Serial.begin();   
   dbgLED = LEDR;     // on-board red LED
   pinMode(dbgLED, OUTPUT);
}

void loop() {
   Serial.println("Serial piped through RPC[M4]"); 
  
   digitalWrite(dbgLED, LOW); 
   delay(200); 
   digitalWrite(dbgLED, HIGH); 
   delay( rand() % 5000 + 1000);
}

#endif		// End.M4
