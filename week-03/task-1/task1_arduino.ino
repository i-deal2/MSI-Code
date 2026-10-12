const int potPin = A0;  // Potentiometer connected to analog pin A0
const int ledPin = 7; 
const int threshold = 500; // Change this value to adjust sensitivity

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int potValue = analogRead(potPin);
  
  // Check if potentiometer exceeds the threshold
  if (potValue > threshold) {
    digitalWrite(ledPin, HIGH); // Turn LED ON
  } else {
    digitalWrite(ledPin, LOW);  // Turn LED OFF
  }

  Serial.println(potValue);
  delay(100); // Small delay for stability
}
