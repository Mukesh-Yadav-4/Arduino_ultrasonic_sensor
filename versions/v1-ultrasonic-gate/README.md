# Ultrasonic Proximity-Based Automatic Gate

Version 1 of the **Secure Smart Parking & Access Control System** is a small embedded prototype that uses an HC-SR04 ultrasonic sensor to detect proximity, then drives an LCD, buzzer, and servo-based gate response.

This is a prototype for educational and portfolio use. The sensor measures distance and proximity only; it does not identify a vehicle or authenticate a user.

## 1. Project Title

Ultrasonic Proximity-Based Automatic Gate

## 2. Overview

This version demonstrates a simple smart-parking style access gate. When an object approaches, the system classifies the measured distance into one of three states and updates the outputs accordingly.

## 3. Problem Statement

Manual gate operation is slow and inconsistent. A basic embedded system can improve responsiveness by detecting an approaching object early, showing the current status clearly, and providing audio feedback while keeping the gate closed until the object is very close.

## 4. Objective

- Measure distance using the HC-SR04 sensor
- Show the measured distance and system state on a 16x2 LCD
- Trigger warning sounds as an object approaches
- Open the gate representation with a servo at close range
- Keep the system easy to understand and suitable for beginners

## 5. How the System Works

1. The HC-SR04 sends an ultrasonic pulse.
2. The Arduino measures the echo time and converts it to distance.
3. The distance is classified into `CLOSED`, `WARNING`, or `OPEN`.
4. The LCD is refreshed continuously with the latest distance and state.
5. The buzzer produces different alert patterns depending on the state.
6. The servo moves only when the state changes.

## 6. System Architecture

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
┌──────────┬───────────┬───────────┐
↓          ↓           ↓
LCD       Buzzer       Servo
Status    Alert        Gate
```

## 7. Hardware / Components

- Arduino Uno
- HC-SR04 ultrasonic sensor
- SG90 micro servo motor
- 16x2 LCD
- Piezo buzzer
- 10k potentiometer for LCD contrast
- 220 ohm resistor for the LCD backlight
- Breadboard
- Jumper wires

## 8. Pin Connections

See [docs/wiring.md](docs/wiring.md) for the full connection table.

## 9. Operating States

### CLOSED

- Distance greater than 30 cm
- Servo at approximately 0 degrees
- Buzzer silent
- LCD shows the measured distance and `Gate: CLOSED`

### WARNING

- Distance between 16 cm and 30 cm
- Gate remains closed
- Servo stays at approximately 0 degrees
- LCD shows `Car Approaching`
- Buzzer gives a gentle repeating warning beep

### OPEN

- Distance 15 cm or less
- Servo moves to approximately 90 degrees
- LCD shows `Gate: OPEN`
- Buzzer gives a short ascending repeating alert

## 10. Control Logic

The sketch uses a simple state machine:

- `CLOSED` when distance is greater than 30 cm or when the echo is missing
- `WARNING` when distance is between 16 cm and 30 cm
- `OPEN` when distance is 15 cm or less

The LCD updates every loop so the display always reflects the latest reading. The servo is commanded only when the state changes. The buzzer pattern depends on the current state.

## 11. Software Used

- Arduino IDE or Tinkercad Circuits
- Arduino `Servo` library
- Arduino `LiquidCrystal` library

## 12. Current Limitations

- This is a prototype, not a final access-control product
- It uses proximity sensing only
- It does not identify vehicles
- It does not authenticate users
- It does not include network, cloud, or database features
- Sensor readings can vary with surface angle, placement, and environment

## 13. Testing Procedure

1. Assemble the circuit according to the wiring table.
2. Upload `src/smart_parking_v1.ino` to the Arduino Uno.
3. Open the Serial Monitor at 9600 baud.
4. Observe the LCD while moving an object toward and away from the sensor.
5. Verify the state transitions:
   - `CLOSED` at far distance
   - `WARNING` in the middle range
   - `OPEN` at close range
6. Confirm the servo and buzzer match the active state.

## 14. Expected Behavior

- Distance greater than 30 cm: gate closed, buzzer silent
- Distance between 16 cm and 30 cm: warning beep, gate closed
- Distance 15 cm or less: gate open, repeating two-tone alert
- When the object moves away, the system returns from `OPEN` to `WARNING` to `CLOSED`

## 15. Future Improvements

- RFID-based authentication
- Parking-slot occupancy tracking
- IoT monitoring and logging
- Optional computer-vision-based identification

## 16. Safety / Real-World Considerations

- Keep the servo load within its rated range
- Use a proper power supply for real hardware builds
- Separate prototype logic from safety-critical gate control in production systems
- Validate mechanical gate motion before attaching a real barrier
- Treat ultrasonic distance as a proximity signal, not an identity signal

## Source

The V1 Arduino sketch is in [src/smart_parking_v1.ino](src/smart_parking_v1.ino).