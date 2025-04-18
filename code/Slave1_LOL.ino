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

#include <Charliplexing.h>
#include <Figure.h>
#include <Font.h>
#include <Wire.h>
#include <TimerOne.h>

// Column definitions for notes
int C=8, D=7, E=6, F=5, G=4, A=3, B=2, C_=1;

volatile char receivedKey = '\0'; // To store received key from I2C
int DEL = 250; // Delay between LED updates
int Points = 0; // Score points
char Key_Value; // Variable to store actual received key
char expectedValues[] = {'C', 'C', 'G', 'G', 'A', 'A', 'G', 'F', 'F', 'E', 'E', 'D', 'D', 'C', 'G', 'G', 'F', 'F', 'E', 'E', 'D','G', 'G', 'F', 'F', 'E', 'E', 'D',
                'C', 'C', 'G', 'G', 'A', 'A', 'G', 'F', 'F', 'E', 'E', 'D', 'D', 'C'};

String result;
unsigned long current_time = millis();  // To store current time
int Between_DEL; // Delay between checks for button press


void setup() {
  // Initialize the LED display
  LedSign::Init();
  Wire.begin(9);
  Wire.onReceive(receiveEvent);
  Timer1.initialize(100000);
  Timer1.attachInterrupt(receiveEvent);
  Serial.begin(9600);
  Wire.onRequest(sendPoint);
}

// Function to set LED states and bring them down the column
void setLED(int pos, int row, int state) {
  if (pos >= 0 && pos < 14) { // Check if position is within valid range
    LedSign::Set(pos, row, state);
    LedSign::Set(pos + 1, row, state); // Turn on the next LED in the same row
  }
}

// Function for Receiving Key Values from MASTER Arduino
void receiveEvent(int bytes) {
  while (Wire.available()) {
    receivedKey = Wire.read(); // Read one character from the I2C
    // Serial.print("Received: "); For DEBUGGING
    // Serial.println(receivedKey); For DEBUGGING
    if(receivedKey !='\0'){
      Key_Value = receivedKey; // Keys received other than null values
    }
  }
}

// Function to Send Calculated Point Values to MASTER Arduino
void sendPoint(){
  Wire.write(Points);
  // Serial.println(Points); For DEBUGGING
}


