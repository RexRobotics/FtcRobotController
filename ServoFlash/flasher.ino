#include <SoftwareSerial.h>

#define SERVO_PIN 3  // Digital pin connected to servo signal

SoftwareSerial mySerial(SERVO_PIN, SERVO_PIN); 

void setup() {
  Serial.begin(9600);
  mySerial.begin(76800);
  pinMode(SERVO_PIN, INPUT_PULLUP);

  Serial.println("=== Dual Mode Servo Programmer ===");
  Serial.println("!!! DO NOT DISCONNECT UNTIL SERIAL INSTRUCTS !!!");
  Serial.println("Type 'C' for Continuous mode or 'P' for Positional mode:");
}

void loop() {
  if (Serial.available() > 0) {
    char choice = toupper(Serial.read());
    if (choice == 'C' || choice == 'P') {
      String modeName = (choice == 'C') ? "Continuous" : "Positional";
      Serial.print("You chose "); Serial.println(modeName);
      Serial.println("Press ENTER to confirm flashing within 5 seconds...");

      countdown(5);

      Serial.println("Flashing servo...");
      if (choice == 'C') sendContinuousModeSequence();
      else sendServoModeSequence();

      Serial.println(modeName + " mode programming complete!");
      Serial.println("It is now safe to disconnect the servo or Arduino.");
      Serial.println("Type 'C' or 'P' to program again.");
    }
  }
}

void countdown(int seconds) {
  for (int i = seconds; i > 0; i--) {
    Serial.print("Confirm in "); Serial.print(i); Serial.println("s");
    delay(1000);
  }
  Serial.println(" ");
}

void simulateProgress() {
  int steps = 20;
  for (int i = 0; i <= steps; i++) {
    int percent = (int)((i / (float)steps) * 100);
    String bar = "[";
    for (int j = 0; j < i; j++) bar += "=";
    for (int j = i; j < steps; j++) bar += " ";
    bar += "] ";
    Serial.print(bar); Serial.print(percent); Serial.println("%");
    delay(50 + random(0, 100));
  }
}

// --- Actual servo byte sequences ---

void sendContinuousModeSequence() {
  // SEND 1
  pinMode(SERVO_PIN, OUTPUT);
  mySerial.write((byte)255); mySerial.write((byte)255); mySerial.write((byte)254);
  mySerial.write((byte)2);   mySerial.write((byte)1);   mySerial.write((byte)254);
  pinMode(SERVO_PIN, INPUT_PULLUP); delay(2); flushMySerial();

  // SEND 2
  pinMode(SERVO_PIN, OUTPUT);
  mySerial.write((byte)255); mySerial.write((byte)255); mySerial.write((byte)1);
  mySerial.write((byte)4);   mySerial.write((byte)2);   mySerial.write((byte)21);
  mySerial.write((byte)1);   mySerial.write((byte)226);
  pinMode(SERVO_PIN, INPUT_PULLUP); delay(2); flushMySerial();

  // SEND 3
  pinMode(SERVO_PIN, OUTPUT);
  mySerial.write((byte)255); mySerial.write((byte)255); mySerial.write((byte)1);
  mySerial.write((byte)4);   mySerial.write((byte)3);   mySerial.write((byte)52);
  mySerial.write((byte)0);   mySerial.write((byte)195);
  pinMode(SERVO_PIN, INPUT_PULLUP); delay(3); flushMySerial();

  // SEND 4C
  pinMode(SERVO_PIN, OUTPUT);
  byte seq4C[] = {
    255,255,1,47,3,6,50,20,0,5,0,10,0,10,0,30,0,0,0,3,
    255,1,0,0,0,65,3,197,1,244,1,255,0,0,2,6,14,5,170,
    3,232,0,20,0,0,0,0,3,232,0,153
  };
  mySerial.write(seq4C, sizeof(seq4C));
  pinMode(SERVO_PIN, INPUT_PULLUP); delay(6); flushMySerial();

  // SEND 5
  pinMode(SERVO_PIN, OUTPUT);
  mySerial.write((byte)255); mySerial.write((byte)255); mySerial.write((byte)1);
  mySerial.write((byte)4);   mySerial.write((byte)3);   mySerial.write((byte)52);
  mySerial.write((byte)1);   mySerial.write((byte)194);
  pinMode(SERVO_PIN, INPUT_PULLUP); delay(2); flushMySerial();

  simulateProgress();
}

void sendServoModeSequence() {
  // SEND 4S
  pinMode(SERVO_PIN, OUTPUT);
  byte seq4S[] = {
    255,255,1,47,3,6,2,30,0,5,0,15,0,45,0,0,0,0,15,3,252,0,
    0,0,0,0,65,3,197,0,0,1,255,1,0,2,9,196,1,244,3,232,0,1,0,0,0,0,3,232,0,178
  };
  mySerial.write(seq4S, sizeof(seq4S));
  pinMode(SERVO_PIN, INPUT_PULLUP); delay(6); flushMySerial();

  // SEND 5
  pinMode(SERVO_PIN, OUTPUT);
  mySerial.write((byte)255); mySerial.write((byte)255); mySerial.write((byte)1);
  mySerial.write((byte)4);   mySerial.write((byte)3);   mySerial.write((byte)52);
  mySerial.write((byte)1);   mySerial.write((byte)194);
  pinMode(SERVO_PIN, INPUT_PULLUP); delay(2); flushMySerial();

  simulateProgress();
}

void flushMySerial() {
  while (mySerial.available()) {
    mySerial.read();
  }
}