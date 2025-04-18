/*
  ============================================================================================
  Project: LED Piano Tiles Game (Slave 1)
  Author: Zahid Muhammad Abdullah
  DATE: July 2024

  Description:
    This is the SLAVE Arduino code responsible for handling the LED display in a piano-tile 
    inspired game using the LOL Shield (Charlieplexing). It receives note inputs via I2C 
    communication from the MASTER Arduino (which detects key presses from switches), and 
    visually displays falling musical notes using LEDs. The player is expected to hit keys 
    in sync with the notes as they reach the bottom of the display.

    Key Features:
    - Uses LOL Shield (Charlieplexing) for LED visualization of falling notes.
    - Receives note input from MASTER Arduino via I2C.
    - Compares received keys with expected note sequence.
    - Increments score for correct key presses at the correct timing.
    - Sends current score back to MASTER Arduino on request.

    Components:
    - LED Display using LOL Shield (Charlieplexing)
    - I2C Communication (Wire library)
    - Timer interrupt (TimerOne library)

    Communication:
    - This SLAVE has I2C address 9.
    - It receives characters representing keys (e.g., 'C', 'D', etc.) from MASTER.
    - Sends integer score back to MASTER when requested.

    Notes:
    - `expectedValues[]` stores the musical note sequence to be displayed.
    - Each iteration of the main loop handles animation and LED update of one frame.
    - Game logic compares player input with falling notes based on their position.
    - Delay values control the speed of falling tiles.

  Libraries Used:
    - <Charliplexing.h>: Controls the LED matrix (LOL Shield).
    - <Wire.h>: Handles I2C communication.
    - <TimerOne.h>: Sets up a timer interrupt for checking key inputs.
    - <Font.h> / <Figure.h>: Optional graphics/fonts for LED display (if used).

  ============================================================================================
*/

#include <Charliplexing.h> // Library for controlling the LED matrix using charlieplexing
#include <Figure.h>        // Used by Charliplexing library (for drawing figures)
#include <Font.h>          // Used by Charliplexing library (for fonts/text)
#include <Wire.h>          // I2C communication
#include <TimerOne.h>      // Timer interrupt library for regularly checking keypresses

// Column pin mappings for note representation on the LED matrix
int C = 8, D = 7, E = 6, F = 5, G = 4, A = 3, B = 2, C_ = 1;

// Shared global variables
volatile char receivedKey = '\0'; // Last received key from the MASTER Arduino via I2C
int DEL = 250;                    // Delay between LED refreshes
int Points = 0;                   // Score counter
char Key_Value;                   // Stores the actual valid key received
char expectedValues[] = {
  'C', 'C', 'G', 'G', 'A', 'A', 'G', 'F', 'F', 'E', 'E', 'D', 'D', 'C',
  'G', 'G', 'F', 'F', 'E', 'E', 'D', 'G', 'G', 'F', 'F', 'E', 'E', 'D',
  'C', 'C', 'G', 'G', 'A', 'A', 'G', 'F', 'F', 'E', 'E', 'D', 'D', 'C'
}; // Predefined correct sequence of notes in the game

String result;                    // For storing/displaying result if needed
unsigned long current_time = millis(); // Timestamp tracking
int Between_DEL;                 // Delay used to debounce/space keypress checks

// ===============================
// SETUP FUNCTION
// ===============================
void setup() {
  LedSign::Init();            // Initialize the Charlieplexed LED display
  Wire.begin(9);              // Start I2C communication with address 9 (Slave)
  Wire.onReceive(receiveEvent); // Callback when data is received from MASTER
  Timer1.initialize(100000);     // Set up Timer1 to trigger every 100ms
  Timer1.attachInterrupt(receiveEvent); // Attach interrupt to handle keypress update
  Serial.begin(9600);            // Optional: for debugging (can be removed)
  Wire.onRequest(sendPoint);     // Callback when MASTER requests score
}

// ===============================
// HELPER: Set a pixel or row on the LED matrix
// ===============================
void setLED(int pos, int row, int state) {
  if (pos >= 0 && pos < 14) { // Ensure position is within the LED matrix width
    LedSign::Set(pos, row, state);       // Turn on/off primary LED
    LedSign::Set(pos + 1, row, state);   // Optionally extend to the next LED for better visibility
  }
}

// ===============================
// I2C RECEIVE HANDLER: Triggered when MASTER sends a key
// ===============================
void receiveEvent(int bytes) {
  while (Wire.available()) {
    receivedKey = Wire.read(); // Read character from MASTER
    if (receivedKey != '\0') {
      Key_Value = receivedKey; // Update valid key value
    }
  }
}

// ===============================
// I2C REQUEST HANDLER: Sends current score back to MASTER
// ===============================
void sendPoint() {
  Wire.write(Points); // Return current point count
}

