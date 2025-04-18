# Gameplay Explained

This document provides a step-by-step explanation of how the game works on the "Our Piano" project.

## Overview

The game is inspired by the popular "Piano Tiles" concept. The player interacts with the game using physical buttons, while visual feedback is provided via an LED matrix (LOL shield). The goal is to press the correct button corresponding to the note (column) at the correct time.

## Step-by-Step Gameplay

1. **Game Initialization**
   - The system powers on and initializes the LOL shield, 7-segment display, and button input system.
   - The melody data (note sequence) is loaded into memory.

2. **Start of the Game**
   - Two bright LEDs begin to fall down a column of the LOL shield.
   - Each column represents a musical note (e.g., Column 0 = C4, Column 1 = D4, ..., Column 7 = C5).

3. **LED Animation**
   - The LEDs simulate a falling motion by turning on/off row-by-row down the selected column.
   - The LED falls correspond to the current note in the melody sequence.

4. **User Input**
   - The player watches the LED fall and tries to press the correct button **when the LED is within the bottom 4 rows**.
   - Each button corresponds to one of the 8 notes/columns.

5. **Scoring System**
   - If the player presses the correct button while the LED is in the scoring zone (bottom 4 rows), they gain 1 point.
   - If the player presses a **wrong button**, the game ends immediately.
   - Missing a note (not pressing any button) is allowed.

6. **Speed Adjustment**
   - As the player scores more, the falling speed increases gradually.
   - If the player fails repeatedly, the game starts slower the next time.

7. **Score Display**
   - A 2-digit 7-segment display shows the current score in real-time.

8. **Game Over**
   - Upon pressing a wrong button, the game ends and resets.
   - The player can start again to attempt a higher score.


