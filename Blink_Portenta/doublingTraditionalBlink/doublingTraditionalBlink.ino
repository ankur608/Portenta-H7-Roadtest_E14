/*
//delay(CoreMark1.0)M7 Core
 
void setup() {
  bootM4();
  pinMode(LEDR, OUTPUT);
  pinMode(LEDB, OUTPUT);
}
 
void loop() {
  digitalWrite(LEDR, LOW);
  digitalWrite(LEDB, LOW);
  delay(1130.26);
  digitalWrite(LEDR, HIGH);
  digitalWrite(LEDB, HIGH);
  delay(1130.26);
}
// 
*/  
//delay(CoreMark1.0)M4 Core
 
void setup() {
  pinMode(LEDG, OUTPUT);
}
 
void loop() {
  digitalWrite(LEDG, LOW);
  delay(309.72);
  digitalWrite(LEDG, HIGH);
  delay(309.72);
}