// ===============================
// MAIN GAME LOOP
// ===============================
void loop() {
  for (int i = 0; i < 200; i++) {
    // The next section defines which note is falling at which row at time 'i'
    // Each note has its own range of movement controlled by its position variable
    // The notes are revealed and disappear from the matrix based on the loop index
    
    int FirstPos = (i < 13) ? i : -1;       // Each note column lights up in sequence
    int SecondPos = (i >= 4 && i < 17) ? (i - 4) : -1;
    int ThirdPos = (i >= 8 && i < 21) ? (i - 8) : -1;
    int FourthPos = (i >= 12 && i < 25) ? (i - 12) : -1;
    int FifthPos = (i >= 16 && i < 29) ? (i - 16) : -1;
    int SixthPos = (i >= 20 && i < 33) ? (i - 20) : -1;
    int SeventhPos = (i >= 24 && i < 37) ? (i - 24) : -1;
    int EigthPos = (i >= 28 && i < 41) ? (i - 28) : -1;
    int NinthPos = (i >= 32 && i < 45) ? (i - 32) : -1;
    int TenthPos = (i >= 36 && i < 49) ? (i - 36) : -1;
    int EleventhPos = (i >= 40 && i < 53) ? (i - 40) : -1;
    int TwelfthPos = (i >= 44 && i < 57) ? (i - 44) : -1;
    int ThirteenthPos = (i >= 48 && i < 61) ? (i - 48) : -1;
    int FourteenthPos = (i >= 52 && i < 65) ? (i - 52) : -1;
    int FifteenthPos = (i >= 56 && i < 69) ? (i - 56) : -1;
    int SixteenthPos = (i >= 60 && i < 73) ? (i - 60) : -1;
    int SeventeenthPos = (i >= 64 && i < 77) ? (i - 64) : -1;
    int EighteenthPos = (i >= 68 && i < 81) ? (i - 68) : -1;
    int NineteenthPos = (i >= 72 && i < 85) ? (i - 72) : -1;
    int TwentiethPos = (i >= 76 && i < 89) ? (i - 76) : -1;
    int TwentyfirstPos = (i >= 80 && i < 93) ? (i - 80) : -1;
    int TwentysecondPos = (i >= 84 && i < 97) ? (i - 84) : -1;
    int TwentythirdPos = (i >= 88 && i < 101) ? (i - 88) : -1;
    int TwentyfourthPos = (i >= 92 && i < 105) ? (i - 92) : -1;
    int TwentyfifthPos = (i >= 96 && i < 109) ? (i - 96) : -1;
    int TwentysixthPos = (i >= 100 && i < 113) ? (i - 100) : -1;
    int TwentyseventhPos = (i >= 104 && i < 117) ? (i - 104) : -1;
    int TwentyeighthPos = (i >= 108 && i < 121) ? (i - 108) : -1;
    int TwentyninthPos = (i >= 112 && i < 125) ? (i - 112) : -1;
    int ThirtiethPos = (i >= 116 && i < 129) ? (i - 116) : -1;
    int ThirtyfirstPos = (i >= 120 && i < 133) ? (i - 120) : -1;
    int ThirtysecondPos = (i >= 124 && i < 137) ? (i - 124) : -1;
    int ThirtythirdPos = (i >= 128 && i < 141) ? (i - 128) : -1;
    int ThirtyfourthPos = (i >= 132 && i < 145) ? (i - 132) : -1;
    int ThirtyfifthPos = (i >= 136 && i < 149) ? (i - 136) : -1;
    int ThirtysixthPos = (i >= 140 && i < 153) ? (i - 140) : -1;
    int ThirtyseventhPos = (i >= 144 && i < 157) ? (i - 144) : -1;
    int ThirtyeighthPos = (i >= 148 && i < 161) ? (i - 148) : -1;
    int ThirtyninthPos = (i >= 152 && i < 165) ? (i - 152) : -1;
    int FourtiethPos = (i >= 156 && i < 169) ? (i - 156) : -1;
    int FourtyfirstPos = (i >= 160 && i < 173) ? (i - 160) : -1;
    int FourtysecondPos = (i >= 164 && i < 177) ? (i - 164) : -1;
    int FourtythirdPos = (i >= 168 && i < 181) ? (i - 168) : -1;
    int FourtyfourthPos = (i >= 172 && i < 185) ? (i - 172) : -1;
    int FourtyfifthPos = (i >= 176 && i < 189) ? (i - 176) : -1;
    int FourtysixthPos = (i >= 180 && i < 193) ? (i - 180) : -1;
    int FourtyseventhPos = (i >= 184 && i < 197) ? (i - 184) : -1;
    int FourtyeighthPos = (i >= 188 && i < 201) ? (i - 188) : -1;
    int FourtyninthPos = (i >= 192 && i < 205) ? (i - 192) : -1;
    int FiftiethPos = (i >= 196 && i < 209) ? (i - 196) : -1;
    int FiftyfirstPos = (i >= 200 && i < 213) ? (i - 200) : -1;
    int FiftysecondPos = (i >= 204 && i < 217) ? (i - 204) : -1;
    int FiftythirdPos = (i >= 208 && i < 221) ? (i - 208) : -1;
    int FiftyfourthPos = (i >= 212 && i < 225) ? (i - 212) : -1;
    int FiftyfifthPos = (i >= 216 && i < 229) ? (i - 216) : -1;
    int FiftysixthPos = (i >= 220 && i < 233) ? (i - 220) : -1;
    int FiftyseventhPos = (i >= 224 && i < 237) ? (i - 224) : -1;
    int FiftyeighthPos = (i >= 228 && i < 241) ? (i - 228) : -1;
    int FiftyninthPos = (i >= 232 && i < 245) ? (i - 232) : -1;
    int SixtiethPos = (i >= 236 && i < 249) ? (i - 236) : -1;


// ============================= LED Displaying Part =============================

    // Array of all positions where LEDs should turn ON for falling notes
    int positions[] = {
      FirstPos, SecondPos, ThirdPos, FourthPos, FifthPos, SixthPos, SeventhPos,
      NinthPos, TenthPos, EleventhPos, TwelfthPos, ThirteenthPos, FourteenthPos,
      FifteenthPos, SeventeenthPos, EighteenthPos, NineteenthPos, TwentiethPos,
      TwentyfirstPos, TwentysecondPos, TwentythirdPos, TwentyfifthPos, TwentysixthPos,
      TwentyseventhPos, TwentyeighthPos, TwentyninthPos, ThirtiethPos, ThirtyfirstPos,
      ThirtythirdPos, ThirtyfourthPos, ThirtyfifthPos, ThirtysixthPos, ThirtyseventhPos,
      ThirtyeighthPos, ThirtyninthPos, FourtyfirstPos, FourtysecondPos, FourtythirdPos,
      FourtyfourthPos, FourtyfifthPos, FourtysixthPos, FourtyseventhPos
    };

    // Corresponding notes for each falling LED (MIDI or frequency values assumed)
    int values[] = {
      C, C, G, G, A, A, G, F, F, E, E, D, D, C, G, G, F, F, E, E, D,
      G, G, F, F, E, E, D, C, C, G, G, A, A, G, F, F, E, E, D, D, C
    };

    int length = sizeof(positions) / sizeof(positions[0]);

    // Turn ON LEDs for each note in the matrix
    for (int j = 0; j < length; j++) {
      setLED(positions[j], values[j], 7); // 7 = brightness/intensity value
    }

    // Wait for DEL milliseconds before updating the display
    delay(DEL);

    // Turn OFF LEDs after the delay
    for (int k = 0; k < length; k++) {
      setLED(positions[k], values[k], 0); // 0 = off
    }


// ============================= Input Checking Part =============================

    // Define time windows (ranges) when each key must be pressed to be considered correct
    int ranges[][2] = {
      {9, 13}, {13, 17}, {17, 21}, {21, 25}, {25, 29}, {29, 33}, {33, 37},
      {41, 45}, {45, 49}, {49, 53}, {53, 57}, {57, 61}, {61, 65}, {65, 69},
      {73, 77}, {77, 81}, {81, 85}, {85, 89}, {89, 93}, {93, 97}, {97, 101},
      {105, 109}, {109, 113}, {113, 117}, {117, 121}, {121, 125}, {125, 129}, {129, 133},
      {137, 141}, {141, 145}, {145, 149}, {149, 153}, {153, 157}, {157, 161}, {161, 165},
      {169, 173}, {173, 177}, {177, 181}, {181, 185}, {185, 189}, {189, 193}, {193, 197}
    };

    // DEBUGGING: Can print which note is correct if needed
    // String messages[] = {"1Correct", "2Correct", ..., "nCorrect"};

    // Check if the user has pressed the correct key within the allowed range
    for (int m = 0; m < sizeof(ranges) / sizeof(ranges[0]); m++) {
      if (i > ranges[m][0] && i < ranges[m][1]) { // Time window check
        if (Key_Value != '0' && Key_Value != '\0') { // Ignore no input or invalid key
          if (Key_Value == expectedValues[m] && millis() - current_time > Between_DEL) {
            result = "Correct";
            Points++; // Add to score
            current_time = millis(); // Update time of last correct input
          } else if (Key_Value != expectedValues[m] && millis() - current_time > Between_DEL) {
            result = "Incorrect"; // Incorrect key press
          }
        }
      }
    }

    // If an incorrect key was pressed, exit the loop (end game)
    if (result == "Incorrect") {
      break;
    }

    // Reset key press input for next loop
    if (receivedKey != '\0') {
      receivedKey = '\0';
    }
    if (result != '\0') {
      result = '\0';
    }

    // Allow time before accepting the next button input
    Between_DEL = DEL * 2.2;

  }
// ============================= Game Result Handling =============================

  // What to do when game ends due to wrong input
  if (result == "Incorrect") {
    Serial.println("Game Over");
    Serial.print("At the end, you scored ");
    Serial.print(Points);
    Serial.println(" points.");
    DEL = DEL / 0.9; // Decrease speed for retry
    delay(3000);
    Points = 0; // Reset score
    delay(1000);
  }

  // If all inputs were correct till the end, level up
  else if (result == "Correct" || result == '\0') {
    DEL = DEL / 1.2; // Increase speed for next round
    Serial.println("Next Level");
    delay(2000);
  }

  // Reset result for next game loop
  if (result != '\0') {
    result = '\0';
  }
}
