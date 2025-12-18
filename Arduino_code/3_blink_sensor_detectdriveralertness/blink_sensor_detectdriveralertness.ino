/*
 * Simple Driver Anti-Sleep Alarm System
 * Uses a blink sensor to detect driver alertness
 */

// Pin setup
const int BLINK_PIN = 2;      // Blink sensor input
const int MOTOR_PIN = 13;     // Vibration motor output
const int BUZZER_PIN = 12;    // Buzzer output

// Timing
unsigned long lastBlinkTime = 0;

void setup() {
  // Set pin modes
  pinMode(BLINK_PIN, INPUT);
  pinMode(MOTOR_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  
  // Start with alerts off
  digitalWrite(MOTOR_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);
}

void loop() {
  // Check blink sensor
  if (!digitalRead(BLINK_PIN)) {
    // Blink detected - reset timer and turn off alerts
    lastBlinkTime = millis();
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(MOTOR_PIN, LOW);
  } else {
    // Calculate time since last blink
    unsigned long timeSinceLastBlink = millis() - lastBlinkTime;
    
    // After 3 seconds, activate buzzer
    if (timeSinceLastBlink >= 3000) {
      digitalWrite(BUZZER_PIN, HIGH);
    }
    
    // After 4 seconds, activate motor
    if (timeSinceLastBlink >= 4000) {
      digitalWrite(MOTOR_PIN, HIGH);
    }
  }
}