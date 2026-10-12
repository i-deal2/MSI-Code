#include <Servo.h>

Servo myservo;
const int potPin = A0;
const int ledPin = 3;
const int threshold = 500; // Threshold where LED turns ON
bool isRunning = true;

void setup() {
  Serial.begin(9600);
  myservo.attach(9);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Check if Python sent a command to halt execution
  if (Serial.available() > 0) {
    char incoming = Serial.read();
    if (incoming == 'q') {
      isRunning = false;
    }
  }

  if (isRunning) {
    int potValue = analogRead(potPin);
    
    // Map potentiometer (0-1023) to servo angle (0-180)
    int angle = map(potValue, 0, 1023, 0, 180);
    myservo.write(angle);

    // Turn LED on or off based on potentiometer threshold
    if (potValue > threshold) {
      digitalWrite(ledPin, HIGH);
    } else {
      digitalWrite(ledPin, LOW);
    }

    // Send potentiometer value to Python for Matplotlib visualization
    Serial.println(potValue);
    delay(50);
  }
}
