code without calls only msg#include <SoftwareSerial.h>

// Pin definitions
#define RELAY 13
#define BUZZER A0
#define SENSOR_PIN 10
#define SIM_RX 6
#define SIM_TX 5

// SIM module setup
SoftwareSerial sim(SIM_RX, SIM_TX);
int _timeout;
String _buffer;
String phoneNumber = "+91**********"; // -> change with your number

// Button/sensor variables
int sensorStatePrevious = LOW;
unsigned long minSensorDuration = 3000; // Time we wait before the sensor active as long (3 seconds)
unsigned long minSensorDuration2 = 6000; // Time for second stage activation (6 seconds)
unsigned long sensorLongMillis;          // Time in ms when the sensor was active
bool isLongPressActive = false;          // True if it is a long active
const int intervalSensor = 50;           // Time between two readings sensor state
unsigned long previousSensorMillis;      // Timestamp of the latest reading
unsigned long sensorOutDuration;         // Time the sensor is active in ms

// General timing
unsigned long currentMillis;

void setup() {
  delay(3000); // Give modules time to initialize
  
  // Initialize serial communications
  Serial.begin(9600);
  sim.begin(9600);
  
  // Configure pins
  pinMode(SENSOR_PIN, INPUT);
  pinMode(RELAY, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  
  // Reserve memory for string buffer
  _buffer.reserve(100);
  
  // Initialize SIM module
  delay(1000);
  Serial.println("System Started...");
  Serial.println("Press button or use commands: s (SMS), r (Receive)");
}

void loop() {
  currentMillis = millis();
  
  // Handle button/sensor state
  readSensorState();
  
  // Handle serial commands
  handleSerialCommands();
  
  // Check for SIM module responses
  if (sim.available() > 0)
    Serial.write(sim.read());
}

// Function for reading the sensor state
void readSensorState() {
  // If the difference in time between the previous reading is larger than intervalSensor
  if(currentMillis - previousSensorMillis > intervalSensor) {
    // Read the digital value of the sensor (LOW/HIGH)
    int sensorState = digitalRead(SENSOR_PIN);
    
    // If the button has been pressed AND wasn't pressed before AND no long press measurement is ongoing
    if (sensorState == LOW && sensorStatePrevious == HIGH && !isLongPressActive) {
      sensorLongMillis = currentMillis;
      sensorStatePrevious = LOW;
      Serial.println("Button pressed");
    }
    
    // Calculate how long the sensor has been activated
    sensorOutDuration = currentMillis - sensorLongMillis;
    
    // If button is still pressed AND 3 second threshold reached
    if (sensorState == LOW && !isLongPressActive && sensorOutDuration >= minSensorDuration) {
      isLongPressActive = true;
      digitalWrite(RELAY, HIGH);
      Serial.println("Button long pressed - Relay activated");
    }
    
    // If button is still pressed AND 6 second threshold reached 
    if (sensorState == LOW && isLongPressActive && sensorOutDuration >= minSensorDuration2) {
      digitalWrite(BUZZER, HIGH);
      Serial.println("Button extra-long pressed - Buzzer activated");
      
      // Send SMS alert when button is held for 6+ seconds
      SendEmergencyMessage();
    }
    
    // If the sensor is released AND was previously activated
    if (sensorState == HIGH && sensorStatePrevious == LOW) {
      sensorStatePrevious = HIGH;
      isLongPressActive = false;
      digitalWrite(RELAY, LOW);
      digitalWrite(BUZZER, LOW);
      Serial.println("Button released");
    }
    
    // Store the current timestamp
    previousSensorMillis = currentMillis;
  }
}

// Handle commands from Serial monitor
void handleSerialCommands() {
  if (Serial.available() > 0) {
    char command = Serial.read();
    switch (command) {
      case 's':
        SendMessage();
        break;
      case 'r':
        ReceiveMessage();
        break;
    }
  }
}

// Send a predefined message
void SendMessage() {
  Serial.println("Sending Message...");
  sim.println("AT+CMGF=1");    // Sets the GSM Module in Text Mode
  delay(1000);
  sim.println("AT+CMGS=\"" + phoneNumber + "\"\r"); // Mobile phone number to send message
  delay(1000);
  String SMS = "Hello, how are you?";
  sim.println(SMS);
  delay(100);
  sim.println((char)26); // ASCII code of CTRL+Z
  delay(1000);
  _buffer = readSerial();
  Serial.println(_buffer);
}

// Send emergency message when button is long-pressed
void SendEmergencyMessage() {
  Serial.println("Sending Emergency Alert...");
  sim.println("AT+CMGF=1");    // Sets the GSM Module in Text Mode
  delay(1000);
  sim.println("AT+CMGS=\"" + phoneNumber + "\"\r"); // Mobile phone number to send message
  delay(1000);
  String SMS = "EMERGENCY ALERT! Button has been pressed for 6+ seconds.";
  sim.println(SMS);
  delay(100);
  sim.println((char)26); // ASCII code of CTRL+Z
  delay(1000);
  _buffer = readSerial();
}

// Receive message setup
void ReceiveMessage() {
  Serial.println("SIM800L Reading SMS");
  delay(1000);
  sim.println("AT+CNMI=2,2,0,0,0"); // AT Command to receive a live SMS
  delay(1000);
  Serial.println("Waiting for incoming messages...");
}

// Read data from SIM module
String readSerial() {
  _timeout = 0;
  while (!sim.available() && _timeout < 12000) {
    delay(13);
    _timeout++;
  }
  if (sim.available()) {
    return sim.readString();
  }
  return "No response";
}