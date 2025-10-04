#include <SoftwareSerial.h>
#include <Servo.h>

#define SERVO_PIN 3  // Change this if you use a different digital pin

// Create a SoftwareSerial object on pin 3 (shared TX/RX)
SoftwareSerial mySerial(SERVO_PIN, SERVO_PIN); 

// Create a Servo object (for positional control)
Servo myServo;

// Setup: Start serial, force continuous mode, run continuous cycle,
// then switch to normal (positional) mode and run a positional cycle.
void setup() {
  Serial.begin(115200);
  mySerial.begin(76800);  // Baud rate expected by the servo
  pinMode(SERVO_PIN, INPUT_PULLUP);
  
  myServo.detach();  // Ensure the Servo library is not attached initially
  
  Serial.println("=== SWITCHING TO CONTINUOUS MODE ===");
  sendContinuousModeSequence();
  delay(2000);
  
  Serial.println("=== RUNNING CONTINUOUS CYCLE ===");
  runContinuousCycle();  

  Serial.println("=== SWITCHING TO NORMAL (POSITIONAL) MODE ===");
  sendServoModeSequence();
  delay(2000);

  myServo.attach(SERVO_PIN);
  
  Serial.println("=== RUNNING POSITIONAL CYCLE ===");
  myServo.write(60);
  delay(2000);

  myServo.write(180);
  delay(2000);

  myServo.write(90);
  delay(2000);
  
  // Detach servo control so we can switch back via SoftwareSerial.
  myServo.detach();
}

void loop() {
  // --- Continuous Mode Phase ---
  Serial.println("=== SWITCHING TO CONTINUOUS MODE ===");
  sendContinuousModeSequence();
  delay(2000);
  
  Serial.println("=== RUNNING CONTINUOUS CYCLE ===");
  runContinuousCycle();  // 5 seconds forward, 5 seconds stop, 5 seconds reverse
  
  // --- Switch to Normal (Positional) Mode ---
  Serial.println("=== SWITCHING TO NORMAL (POSITIONAL) MODE ===");
  sendServoModeSequence();
  delay(2000);
  
  myServo.attach(SERVO_PIN);
  
  Serial.println("=== RUNNING POSITIONAL CYCLE ===");
  myServo.write(60);    // Move to a chosen position
  delay(2000);
  myServo.write(180);   // Move to the opposite extreme (simulate "180° from there")
  delay(2000);
  myServo.write(90);    // Move 90° back
  delay(2000);
  
  myServo.detach();
  
  // Repeat the entire cycle.
}

void runContinuousCycle() {
  runForDuration(2000, 5000); // 2000 µs pulse: full forward
  runForDuration(1500, 5000); // 1500 µs pulse: stop (neutral)
  runForDuration(1000, 5000); // 1000 µs pulse: full reverse
}

// Send pulses repeatedly for a given duration.
void runForDuration(int pulseWidth, unsigned long durationMs) {
  unsigned long startTime = millis();
  while (millis() - startTime < durationMs) {
    sendServoPulse(pulseWidth);
    delay(20); // Typical servo refresh period
  }
}

// Generates one servo PWM pulse on SERVO_PIN.
// In continuous mode, pulse width determines speed/direction:
//   ~1000 µs = full reverse, ~1500 µs = stop, ~2000 µs = full forward.
// This function temporarily sets SERVO_PIN as OUTPUT to drive the pulse,
// then returns it to INPUT_PULLUP for SoftwareSerial use.
void sendServoPulse(int pulseWidthMicroseconds) {
  pinMode(SERVO_PIN, OUTPUT);
  digitalWrite(SERVO_PIN, LOW);
  delay(10);
  digitalWrite(SERVO_PIN, HIGH);
  delayMicroseconds(pulseWidthMicroseconds);
  digitalWrite(SERVO_PIN, LOW);
  delay(10);
  digitalWrite(SERVO_PIN, HIGH);
  pinMode(SERVO_PIN, INPUT_PULLUP);
  flushMySerial();
}

