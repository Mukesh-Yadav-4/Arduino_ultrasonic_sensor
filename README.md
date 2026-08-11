# Secure Smart Parking & Access Control System

An evolving embedded systems project for an Electronics and Communication Engineering portfolio.

Version 1 is a working prototype named **Ultrasonic Proximity-Based Automatic Gate**. It uses an HC-SR04 ultrasonic sensor to measure proximity, an LCD for live status, a buzzer for alerts, and a servo motor to represent an automatic gate.

## Project Overview

This repository documents the project as a versioned build history so future upgrades can be added without restructuring the whole codebase.

Version 1 is a proximity-based prototype only. It does **not** identify vehicles, authenticate users, or provide IoT connectivity. The ultrasonic sensor detects distance, not vehicle identity.

## Current Status

| Version | Focus | Status |
| --- | --- | --- |
| V1 | Ultrasonic proximity detection + automatic gate | Working |
| V2 | RFID authentication | Planned |
| V3 | Parking-space management | Planned |
| V4 | IoT monitoring | Planned |
| V5 | Optional computer vision | Planned |

## Project Evolution

V1 -> Proximity detection + automatic gate

V2 -> RFID authentication

V3 -> Parking-space management

V4 -> IoT monitoring

V5 -> Optional computer vision

## Current Architecture

```text
HC-SR04
	↓
Distance measurement
	↓
Arduino Uno
	↓
Distance classification
	↓
CLOSED / WARNING / OPEN
	↓
┌──────────┬───────────┬
↓          ↓           ↓
LCD       Buzzer       Servo
Status    Alert        Gate
```

## Technologies

- Arduino Uno
- Arduino C/C++
- HC-SR04 ultrasonic sensing
- SG90 micro servo control
- 16x2 parallel LCD interface
- Piezo buzzer output
- Tinkercad for initial prototype validation

## Hardware

- Arduino Uno
- HC-SR04 ultrasonic sensor
- SG90 micro servo motor
- 16x2 LCD
- Piezo buzzer
- 10k potentiometer for LCD contrast
- 220 ohm resistor for LCD backlight
- Breadboard and jumper wires

## Repository Structure

```text
/
├── README.md
├── LICENSE
├── .gitignore
├── SmartParkingAssistant.ino
├── versions/
│   └── v1-ultrasonic-gate/
│       ├── README.md
│       ├── src/
│       │   └── smart_parking_v1.ino
│       ├── docs/
│       │   ├── wiring.md
│       │   └── system-architecture.md
│       └── media/
└── docs/
    └── roadmap.md
```

The original root-level sketch is retained as a legacy reference. The canonical V1 source for this repository is in `versions/v1-ultrasonic-gate/src/smart_parking_v1.ino`.

## Future Roadmap

Planned upgrades are documented in [docs/roadmap.md](docs/roadmap.md). The repository is intentionally structured so each future version can live in its own folder without disturbing earlier builds.

## About the Prototype

This is an embedded prototype intended for student demonstration, lab validation, and portfolio presentation. It is suitable for explaining sensing, classification, output control, and state-based embedded design.

It is not a production parking barrier system and should not be treated as a security-grade access controller.