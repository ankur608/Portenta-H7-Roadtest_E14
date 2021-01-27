//DAC_meas.
void setup() {
  analogWriteResolution(12);
  randomSeed(A1);  // random Analog reading 
  Serial.begin(115200);
  pinMode(A0, OUTPUT);
  // pinMode(A6, INPUT);  //A6 (default) Analog input
}

void loop() {
  int randomNum  = rand() % 1024;  // random number between 0 and 1023
  DACval(randomNum);
  delay(500);
}

void DACval(int dac_value){
  analogWrite(DAC, dac_value);
  Serial.print("DAC[A0] : ");
  Serial.print(dac_value);
  Serial.print("\t");
  Serial.print("[A6]: ");
  Serial.println(analogRead(A6));
}
