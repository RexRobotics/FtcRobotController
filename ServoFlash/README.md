# !!! IMPORTANT: Consult Kairav Before Use !!!

# Dual-Mode Servo Programmer (goBILDA)

This Arduino sketch allows you to **program goBILDA dual-mode servos** for FTC robots.  
It supports switching between **Continuous (CR) mode** and **Positional (P) mode** via the Serial Monitor.

---

## Features

- **Choose mode**: Type `C` for Continuous or `P` for Positional.
- **Confirmation**: 5-second countdown before flashing.
- **Progress bar**: Visual feedback while sending the programming sequences.
- **Full goBILDA byte sequences** included for reliable flashing.
- Tracks current mode (`isContinuous`) for reference.

---

## Hardware Requirements

- **Arduino Uno R3** (or compatible)
- **goBILDA dual-mode servo**
- Jumper wires connecting the servo to the Arduino:
  - **Signal pin** → `D3` (SERVO_PIN)
  - **VCC/GND** → Arduino 5V / GND
- USB cable for programming and Serial Monitor access

---

## Software Requirements

- **Arduino IDE** (1.8.x or newer)
- No additional libraries required (uses `SoftwareSerial` built-in)

---

## Usage Instructions

1. Open `DualModeServo.ino` in the Arduino IDE.
2. Connect your Arduino to the computer and the servo to the correct pins.
3. Open **Serial Monitor**:
   - Set **baud rate** to `9600`.
   - Ensure **"Newline"** or **"Both NL & CR"** is selected for line ending.
4. Type `C` for **Continuous** mode or `P` for **Positional** mode.
5. The console will show: