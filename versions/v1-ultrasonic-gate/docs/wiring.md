# V1 Wiring Reference

This document lists the full wiring for Version 1: **Ultrasonic Proximity-Based Automatic Gate**.

## Arduino Pin Map

| Arduino Pin | Connected To | Function |
| --- | --- | --- |
| 5V | HC-SR04 VCC | Power supply |
| GND | HC-SR04 GND | Common ground |
| D9 | HC-SR04 TRIG | Trigger pulse output |
| D10 | HC-SR04 ECHO | Echo input |
| 5V | SG90 VCC | Servo power |
| GND | SG90 GND | Servo ground |
| D6 | SG90 Signal | Servo control signal |
| D8 | Buzzer positive | Audio output |
| GND | Buzzer negative | Common ground |
| D12 | LCD RS | Register select |
| D11 | LCD EN | Enable |
| D5 | LCD D4 | LCD data bit 4 |
| D4 | LCD D5 | LCD data bit 5 |
| D3 | LCD D6 | LCD data bit 6 |
| D2 | LCD D7 | LCD data bit 7 |
| GND | LCD RW | Read/write tied low |
| GND | LCD VSS | Ground |
| 5V | LCD VDD | Power supply |
| 5V through 220 ohm resistor | LCD LED A | Backlight positive |
| GND | LCD LED K | Backlight negative |
| 5V | Potentiometer outer pin | Contrast reference |
| GND | Potentiometer other outer pin | Contrast reference |
| Potentiometer middle pin | LCD VO | LCD contrast adjustment |

## Component Details

### HC-SR04 Ultrasonic Sensor

| Sensor Pin | Arduino Connection | Notes |
| --- | --- | --- |
| VCC | 5V | Power |
| GND | GND | Ground |
| TRIG | D9 | Ultrasonic trigger |
| ECHO | D10 | Echo timing input |

### SG90 Servo Motor

| Servo Wire | Arduino Connection | Notes |
| --- | --- | --- |
| Red | 5V | Power |
| Brown / Black | GND | Ground |
| Orange / Yellow | D6 | Control signal |

### Piezo Buzzer

| Buzzer Pin | Arduino Connection | Notes |
| --- | --- | --- |
| Positive | D8 | Alert output |
| Negative | GND | Ground |

### 16x2 LCD

| LCD Pin | Arduino / Circuit Connection | Notes |
| --- | --- | --- |
| RS | D12 | Register select |
| EN | D11 | Enable |
| D4 | D5 | Data line 4 |
| D5 | D4 | Data line 5 |
| D6 | D3 | Data line 6 |
| D7 | D2 | Data line 7 |
| RW | GND | Write-only mode |
| VSS | GND | Ground |
| VDD | 5V | Power |
| VO | Potentiometer middle pin | Contrast control |
| LED A | 5V through 220 ohm resistor | Backlight positive |
| LED K | GND | Backlight negative |

### 10k Potentiometer

| Potentiometer Pin | Connection | Notes |
| --- | --- | --- |
| Outer pin 1 | 5V | One end of contrast reference |
| Middle pin | LCD VO | Contrast wiper |
| Outer pin 2 | GND | Other end of contrast reference |

## Wiring Notes

- The LCD works only when `RW` is tied to ground.
- Rotate the 10k potentiometer slowly if the backlight is on but the text is missing.
- The sketch uses the LCD constructor `LiquidCrystal lcd(12, 11, 5, 4, 3, 2);`.
- Keep a common ground between the Arduino and all connected components.

## Prototype Reminder

This wiring supports a proximity-based prototype. It is suitable for Tinkercad and bench testing, but it is not a substitute for a production gate controller.