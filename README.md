# 🚨 DROWSY_TECH - Emergency Sleep Alarm

> An IOT-based safety system designed to detect driver fatigue and prevent road accidents.

## About The Project
This repository contains the development lifecycle and final implementation of **DROWSY_TECH**, a smart anti-sleep alarm system. 

The project was developed to address the critical issue of driver drowsiness. It utilizes an **IR Blink Sensor** to monitor eye closure duration in real-time. If the system detects that the driver has fallen asleep, it triggers a loud buzzer to alert them and uses a **SIM800L GSM Module** to send an emergency SMS notification to designated contacts.
 
**Contributors:**  
Rishitha(ECE)  
M.Navya(CSE)  
Kavya(ECE)  
Yashaswini(AIDS)

## Tech Stack
* **C++ / Arduino:** Core logic for sensor data processing and hardware control.
* **GSM Protocol:** AT commands for SMS communication via SIM800L.
* **Hardware Interfacing:** Integration of IR sensors, Piezo buzzers, and power management modules.

## 📂 Project Structure
The repository follows a progressive development structure, tracking the project from initial experiments to the final working model:

```text
Emergency_sleep_alarm/
├── Arduino_code/                 # Development iterations
│   ├── 1_Initial_Experimented/   # Basic sensor calibration
│   ├── 3_blink_sensor_detect/    # Logic for eye-blink tracking
│   ├── 4_for_sim800l/            # GSM module testing
│   └── 7_FINAL_WORKING_CODE/     # The production-ready system code
│
├── Documentation/                # Technical reports & Manuals
│   ├── final_documentation.pdf   # Complete project report
│   └── personal_documentation.docx# Research and log notes
│
└── Working_Model/                # Physical Prototype
    ├── Photos/                   # High-res images of the hardware setup
    └── Demo_Video/               # Video demonstration of the alarm system
```
## Features
* **Real-Time Blink Detection:** Uses high-sensitivity IR sensors to track eye movements and distinguish between normal blinking and dangerous drowsiness levels.
* **Dual Alert System:** - **Local:** Immediate auditory feedback via a high-decibel piezo buzzer to wake the driver.
  - **Remote:** Automatic emergency messaging via the SIM800L module to alert family or emergency services.
* **Iterative Development:** The repository documents the evolution of the project, from basic pin definitions to complex GSM integration.
* **Robust Documentation:** Includes a detailed PDF report and personal development logs for academic or research reference.

## How to Run
Since this project is built on the Arduino platform, you will need the Arduino IDE and the necessary hardware components (Arduino Uno/Nano, IR Sensor, SIM800L).

1. **Clone or Download** this repository to your local machine.
2. Navigate to the `Arduino_code/7_FINAL_WORKING_CODE` folder.
3. Open the **`.ino`** file in your **Arduino IDE**.
4. Install any required libraries (e.g., SoftwareSerial for GSM).
5. Connect your hardware, select the correct COM Port, and click **Upload**.
6. Ensure the SIM800L is powered correctly (it requires 3.7V - 4.2V with high current) to send the SMS.

---
### Acknowledgments
**Safety First** - *Innovate. Create. Elevate.*
<br>
*Created by the DROWSY_TECH Team*
