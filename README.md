# 🎹 Our Piano - Arduino-Based Piano Tiles Game

**Project Duration**: 2nd Semester Undergraduate (Spring 2024)  
**Team**: [Your name], [Teammates if any]  
**Platform**: Arduino Uno R3, LOL Shield, I2C Communication, 7-segment Display  
**Languages**: Arduino (C++), I2C Protocol

## 🔧 Overview
"Our Piano" is an interactive real-time game inspired by the mobile game *Piano Tiles*, built entirely using Arduinos and LED matrix hardware. Players press buttons in sync with musical notes visualized as falling LEDs.

## 🧠 Gameplay
- **8 columns** of an LED matrix represent 8 musical notes (C4 to C5).
- 2 bright LEDs "fall" down a column to indicate which note should be played.
- Players press buttons corresponding to each note.
- Points are awarded for correctly timed presses.
- Game speed increases the longer the player survives; if a mistake is made, the game restarts and gets slightly easier next time.

## 🔄 Hardware Architecture
Due to the LOL shield occupying all Arduino pins:
- Used **I2C** communication to manage three Arduinos:
  - Master: Handles buttons and audio output
  - Slave 1: Drives the LOL Shield and LED animation
  - Slave 2: Displays score on 2-digit 7-segment display

## 🔊 Features
- Dynamic difficulty scaling
- Real-time score display
- Error detection for mistimed button presses
- Accurate pitch generation for each note

## 📷 Media
Check the `media/` folder for images and demo videos of the system in action.

## 🔗 Future Improvements
- Multi-player support
- Integration with actual piano keys (instead of buttons)
- MIDI file parsing to auto-generate tunes
- VR Integration (e.g., using haptic gloves - for future projects like AirKeys)

