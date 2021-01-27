#include <AnalogSmooth.h>

const int DAC_PIN = A6;

// Parameters
const int DAC_BITS = 12;        // 12-bit DAC
const int BUF_SIZE = 360;       // Each degree
const float AMPLITUDE = 0.5;    // Normalized to max GPIO voltage
const float OFFSET = 0.5;       // Normalized to max GPIO voltage
const float FREQUENCY = 500.0;  // Hz (not exact due to overhead DAC instructions)

// Calculate delay between DAC updates
const uint16_t DELAY_US = (uint16_t)(((1 / FREQUENCY) / BUF_SIZE) * 1000000);

// Calculate max value of DAC bits
uint16_t dac_range = pow(2, DAC_BITS) - 1;

// Global sinewave buffer
uint16_t sine_buf[BUF_SIZE];

// Defaults to window size 10
AnalogSmooth as = AnalogSmooth();
// Window size can range from 1 - 100
AnalogSmooth as100 = AnalogSmooth(100);

void setup() {
  Serial.begin(115200);
  // Configure DAC with maximum resolution
  analogWriteResolution(DAC_BITS);

  // Pre-calculate sinewave and store to lookup table
  calc_sinewave(dac_range, sine_buf, BUF_SIZE);
}

void loop() {

  // Write sinewave to DAC at each degree
  for ( int i = 0; i < BUF_SIZE; i++ ) {
    analogWrite(DAC_PIN, sine_buf[i]);
    //Serial.print("DAC_OUT: ");
    Serial.println(analogRead(A6)); 

    float analog = analogRead(A6);
    float analogSmooth = as.smooth(analog);
    Serial.print("Smooth (10): ");  
    Serial.println(analogSmooth);

    // Smoothing with window size 100
    float analogSmooth100 = as100.analogReadSmooth(A6);
    Serial.print("Smooth (100): ");  
    Serial.println(analogSmooth100);
    delayMicroseconds(DELAY_US);
  }
}

// Calculate sinewave
void calc_sinewave(uint16_t range, uint16_t * sinewave, int len) {
  for ( int i = 0; i < len; i++ ) {
    double rad = (PI * i) / 180.0;
    sinewave[i] = (uint16_t)(dac_range * ((AMPLITUDE * cos(rad)) + OFFSET));
  }
}
