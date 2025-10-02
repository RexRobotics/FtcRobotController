#include <SoftwareSerial.h>

#define SERVO_PIN 3
SoftwareSerial mySerial(SERVO_PIN, SERVO_PIN);

bool isContinuous = false;  // Tracks current mode

void setup() {
  Serial.begin(9600);
  mySerial.begin(76800);
  pinMode(SERVO_PIN, INPUT_PULLUP);

  Serial.println("Dual Mode Servo Programmer");
  Serial.println("Type 'C' for Continuous mode or 'P' for Positional mode:");
}

void loop() {
  if (Serial.available()) {
    char cmd = Serial.read();

    // Only respond to C or P
    if (cmd == 'C' || cmd == 'c' || cmd == 'P' || cmd == 'p') {
      bool targetContinuous = (cmd == 'C' || cmd == 'c');

      Serial.print("\nYou chose ");
      Serial.print(targetContinuous ? "Continuous" : "Positional");
      Serial.println(" mode.");

      // 5-second countdown
      Serial.println("Press ENTER to confirm flashing within 5 seconds...");
      for (int i = 5; i > 0; i--) {
        Serial.print("Confirm in ");
        Serial.print(i);
        Serial.println("s");
        delay(1000);

        // Check if Enter pressed
        if (Serial.available()) {
          char enterCheck = Serial.read();
          if (enterCheck == '\n' || enterCheck == '\r') {
            flashServo(targetContinuous);
            break;
          }
        }
      }
      Serial.println("Flashing timed out. Type C or P to try again.\n");
    }
  }
}

// ---------------- Flashing function ----------------
void flashServo(bool continuous) {
  Serial.println("Flashing servo...");

  const int steps = 20; // Number of progress steps
  for (int i = 0; i <= steps; i++) {
    if (continuous) sendContinuousModeSequence();
    else sendServoModeSequence();

    // Display progress bar
    Serial.print("[");
    for (int j = 0; j < i; j++) Serial.print("=");
    for (int j = i; j < steps; j++) Serial.print(" ");
    Serial.print("] ");
    Serial.print((i * 100) / steps);
    Serial.println("%");
    delay(200); // Simulate time for flashing
  }

  isContinuous = continuous;
  Serial.println("Servo programming complete!\n");
}

// ---------------- Mode Sequences ----------------

void sendContinuousModeSequence() {
  // SEND 1
  mySerial.write((byte)255); mySerial.write((byte)255); mySerial.write((byte)254);
  mySerial.write((byte)2); mySerial.write((byte)1); mySerial.write((byte)254); delay(2);

  // SEND 2
  mySerial.write((byte)255); mySerial.write((byte)255); mySerial.write((byte)1);
  mySerial.write((byte)4); mySerial.write((byte)2); mySerial.write((byte)21);
  mySerial.write((byte)1); mySerial.write((byte)226); delay(2);

  // SEND 3
  mySerial.write((byte)255); mySerial.write((byte)255); mySerial.write((byte)1);
  mySerial.write((byte)4); mySerial.write((byte)3); mySerial.write((byte)52);
  mySerial.write((byte)0); mySerial.write((byte)195); delay(3);

  // SEND 4C
  mySerial.write((byte)255); mySerial.write((byte)255); mySerial.write((byte)1);
  mySerial.write((byte)47); mySerial.write((byte)3); mySerial.write((byte)6);
  mySerial.write((byte)50); mySerial.write((byte)20); mySerial.write((byte)0);
  mySerial.write((byte)5); mySerial.write((byte)0); mySerial.write((byte)10);
  mySerial.write((byte)0); mySerial.write((byte)10); mySerial.write((byte)0);
  mySerial.write((byte)30); mySerial.write((byte)0); mySerial.write((byte)0);
  mySerial.write((byte)0); mySerial.write((byte)3); mySerial.write((byte)255);
  mySerial.write((byte)1); mySerial.write((byte)0); mySerial.write((byte)0);
  mySerial.write((byte)0); mySerial.write((byte)65); mySerial.write((byte)3);
  mySerial.write((byte)197); mySerial.write((byte)1); mySerial.write((byte)244);
  mySerial.write((byte)1); mySerial.write((byte)255); mySerial.write((byte)0);
  mySerial.write((byte)0); mySerial.write((byte)2); mySerial.write((byte)6);
  mySerial.write((byte)14); mySerial.write((byte)5); mySerial.write((byte)170);
  mySerial.write((byte)3); mySerial.write((byte)232); mySerial.write((byte)0);
  mySerial.write((byte)20); mySerial.write((byte)0); mySerial.write((byte)0);
  mySerial.write((byte)0); mySerial.write((byte)0); mySerial.write((byte)3);
  mySerial.write((byte)232); mySerial.write((byte)0); mySerial.write((byte)153);
  delay(6);

  // SEND 5
  mySerial.write((byte)255); mySerial.write((byte)255); mySerial.write((byte)1);
  mySerial.write((byte)4); mySerial.write((byte)3); mySerial.write((byte)52);
  mySerial.write((byte)1); mySerial.write((byte)194); delay(2);
}

void sendServoModeSequence() {
  // SEND 4S
  mySerial.write((byte)255); mySerial.write((byte)255); mySerial.write((byte)1);
  mySerial.write((byte)47); mySerial.write((byte)3); mySerial.write((byte)6);
  mySerial.write((byte)2); mySerial.write((byte)30); mySerial.write((byte)0);
  mySerial.write((byte)5); mySerial.write((byte)0); mySerial.write((byte)15);
  mySerial.write((byte)0); mySerial.write((byte)45); mySerial.write((byte)0);
  mySerial.write((byte)0); mySerial.write((byte)0); mySerial.write((byte)0);
  mySerial.write((byte)15); mySerial.write((byte)3); mySerial.write((byte)252);
  mySerial.write((byte)0); mySerial.write((byte)0); mySerial.write((byte)0);
  mySerial.write((byte)0); mySerial.write((byte)65); mySerial.write((byte)3);
  mySerial.write((byte)197); mySerial.write((byte)0); mySerial.write((byte)0);
  mySerial.write((byte)1); mySerial.write((byte)255); mySerial.write((byte)1);
  mySerial.write((byte)0); mySerial.write((byte)2); mySerial.write((byte)9);
  mySerial.write((byte)196); mySerial.write((byte)1); mySerial.write((byte)244);
  mySerial.write((byte)3); mySerial.write((byte)232); mySerial.write((byte)0);
  mySerial.write((byte)1); mySerial.write((byte)0); mySerial.write((byte)0);
  mySerial.write((byte)0); mySerial.write((byte)0); mySerial.write((byte)3);
  mySerial.write((byte)232); mySerial.write((byte)0); mySerial.write((byte)178);
  delay(6);

  // SEND 5
  mySerial.write((byte)255); mySerial.write((byte)255); mySerial.write((byte)1);
  mySerial.write((byte)4); mySerial.write((byte)3); mySerial.write((byte)52);
  mySerial.write((byte)1); mySerial.write((byte)194); delay(2);
}