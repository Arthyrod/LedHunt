# LedHunt
LedHunt is a hardware-integrated game developed as the Final Project for the Microprocessed Systems course.

---

🕹️ Project Overview

The game simulates a shooting gallery where the player must hit moving targets represented by LEDs. The system correlates horizontal LED positions for both the "shot" and the "target."
Key Features

* Custom Hardware: A dedicated PCB designed in KiCad and hand-fabricated.

 * Shift Register Logic: Uses two 74HC595 ICs to expand the Arduino’s GPIO capabilities, managing the LED array with minimal pin usage.

 * Real-time Feedback: * Visual: A 16x2 LCD displays the total number of shots and successful hits.

 * Auditory: A buzzer provides immediate sound cues upon hitting a target.

 * Interrupt-Driven Events: Utilizes hardware interrupts to trigger hit animations and sound effects instantly, ensuring a responsive gameplay experience.

⚙️ Technical Architecture

 * Microcontroller: Arduino Uno (ATmega328P).

 * Memory Optimization: Efficient use of the 74HC595 shift registers to handle the game's "display" logic.

 * Firmware Logic: The game loop manages target movement, while an interrupt routine handles the scoring and feedback mechanisms to maintain timing accuracy.

🛠️ Hardware Fabrication

This project involved the full electronics workflow:

 * Schematic Capture: Designed in KiCad.

 * PCB Layout: Focused on trace routing for the shift registers and LED matrix.

*Prototyping: Manual etching and soldering of the final board.
---
🚀 Known Issues & Roadmap

  * Debouncing Fix: Resolve a firmware bug where a single input pulse is occasionally registered as two separate shots.

  *Difficulty Scaling: Implement variable speeds for the target LEDs.