// Sends a series of commands (SEND 1, SEND 2, SEND 3, SEND 4C, SEND 5)
// that force the servo into continuous rotation mode.
void sendContinuousModeSequence() {
  Serial.println("Continuous Mode: SEND 1");
  pinMode(SERVO_PIN, OUTPUT);
  mySerial.write((byte)255);
  mySerial.write((byte)255);
  mySerial.write((byte)254);
  mySerial.write((byte)2);
  mySerial.write((byte)1);
  mySerial.write((byte)254);
  pinMode(SERVO_PIN, INPUT_PULLUP);
  delay(2);
  flushMySerial();
  
  Serial.println("Continuous Mode: SEND 2");
  pinMode(SERVO_PIN, OUTPUT);
  mySerial.write((byte)255);
  mySerial.write((byte)255);
  mySerial.write((byte)1);
  mySerial.write((byte)4);
  mySerial.write((byte)2);
  mySerial.write((byte)21);
  mySerial.write((byte)1);
  mySerial.write((byte)226);
  pinMode(SERVO_PIN, INPUT_PULLUP);
  delay(2);
  flushMySerial();
  
  Serial.println("Continuous Mode: SEND 3");
  pinMode(SERVO_PIN, OUTPUT);
  mySerial.write((byte)255);
  mySerial.write((byte)255);
  mySerial.write((byte)1);
  mySerial.write((byte)4);
  mySerial.write((byte)3);
  mySerial.write((byte)52);
  mySerial.write((byte)0);
  mySerial.write((byte)195);
  pinMode(SERVO_PIN, INPUT_PULLUP);
  delay(3);
  flushMySerial();
  
  Serial.println("Continuous Mode: SEND 4C");
  pinMode(SERVO_PIN, OUTPUT);
  mySerial.write((byte)255);
  mySerial.write((byte)255);
  mySerial.write((byte)1);
  mySerial.write((byte)47);
  mySerial.write((byte)3);
  mySerial.write((byte)6);
  mySerial.write((byte)50);
  mySerial.write((byte)20);
  mySerial.write((byte)0);
  mySerial.write((byte)5);
  mySerial.write((byte)0);
  mySerial.write((byte)10);
  mySerial.write((byte)0);
  mySerial.write((byte)10);
  mySerial.write((byte)0);
  mySerial.write((byte)30);
  mySerial.write((byte)0);
  mySerial.write((byte)0);
  mySerial.write((byte)0);
  mySerial.write((byte)3);
  mySerial.write((byte)255);
  mySerial.write((byte)1);
  mySerial.write((byte)0);
  mySerial.write((byte)0);
  mySerial.write((byte)0);
  mySerial.write((byte)65);
  mySerial.write((byte)3);
  mySerial.write((byte)197);
  mySerial.write((byte)1);
  mySerial.write((byte)244);
  mySerial.write((byte)1);
  mySerial.write((byte)255);
  mySerial.write((byte)0);
  mySerial.write((byte)0);
  mySerial.write((byte)2);
  mySerial.write((byte)6);
  mySerial.write((byte)14);
  mySerial.write((byte)5);
  mySerial.write((byte)170);
  mySerial.write((byte)3);
  mySerial.write((byte)232);
  mySerial.write((byte)0);
  mySerial.write((byte)20);
  mySerial.write((byte)0);
  mySerial.write((byte)0);
  mySerial.write((byte)0);
  mySerial.write((byte)0);
  mySerial.write((byte)3);
  mySerial.write((byte)232);
  mySerial.write((byte)0);
  mySerial.write((byte)153);
  pinMode(SERVO_PIN, INPUT_PULLUP);
  delay(6);
  flushMySerial();
  
  Serial.println("Continuous Mode: SEND 5");
  pinMode(SERVO_PIN, OUTPUT);
  mySerial.write((byte)255);
  mySerial.write((byte)255);
  mySerial.write((byte)1);
  mySerial.write((byte)4);
  mySerial.write((byte)3);
  mySerial.write((byte)52);
  mySerial.write((byte)1);
  mySerial.write((byte)194);
  pinMode(SERVO_PIN, INPUT_PULLUP);
  delay(2);
  flushMySerial();
  
  Serial.println("Continuous mode sequence complete.");
}

// Sends the command sequence for normal (positional) mode using the "SEND 4S" branch
// followed by SEND 5.
void sendServoModeSequence() {
  Serial.println("Normal Mode: SEND 4S");
  pinMode(SERVO_PIN, OUTPUT);
  mySerial.write((byte)255);
  mySerial.write((byte)255);
  mySerial.write((byte)1);
  mySerial.write((byte)47);
  mySerial.write((byte)3);
  mySerial.write((byte)6);
  mySerial.write((byte)2);
  mySerial.write((byte)30);
  mySerial.write((byte)0);
  mySerial.write((byte)5);
  mySerial.write((byte)0);
  mySerial.write((byte)15);
  mySerial.write((byte)0);
  mySerial.write((byte)45);
  mySerial.write((byte)0);
  mySerial.write((byte)0);
  mySerial.write((byte)0);
  mySerial.write((byte)0);
  mySerial.write((byte)15);
  mySerial.write((byte)3);
  mySerial.write((byte)252);
  mySerial.write((byte)0);
  mySerial.write((byte)0);
  mySerial.write((byte)0);
  mySerial.write((byte)0);
  mySerial.write((byte)65);
  mySerial.write((byte)3);
  mySerial.write((byte)197);
  mySerial.write((byte)0);
  mySerial.write((byte)0);
  mySerial.write((byte)1);
  mySerial.write((byte)255);
  mySerial.write((byte)1);
  mySerial.write((byte)0);
  mySerial.write((byte)2);
  mySerial.write((byte)9);
  mySerial.write((byte)196);
  mySerial.write((byte)1);
  mySerial.write((byte)244);
  mySerial.write((byte)3);
  mySerial.write((byte)232);
  mySerial.write((byte)0);
  mySerial.write((byte)1);
  mySerial.write((byte)0);
  mySerial.write((byte)0);
  mySerial.write((byte)0);
  mySerial.write((byte)0);
  mySerial.write((byte)3);
  mySerial.write((byte)232);
  mySerial.write((byte)0);
  mySerial.write((byte)178);
  pinMode(SERVO_PIN, INPUT_PULLUP);
  delay(6);
  flushMySerial();
  
  Serial.println("Normal Mode: SEND 5");
  pinMode(SERVO_PIN, OUTPUT);
  mySerial.write((byte)255);
  mySerial.write((byte)255);
  mySerial.write((byte)1);
  mySerial.write((byte)4);
  mySerial.write((byte)3);
  mySerial.write((byte)52);
  mySerial.write((byte)1);
  mySerial.write((byte)194);
  pinMode(SERVO_PIN, INPUT_PULLUP);
  delay(2);
  flushMySerial();
  
  Serial.println("Normal mode sequence complete.");
}

// Reads and discards any bytes waiting in the SoftwareSerial buffer.
void flushMySerial() {
  while (mySerial.available()) {
    mySerial.read();
  }
}