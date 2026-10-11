// Define the pins for each segment (D0 to D6)
const int segmentA = 3;
const int segmentB = 2;
const int segmentC = 8;
const int segmentD = 7;
const int segmentE = 6;
const int segmentF = 4;
const int segmentG = 5;

// Define the pins for the push buttons
const int buttonIncrementPin = 11;
const int buttonResetPin = 10;

// Variables to track display state
int currentDigit = 0;

// Debouncing variables for Increment Button
int lastIncState = HIGH;
int incButtonState = HIGH;
unsigned long lastIncDebounceTime = 0;

// Debouncing variables for Reset Button
int lastResetState = HIGH;
int resetButtonState = HIGH;
unsigned long lastResetDebounceTime = 0;

const unsigned long debounceDelay = 50; // Debounce delay in milliseconds

// Function to update segments based on active-low logic (LOW = ON, HIGH = OFF)
void displayDigit(int digit) {
  switch (digit) {
    case 0:
      digitalWrite(segmentA, LOW);
      digitalWrite(segmentB, LOW);
      digitalWrite(segmentC, LOW);
      digitalWrite(segmentD, LOW);
      digitalWrite(segmentE, LOW);
      digitalWrite(segmentF, LOW);
      digitalWrite(segmentG, HIGH);
      break;
    case 1:
      digitalWrite(segmentA, HIGH);
      digitalWrite(segmentB, LOW);
      digitalWrite(segmentC, LOW);
      digitalWrite(segmentD, HIGH);
      digitalWrite(segmentE, HIGH);
      digitalWrite(segmentF, HIGH);
      digitalWrite(segmentG, HIGH);
      break;
    case 2:
      digitalWrite(segmentA, LOW);
      digitalWrite(segmentB, LOW);
      digitalWrite(segmentC, HIGH);
      digitalWrite(segmentD, LOW);
      digitalWrite(segmentE, LOW);
      digitalWrite(segmentF, HIGH);
      digitalWrite(segmentG, LOW);
      break;
    case 3:
      digitalWrite(segmentA, LOW);
      digitalWrite(segmentB, LOW);
      digitalWrite(segmentC, LOW);
      digitalWrite(segmentD, LOW);
      digitalWrite(segmentE, HIGH);
      digitalWrite(segmentF, HIGH);
      digitalWrite(segmentG, LOW);
      break;
    case 4:
      digitalWrite(segmentA, HIGH);
      digitalWrite(segmentB, LOW);
      digitalWrite(segmentC, LOW);
      digitalWrite(segmentD, HIGH);
      digitalWrite(segmentE, HIGH);
      digitalWrite(segmentF, LOW);
      digitalWrite(segmentG, LOW);
      break;
    case 5:
      digitalWrite(segmentA, LOW);
      digitalWrite(segmentB, HIGH);
      digitalWrite(segmentC, LOW);
      digitalWrite(segmentD, LOW);
      digitalWrite(segmentE, HIGH);
      digitalWrite(segmentF, LOW);
      digitalWrite(segmentG, LOW);
      break;
    case 6:
      digitalWrite(segmentA, LOW);
      digitalWrite(segmentB, HIGH);
      digitalWrite(segmentC, LOW);
      digitalWrite(segmentD, LOW);
      digitalWrite(segmentE, LOW);
      digitalWrite(segmentF, LOW);
      digitalWrite(segmentG, LOW);
      break;
    case 7:
      digitalWrite(segmentA, LOW);
      digitalWrite(segmentB, LOW);
      digitalWrite(segmentC, LOW);
      digitalWrite(segmentD, HIGH);
      digitalWrite(segmentE, HIGH);
      digitalWrite(segmentF, HIGH);
      digitalWrite(segmentG, HIGH);
      break;
    case 8:
      digitalWrite(segmentA, LOW);
      digitalWrite(segmentB, LOW);
      digitalWrite(segmentC, LOW);
      digitalWrite(segmentD, LOW);
      digitalWrite(segmentE, LOW);
      digitalWrite(segmentF, LOW);
      digitalWrite(segmentG, LOW);
      break;
    case 9:
      digitalWrite(segmentA, LOW);
      digitalWrite(segmentB, LOW);
      digitalWrite(segmentC, LOW);
      digitalWrite(segmentD, LOW);
      digitalWrite(segmentE, HIGH);
      digitalWrite(segmentF, LOW);
      digitalWrite(segmentG, LOW);
      break;
  }
}

void setup() {
  Serial.begin(9600);
  
  // Initialize segment pins as OUTPUTs
  pinMode(segmentA, OUTPUT);
  pinMode(segmentB, OUTPUT);
  pinMode(segmentC, OUTPUT);
  pinMode(segmentD, OUTPUT);
  pinMode(segmentE, OUTPUT);
  pinMode(segmentF, OUTPUT);
  pinMode(segmentG, OUTPUT);

  // Initialize both button pins with internal pull-up resistors
  pinMode(buttonIncrementPin, INPUT_PULLUP);
  pinMode(buttonResetPin, INPUT_PULLUP);

  // Display initial digit 0
  displayDigit(currentDigit);
  Serial.println("7-Segment Counter with Reset Ready!");
  Serial.print("Displaying Digit: ");
  Serial.println(currentDigit);
}

void loop() {
  // Read current states of both buttons
  int readingInc = digitalRead(buttonIncrementPin);
  int readingReset = digitalRead(buttonResetPin);

  // --- Increment Button Logic ---
  if (readingInc != lastIncState) {
    lastIncDebounceTime = millis();
  }
  if ((millis() - lastIncDebounceTime) > debounceDelay) {
    if (readingInc != incButtonState) {
      incButtonState = readingInc;
      // Trigger on button press (transition to LOW)
      if (incButtonState == LOW) {
        currentDigit = (currentDigit + 1) % 10; // Increment and cycle 0-9
        displayDigit(currentDigit);
        Serial.print("Displaying Digit: ");
        Serial.println(currentDigit);
      }
    }
  }
  lastIncState = readingInc;

  // --- Reset Button Logic ---
  if (readingReset != lastResetState) {
    lastResetDebounceTime = millis();
  }
  if ((millis() - lastResetDebounceTime) > debounceDelay) {
    if (readingReset != resetButtonState) {
      resetButtonState = readingReset;
      // Trigger on button press (transition to LOW)
      if (resetButtonState == LOW) {
        currentDigit = 0; // Reset count to 0
        displayDigit(currentDigit);
        Serial.println("Counter Reset to 0!");
      }
    }
  }
  lastResetState = readingReset;
}

