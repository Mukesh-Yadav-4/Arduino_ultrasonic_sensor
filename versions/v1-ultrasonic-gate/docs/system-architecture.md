# V1 System Architecture

Version 1 uses a simple sensing-and-response pipeline.

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

## Block Description

### HC-SR04

Generates the ultrasonic pulse and measures the echo return time.

### Distance Measurement

Converts echo time into a distance estimate in centimeters.

### Arduino Uno

Reads the sensor value, classifies the state, updates the LCD, and controls the buzzer and servo.

### Distance Classification

Maps the measured distance into one of three states:

- `CLOSED`
- `WARNING`
- `OPEN`

### Outputs

- LCD: displays distance and current state
- Buzzer: provides audible warning patterns
- Servo: represents the automatic gate position

## Design Notes

- The LCD is updated continuously so the user always sees the latest status.
- The servo is only moved when the state changes.
- Missing echo readings are handled safely by falling back to the closed state.
- The design is intentionally simple so it is easy to explain in an ECE presentation.