void loop() {
  for (int i = 0; i < 200; i++) {
    // Define Positions of notes.
    int FirstPos = (i < 13) ? i : -1; // Disappear if goes above 12
    int SecondPos = (i >= 4 && i < 17) ? (i - 4) : -1; // Disappear if goes above 16
    int ThirdPos = (i >= 8 && i < 21) ? (i - 8) : -1; // Disappear if goes above 20
    int FourthPos = (i >= 12 && i < 25) ? (i - 12) : -1; // Disappear if goes above 24
    int FifthPos = (i >= 16 && i < 29) ? (i - 16) : -1; // Disappear if goes above 28
    int SixthPos = (i >= 20 && i < 33) ? (i - 20) : -1; // Disappear if goes above 32
    int SeventhPos = (i >= 24 && i < 37) ? (i - 24) : -1; // Disappear if goes above 36
    int EigthPos = (i >= 28 && i < 41) ? (i - 28) : -1; // Disappear if goes above 40
    int NinthPos = (i >= 32 && i < 45) ? (i - 32) : -1; // Disappear if goes above 44
    int TenthPos = (i >= 36 && i < 49) ? (i - 36) : -1; // Disappear if goes above 48
    int EleventhPos = (i >= 40 && i < 53) ? (i - 40) : -1; // Disappear if goes above 52
    int TwelfthPos = (i >= 44 && i < 57) ? (i - 44) : -1; // Disappear if goes above 56
    int ThirteenthPos = (i >= 48 && i < 61) ? (i - 48) : -1; // Disappear if goes above 60
    int FourteenthPos = (i >= 52 && i < 65) ? (i - 52) : -1; // Disappear if goes above 64
    int FifteenthPos = (i >= 56 && i < 69) ? (i - 56) : -1; // Disappear if goes above 68
    int SixteenthPos = (i >= 60 && i < 73) ? (i - 60) : -1; // Disappear if goes above 72
    int SeventeenthPos = (i >= 64 && i < 77) ? (i - 64) : -1; // Disappear if goes above 76
    int EighteenthPos = (i >= 68 && i < 81) ? (i - 68) : -1; // Disappear if goes above 80
    int NineteenthPos = (i >= 72 && i < 85) ? (i - 72) : -1; // Disappear if goes above 84
    int TwentiethPos = (i >= 76 && i < 89) ? (i - 76) : -1; // Disappear if goes above 88
    int TwentyfirstPos = (i >= 80 && i < 93) ? (i - 80) : -1; // Disappear if goes above 92
    int TwentysecondPos = (i >= 84 && i < 97) ? (i - 84) : -1; // Disappear if goes above 96
    int TwentythirdPos = (i >= 88 && i < 101) ? (i - 88) : -1; // Disappear if goes above 100
    int TwentyfourthPos = (i >= 92 && i < 105) ? (i - 92) : -1; // Disappear if goes above 104
    int TwentyfifthPos = (i >= 96 && i < 109) ? (i - 96) : -1; // Disappear if goes above 108
    int TwentysixthPos = (i >= 100 && i < 113) ? (i - 100) : -1; // Disappear if goes above 112
    int TwentyseventhPos = (i >= 104 && i < 117) ? (i - 104) : -1; // Disappear if goes above 116
    int TwentyeighthPos = (i >= 108 && i < 121) ? (i - 108) : -1; // Disappear if goes above 120
    int TwentyninthPos = (i >= 112 && i < 125) ? (i - 112) : -1; // Disappear if goes above 124
    int ThirtiethPos = (i >= 116 && i < 129) ? (i - 116) : -1; // Disappear if goes above 128
    int ThirtyfirstPos = (i >= 120 && i < 133) ? (i - 120) : -1; // Disappear if goes above 132
    int ThirtysecondPos = (i >= 124 && i < 137) ? (i - 124) : -1; // Disappear if goes above 136
    int ThirtythirdPos = (i >= 128 && i < 141) ? (i - 128) : -1; // Disappear if goes above 140
    int ThirtyfourthPos = (i >= 132 && i < 145) ? (i - 132) : -1; // Disappear if goes above 144
    int ThirtyfifthPos = (i >= 136 && i < 149) ? (i - 136) : -1; // Disappear if goes above 148
    int ThirtysixthPos = (i >= 140 && i < 153) ? (i - 140) : -1; // Disappear if goes above 152
    int ThirtyseventhPos = (i >= 144 && i < 157) ? (i - 144) : -1; // Disappear if goes above 156
    int ThirtyeighthPos = (i >= 148 && i < 161) ? (i - 148) : -1; // Disappear if goes above 160
    int ThirtyninthPos = (i >= 152 && i < 165) ? (i - 152) : -1; // Disappear if goes above 164
    int FourtiethPos = (i >= 156 && i < 169) ? (i - 156) : -1; // Disappear if goes above 168
    int FourtyfirstPos = (i >= 160 && i < 173) ? (i - 160) : -1; // Disappear if goes above 172
    int FourtysecondPos = (i >= 164 && i < 177) ? (i - 164) : -1; // Disappear if goes above 176
    int FourtythirdPos = (i >= 168 && i < 181) ? (i - 168) : -1; // Disappear if goes above 180
    int FourtyfourthPos = (i >= 172 && i < 185) ? (i - 172) : -1; // Disappear if goes above 184
    int FourtyfifthPos = (i >= 176 && i < 189) ? (i - 176) : -1; // Disappear if goes above 188
    int FourtysixthPos = (i >= 180 && i < 193) ? (i - 180) : -1; // Disappear if goes above 192
    int FourtyseventhPos = (i >= 184 && i < 197) ? (i - 184) : -1; // Disappear if goes above 196
    int FourtyeighthPos = (i >= 188 && i < 201) ? (i - 188) : -1; // Disappear if goes above 200
    int FourtyninthPos = (i >= 192 && i < 205) ? (i - 192) : -1; // Disappear if goes above 204
    int FiftiethPos = (i >= 196 && i < 209) ? (i - 196) : -1; // Disappear if goes above 208
    int FiftyfirstPos = (i >= 200 && i < 213) ? (i - 200) : -1; // Disappear if goes above 212
    int FiftysecondPos = (i >= 204 && i < 217) ? (i - 204) : -1; // Disappear if goes above 216
    int FiftythirdPos = (i >= 208 && i < 221) ? (i - 208) : -1; // Disappear if goes above 220
    int FiftyfourthPos = (i >= 212 && i < 225) ? (i - 212) : -1; // Disappear if goes above 224
    int FiftyfifthPos = (i >= 216 && i < 229) ? (i - 216) : -1; // Disappear if goes above 228
    int FiftysixthPos = (i >= 220 && i < 233) ? (i - 220) : -1; // Disappear if goes above 232
    int FiftyseventhPos = (i >= 224 && i < 237) ? (i - 224) : -1; // Disappear if goes above 236
    int FiftyeighthPos = (i >= 228 && i < 241) ? (i - 228) : -1; // Disappear if goes above 240
    int FiftyninthPos = (i >= 232 && i < 245) ? (i - 232) : -1; // Disappear if goes above 244
    int SixtiethPos = (i >= 236 && i < 249) ? (i - 236) : -1; // Disappear if goes above 248


    // For LEDs corresponding to the melody to come down the column

    // Define positions for LEDs according to the melody's notes and Delays
    int positions[] = {FirstPos, SecondPos, ThirdPos, FourthPos, FifthPos, SixthPos, SeventhPos,
                   NinthPos, TenthPos, EleventhPos, TwelfthPos, ThirteenthPos, FourteenthPos,
                   FifteenthPos, SeventeenthPos, EighteenthPos, NineteenthPos, TwentiethPos,
                   TwentyfirstPos, TwentysecondPos, TwentythirdPos, TwentyfifthPos, TwentysixthPos,
                   TwentyseventhPos, TwentyeighthPos, TwentyninthPos, ThirtiethPos, ThirtyfirstPos,
                   ThirtythirdPos, ThirtyfourthPos, ThirtyfifthPos, ThirtysixthPos, ThirtyseventhPos,
                   ThirtyeighthPos, ThirtyninthPos, FourtyfirstPos, FourtysecondPos, FourtythirdPos,
                   FourtyfourthPos, FourtyfifthPos, FourtysixthPos, FourtyseventhPos};
    
    // Dofining notes at above mentioned Positions
    int values[] = {C, C, G, G, A, A, G, F, F, E, E, D, D, C, G, G, F, F, E, E, D, G, G, F, F, E, E, D,
                C, C, G, G, A, A, G, F, F, E, E, D, D, C};

    int length = sizeof(positions) / sizeof(positions[0]);

    // Turn on the LEDs for each note in the column
    for (int j = 0; j < length; j++) {
      setLED(positions[j], values[j], 7);
    }
    // Wait before next LED update
    delay(DEL);

    // Turn off the LEDs for each note in the column
    for (int k = 0; k < length; k++) {
      setLED(positions[k], values[k], 0);
    }


// The Checking Part


// Define the ranges to check if Button is pressed at the right time
    int ranges[][2] = {
        {9, 13}, {13, 17}, {17, 21}, {21, 25}, {25, 29}, {29, 33}, {33, 37},
        {41, 45}, {45, 49}, {49, 53}, {53, 57}, {57, 61}, {61, 65}, {65, 69},
        {73, 77}, {77, 81}, {81, 85}, {85, 89}, {89, 93}, {93, 97}, {97, 101},
        {105,109}, {109,113}, {113,117}, {117,121}, {121,125}, {125,129}, {129,133},
        {137,141}, {141,145}, {145,149}, {149,153}, {153,157}, {157,161}, {161,165},
        {169,173}, {173,177}, {177,181}, {181,185}, {185,189}, {189,193}, {193,197}
      };


    // String messages[] = {"1Correct", "2Correct", "3Correct", "4Correct", "5Correct", "6Correct", "7Correct", "8Correct", "9Correct", 
    //                  "10Correct", "11Correct", "12Correct", "13Correct", "14Correct", "15Correct", "16Correct", "17Correct", 
                    //  "18Correct", "19Correct", "20Correct", "21Correct"}; For DEBUGGING


        // For Checking if Right Button was pressed 
        for (int m = 0; m < sizeof(ranges) / sizeof(ranges[0]); m++) { 
        if (i > ranges[m][0] && i < ranges[m][1]) { // if the button was in the right range of last LEDs
          if (Key_Value != '0' && Key_Value != '\0') { // Ignore receieved key values that are null and zeroes
              if (Key_Value == expectedValues[m] && millis() - current_time > Between_DEL) { // If key values matches and are pressed at the right time
                  // Serial.println("Correct");
                  result = "Correct";
                  Points++; // Calculating Points
                  current_time = millis();  // Record the time of the correct note
              }else if(Key_Value != expectedValues[m] && (millis() - current_time > Between_DEL)){ // If key values does not matche
                    result = "Incorrect";
                    // Serial.println("Incorrect");
                      // Reset the flag
               }
          }
        }
      }
      
      // To Stop the game if an incorrect button was pressed
      if (result == "Incorrect"){
        break;
      }


    // Resetting the result and received Key Values
    if(receivedKey !='\0'){
      receivedKey = '\0';
    }
    if(result !='\0'){
      result = '\0';
    }
      // Serial.println(result); For DEBUGGING

      // Delay to allow button to be pressed within a range of last 4 LEDs and not Repeat the results
      Between_DEL = DEL * 2.2;

  }
  // What to Do if the game was over because of incorrect Key Pressed
  if (result == "Incorrect"){
    Serial.println("Game Over");
    Serial.print("At the end, Key_Valueu scored "); Serial.print(Points); Serial.println(" points.");
    DEL = DEL/0.9; // Decrease the Speed of the Game
    delay(3000);
    Points = 0; //Resetting the Points to 0
    delay(1000);
  }else if (result == "Correct" || result == '\0'){ // What to do if an incorrect Key was never pressed.
    DEL = DEL/1.2; // Increase the Speed for the Next Level.
    Serial.println("Next Level");
    delay(2000);
  }
  if(result !='\0'){ // resetting the result variable
      result = '\0';
    }
}

