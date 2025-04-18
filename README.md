# 🎹 Our Piano - Arduino-Based Piano Tiles Game

**📅 Project Duration**: 2nd Semester Undergraduate (Spring 2024)  
**👨‍💻 Team**: C.A.N.A [Zahid Muhammad Abdullah, Marilyn Novera, Theron Charlize, Raza Ali]  
**🛠 Platform**: Arduino Uno R3, LOL Shield, I2C Communication, 7-segment Display  
**💬 Languages**: Arduino (C++), I2C Protocol

---

## 🔧 Overview
**"Our Piano"** is an interactive real-time game inspired by the mobile game *Piano Tiles*, built entirely using Arduino boards and LED matrix hardware. Players must press buttons in sync with musical notes visualized as falling LEDs — like a physical rhythm game.

---

## 🎮 Gameplay Mechanics
- 🎵 **8 LED matrix columns** represent musical notes from **C4 to C5**.
- 🔻 **Two bright LEDs** fall down a column, indicating the note to be played.
- 🎯 Players press the button mapped to the active note.
- ✅ Correctly timed presses award points.
- 🔁 Game speed increases as the player survives longer.
- ❌ A wrong button press ends the game (missing is allowed).
- 📉 Restarted games become slightly easier if the player fails repeatedly.

---

## 🔄 Hardware Architecture
Because the LOL shield occupies all Arduino pins, we implemented **I2C communication** to coordinate three Arduinos:

- **Master Arduino**:
  - Reads button inputs
  - Produces tone output via a speaker
- **Slave 1 (LOL Shield Controller)**:
  - Animates LED note sequences
- **Slave 2 (Score Display)**:
  - Shows score on a 2-digit 7-segment display

---

## 🔊 Features
- 🎼 Realistic pitch generation for each note (based on frequency)
- 🧠 Dynamic difficulty adjustment
- 🕹 Real-time gameplay and scoring
- 🛑 Mistake detection logic using note-column mapping
- 🧩 Modular design using I2C for expandability

---

## 🎥 Demo Video

Watch **"Our Piano"** in action:

🔗 [View on Google Drive](https://drive.google.com/file/d/1aexgMx8grHPoIK_tpc_UuSy4uI0Ut3_A/view?usp=share_link)

---

## 🌱 Future Improvements
- 👥 Multi-player support (dueling piano mode)
- 🎹 Real piano key integration
- 🎼 MIDI file parsing for automatic tune generation
- 🕶 VR integration with haptic gloves *(future concept: AirKeys)*

---

Feel free to explore the full code, circuit diagrams, and notes in the respective folders!
