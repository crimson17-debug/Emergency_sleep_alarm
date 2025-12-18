#include <SoftwareSerial.h>

#define SENSOR_PIN 2     // Eye blink sensor pin

#define MOTOR_PIN 8      // Motor control pin

#define BUZZER_PIN 9     // Buzzer control pin

#define GSM_TX_PIN 5    // GSM module TX pin

#define GSM_RX_PIN 6    // GSM module RX pin

const unsigned long EYE_CLOSE_THRESHOLD = 1000;  // 1 second threshold for motor stop

const unsigned long SMS_ALERT_THRESHOLD = 5000;  // 5 seconds threshold for SMS alert

const char* PHONE_NUMBER = "+91 938XXXXXXX";  // Replace with your phone number

SoftwareSerial gsmSerial(GSM_TX_PIN, GSM_RX_PIN); // RX, TX for GSM module

unsigned long eyeClosedStartTime = 0; // Time when eyes were first detected as closed

bool isEyesClosed = false;            // Flag to track the state of eye closure

bool smsAlertSent = false;            // Flag to track if SMS alert has been sent



void setup() {

  pinMode(MOTOR_PIN, OUTPUT);

  pinMode(BUZZER_PIN, OUTPUT);

  pinMode(SENSOR_PIN, INPUT); // Use INPUT_PULLUP if needed for a passive sensor

  

  // Initial state: motor running, buzzer off

  digitalWrite(MOTOR_PIN, HIGH);

  digitalWrite(BUZZER_PIN, LOW);

  

  Serial.begin(9600);   // Initialize serial communication for debugging

  gsmSerial.begin(9600); // Initialize GSM module communication

  

  Serial.println("Drowsiness Detection System with GSM Alert");

  initGSM(); // Initialize GSM module

}



void loop() {

  bool currentEyeState = !digitalRead(SENSOR_PIN); // LOW means eyes are closed

  Serial.print("Sensor State: ");

  Serial.println(currentEyeState ? "Closed" : "Open");

  

  if (currentEyeState) {

    // Eyes are closed

    if (!isEyesClosed) {

      eyeClosedStartTime = millis(); // Record the time when eyes were first detected as closed

      isEyesClosed = true;

      

      // Only turn on buzzer if SMS hasn't been sent

      if (!smsAlertSent) {

        digitalWrite(BUZZER_PIN, HIGH); // Turn on buzzer immediately

        Serial.println("Buzzer ON - Eyes Closed");

      }

    }

    

    unsigned long eyeClosedDuration = millis() - eyeClosedStartTime;

    

    // Check if the eyes have been closed for longer than the motor threshold

    if (eyeClosedDuration >= EYE_CLOSE_THRESHOLD) {

      digitalWrite(MOTOR_PIN, HIGH);  // Stop the motor after threshold

      Serial.println("ALERT: Extended Eye Closure Detected! Motor Stopped.");

    }

    

    // Check if the eyes have been closed long enough to send SMS and haven't sent one yet

    if (eyeClosedDuration >= SMS_ALERT_THRESHOLD && !smsAlertSent) {

      sendSMS("HELP! Driver drowsiness detected!");

      smsAlertSent = true; // Mark that we've sent the SMS

      digitalWrite(BUZZER_PIN, LOW); // Turn off buzzer after SMS is sent

      Serial.println("SMS Alert Sent! Buzzer turned OFF.");

    }

  } else {

    // Eyes are open

    if (isEyesClosed) {

      isEyesClosed = false;

      

      // Only turn off buzzer if SMS hasn't been sent

      if (!smsAlertSent) {

        digitalWrite(BUZZER_PIN, LOW); // Turn off the buzzer

      }

      

      digitalWrite(MOTOR_PIN, LOW); // Restart the motor immediately

      Serial.println("Eyes Open, Motor Running");

    }

  }

}



void initGSM() {

  Serial.println("Initializing GSM module...");

  delay(1000);

  

  gsmSerial.println("AT"); // Test AT command

  delay(1000);

  

  gsmSerial.println("AT+CMGF=1"); // Set SMS text mode

  delay(1000);

  

  Serial.println("GSM module initialized");

}



void sendSMS(const char* message) {

  Serial.println("Sending SMS...");

  

  gsmSerial.println("AT+CMGF=1"); // Set SMS text mode

  delay(1000);

  

  // Command to send SMS

  gsmSerial.print("AT+CMGS=\"");

  gsmSerial.print(PHONE_NUMBER);

  gsmSerial.println("\"");

  delay(1000);

  

  // SMS content

  gsmSerial.print(message);

  delay(100);

  gsmSerial.write(26); // ASCII code for CTRL+Z to end SMS

  

  Serial.println("SMS sent!");

  delay(1000);

}