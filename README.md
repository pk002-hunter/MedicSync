# MedicSync
MedicSync is an offline-first tactical triage system that uses an IoT vest and a Progressive Web App to instantly detect soldier injuries and automate medical data transfer. It replaces manual paper reporting to speed up field treatment and hospital preparation during the critical "Golden Hour."

# 🦅 MedicSync: Autonomous Tactical Triage & Health System

![Version](https://img.shields.io/badge/version-1.0.0-blue.svg)
![Status](https://img.shields.io/badge/status-Prototype-orange.svg)
![Hardware](https://img.shields.io/badge/hardware-ESP8266-success.svg)
![License](https://img.shields.io/badge/license-MIT-green.svg)

## 📝 Overview
In combat and mass-casualty scenarios, the "Golden Hour" dictates survival. Currently, triage relies on manual checks and physical paper tags (like the DD Form 1380), leading to chaotic handovers and lost time. 

**MedicSync** is an End-to-End Military Medical Ecosystem designed to automate the "Chain of Survival." It replaces paper with a resilient, offline-first digital pipeline. From the moment a soldier goes down to the moment they arrive at the hospital, MedicSync ensures zero data is lost and treatment is instantaneous.

## 🎯 Key Features
* **Silent Scream (Auto-Detection):** Hardware sensors instantly detect critical drops in vitals or high-impact events and silently alert the squad via Wi-Fi telemetry.
* **Buddy Awareness (Haptic SOS):** Integrated vibration motors provide silent, Morse-code haptic feedback to nearby squadmates, enabling immediate "Care Under Fire."
* **Digital Dog Tags:** Secure identification using Unique Service Numbers (e.g., PARA-01-05), keeping high-value target identities masked from radio interception.
* **Offline-First PWA:** The Medic's dashboard works 100% offline using Service Workers and IndexedDB. It automatically syncs to Command HQ via a custom Background Sync Engine when connection returns.
* **Interactive Body Map:** A UI masterpiece that allows medics to log injuries and treatments (e.g., Tourniquets, Morphine) with single taps on a graphical body map, saving crucial minutes.

## 🏗️ System Architecture
MedicSync operates across three distinct layers:

1. **The IoT Layer (Soldier):** A ruggedized wearable vest insert that continuously streams telemetry and listens for haptic alerts.
2. **The Edge Layer (Medic):** A Local LAN-capable web application that triages casualties (Red/Yellow/Green) and logs field treatments.
3. **The Cloud Layer (Command HQ):** A central database that maps battlefield casualties and alerts standby hospitals for inbound medical evacuations.

## 💻 Tech Stack
**Frontend (Medic Dashboard)**
* HTML5 / CSS3 / JavaScript (Vanilla / React.js)
* Progressive Web App (PWA) Standards (Service Workers, IndexedDB)

**Backend (Command HQ)**
* Node.js & Express.js
* REST API Architecture
* MongoDB (NoSQL Database for Casualty Reports)

**Hardware (Tactical Vest)**
* Microcontroller: ESP8266 (NodeMCU)
* Vitals: AD8232 (ECG) / MAX30102 (Pulse Oximeter)
* Trauma Detection: MPU6050 (Gyroscope/Accelerometer)
* Feedback: 3V Vibration Motor Module

## 🛠️ Hardware Setup & Wiring (ESP8266)
| Component | ESP8266 Pin | Function |
| :--- | :--- | :--- |
| **MPU6050 (SCL)** | D1 (GPIO 5) | I2C Clock for Fall Detection |
| **MPU6050 (SDA)** | D2 (GPIO 4) | I2C Data for Fall Detection |
| **AD8232 (Output)** | A0 | Analog Heart Rate Waveform |
| **Vibration Motor** | D5 (GPIO 14) | Haptic SOS Feedback |

## 🚀 Getting Started (Development)

### 1. Run the HQ Server
```bash
# Clone the repository
git clone [https://github.com/yourusername/MedicSync.git](https://github.com/yourusername/MedicSync.git)

# Navigate to the backend directory
cd MedicSync/backend

# Install dependencies
npm install express cors axios mongoose

# Start the Node server
node server.js
