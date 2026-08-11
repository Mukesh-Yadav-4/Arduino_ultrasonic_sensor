/*
  SMART PARKING GATE ASSISTANT

  > 30 cm       -> Gate CLOSED, silent
  16-30 cm      -> WARNING, slow beep
  <= 15 cm      -> Gate OPEN, fast/high beep
*/

#include <Servo.h>
#include <LiquidCrystal.h>

// ---------------- PIN SETUP ----------------

const int trigPin = 9;
const int echoPin = 10;
const int servoPin = 6;
const int buzzerPin = 8;

// LCD: RS, EN, D4, D5, D6, D7
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

Servo gateServo;


// ---------------- SETTINGS ----------------

const int warningCM = 30;
const int thresholdCM = 15;

const int gateClosedAngle = 0;
const int gateOpenAngle = 90;


// ---------------- BUZZER SETTINGS ----------------

unsigned long lastBeepTime = 0;

const unsigned long warningInterval = 700;
const unsigned long openInterval = 250;


// ---------------- STATES ----------------

enum GateState {
  CLOSED,
  WARNING,
  OPEN
};

GateState currentState = CLOSED;


// =================================================
// SETUP
// =================================================

void setup()
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);

  gateServo.attach(servoPin);
  gateServo.write(gateClosedAngle);

  lcd.begin(16, 2);

  lcd.setCursor(0, 0);
  lcd.print("Parking System");

  lcd.setCursor(0, 1);
  lcd.print("Initializing...");

  delay(1500);

  lcd.clear();

  Serial.begin(9600);
}


// =================================================
// READ DISTANCE
// =================================================

long getDistanceCM()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000);

  if (duration == 0)
  {
    return -1;
  }

  long distanceCM = duration * 0.034 / 2;

  return distanceCM;
}


// =================================================
// MAIN LOOP
// =================================================

void loop()
{
  // ------------------------------------------------
  // READ DISTANCE
  // ------------------------------------------------

  long distance = getDistanceCM();


  // ------------------------------------------------
  // DETERMINE STATE
  // ------------------------------------------------

  GateState newState;

  if (distance > 0 && distance <= thresholdCM)
  {
    newState = OPEN;
  }
  else if (distance > thresholdCM && distance <= warningCM)
  {
    newState = WARNING;
  }
  else
  {
    newState = CLOSED;
  }


  // ------------------------------------------------
  // STATE CHANGE
  // ------------------------------------------------

  if (newState != currentState)
  {
    currentState = newState;

    // Reset buzzer timer
    lastBeepTime = millis();

    // Stop old sound
    noTone(buzzerPin);


    // OPEN
    if (currentState == OPEN)
    {
      gateServo.write(gateOpenAngle);

      // Immediate first beep
      tone(buzzerPin, 1200, 150);
    }


    // WARNING
    else if (currentState == WARNING)
    {
      gateServo.write(gateClosedAngle);

      // Immediate first beep
      tone(buzzerPin, 700, 120);
    }


    // CLOSED
    else
    {
      gateServo.write(gateClosedAngle);

      // Completely silent
      noTone(buzzerPin);
    }
  }


  // ------------------------------------------------
  // LCD - DISTANCE
  // ------------------------------------------------

  lcd.setCursor(0, 0);

  if (distance > 0)
  {
    lcd.print("Dist: ");
    lcd.print(distance);
    lcd.print(" cm    ");
  }
  else
  {
    lcd.print("Dist: No Echo   ");
  }


  // ------------------------------------------------
  // LCD - STATUS
  // ------------------------------------------------

  lcd.setCursor(0, 1);

  if (currentState == OPEN)
  {
    lcd.print("Gate: OPEN      ");
  }
  else if (currentState == WARNING)
  {
    lcd.print("Car Approaching ");
  }
  else
  {
    lcd.print("Gate: CLOSED    ");
  }


// ------------------------------------------------
// REPEATING BUZZER
// ------------------------------------------------

unsigned long now = millis();

// =================================================
// WARNING
// Low gentle beep
// =================================================

if (currentState == WARNING)
{
  if (now - lastBeepTime >= warningInterval)
  {
    tone(buzzerPin, 400, 100);

    lastBeepTime = now;
  }
}


// =================================================
// OPEN
// Ascending "doo-doo"
// =================================================

else if (currentState == OPEN)
{
  if (now - lastBeepTime >= openInterval)
  {
    tone(buzzerPin, 450, 100);
    delay(120);

    tone(buzzerPin, 650, 130);

    lastBeepTime = now;
  }
}


// =================================================
// CLOSED
// Completely silent
// =================================================

else
{
  noTone(buzzerPin);
}
  // ------------------------------------------------
  // SERIAL MONITOR
  // ------------------------------------------------

  Serial.print("Distance: ");

  if (distance > 0)
  {
    Serial.print(distance);
    Serial.print(" cm");
  }
  else
  {
    Serial.print("No Echo");
  }

  Serial.print(" | State: ");

  if (currentState == OPEN)
  {
    Serial.println("OPEN");
  }
  else if (currentState == WARNING)
  {
    Serial.println("WARNING");
  }
  else
  {
    Serial.println("CLOSED");
  }


  delay(50);
}