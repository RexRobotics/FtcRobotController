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
- **Do not disconnect the servo or Arduino** until the Serial Monitor indicates it is safe to do so.

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
6. Press **Enter** to confirm within the countdown.
7. The **progress bar** will display while flashing.
8. Wait for the Serial Monitor to indicate **"Programming complete! It is now safe to disconnect."**
9. Repeat the process for the other mode if needed.

---

## Notes

- Flashing takes **~2–3 seconds** per mode.
- Do **not** disconnect the servo or Arduino until told by the Serial Monitor.
- This sketch is intended for **FTC team use**; always follow team safety and robot rules.

---

## Support

If you encounter issues, check:

- Proper servo connection (signal, VCC, GND)
- Correct Serial Monitor baud rate (9600)
- That your servo is a **dual-mode goBILDA servo**
- Consult **Kairav** for further guidance

