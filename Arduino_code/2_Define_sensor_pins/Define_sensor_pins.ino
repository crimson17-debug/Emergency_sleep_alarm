// Define sensor pins const int heartRatePin = A0; 
 // Heart rate sensor connected to analog pin A0 const int blinkSensorPin = 2;
  // Eye blink sensor connected to digital pin 2

// Variables to store readings
//  int heartRateValue = 0; 
// bool blinkDetected = false;

void setup() { Serial.begin(9600); 
// Start serial communication at 9600 baud pinMode(blinkSensorPin, INPUT); 

// Set blink sensor pin as input }

void loop() { // Read heart rate sensor value heartRateValue = analogRead(heartRatePin); Serial.print("Heart Rate Sensor Value: "); Serial.println(heartRateValue);

// Read eye blink sensor state
blinkDetected = digitalRead(blinkSensorPin);
if (blinkDetected) {
    Serial.println("Blink Detected!");
}

delay(500); // Delay to avoid excessive serial output

}