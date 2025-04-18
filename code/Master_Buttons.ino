/*
  master_buttons.ino

  Description:
  This Arduino sketch serves as the master controller in a multi-Arduino setup for a custom-built piano game inspired by "Piano Tiles." 
  It reads button presses from 8 piano keys, modulates the note frequency based on potentiometer input (octave shift), 
  and plays the tones through a speaker. It also communicates over I2C with two slave Arduinos:
    - Slave 1 (Address 9): Receives key press information and returns updated score (points).
    - Slave 2 (Address 8): Receives the score to be displayed on an external display module.

  Key Features:
    - Button-based piano note triggering
    - Dynamic frequency shift using a potentiometer
    - Tone generation via speaker (buzz pin)
    - I2C communication for sending key inputs and transferring score

  Author: Zahid Muhammad Abdullah
  Date: July 2024
*/

#include <Wire.h>
#include <TimerOne.h>

// -------------------- Note Frequency Definitions --------------------
#define T_C 262
#define T_D 294
#define T_E 330
#define T_F 349
#define T_G 392
#define T_A 440
#define T_B 493
#define T_C1 524  // C one octave above

// -------------------- Pin Definitions --------------------
const int C = 3;
const int D = 4;
const int E = 5;
const int F = 6;
const int G = 7;
const int A = 8;
const int B = 9;
const int C1 = 10;
const int Buzz = 11;
const int potentiometerPin = A0; // For octave shift control

// -------------------- Global Variables --------------------
volatile int Points;     // Points received from Slave 1
int Sent_Points;         // Points to send to Slave 2

// -------------------- Setup --------------------
void setup() {
  Serial.begin(9600);
  Wire.begin(); // Join I2C bus as master

  // Initialize key input pins
  pinMode(C, INPUT_PULLUP);
  pinMode(D, INPUT_PULLUP);
  pinMode(E, INPUT_PULLUP);
  pinMode(F, INPUT_PULLUP);
  pinMode(G, INPUT_PULLUP);
  pinMode(A, INPUT_PULLUP);
  pinMode(B, INPUT_PULLUP);
  pinMode(C1, INPUT_PULLUP);

  Wire.setClock(40000); // Set I2C clock speed
  Wire.onReceive(receivePoint);  // I2C receive handler (not actually needed in master)
}

// -------------------- Play Tone with Octave Shift --------------------
void playTone(int baseFrequency, int octaveShift) {
  int frequency = baseFrequency * (1 << octaveShift); // frequency × 2^octaveShift
  tone(Buzz, frequency);
}

// -------------------- Send Key to Slave 1 --------------------
void sendKey(char key) {
  Wire.beginTransmission(9); // Address of Slave 1
  Wire.write(key);
  Wire.endTransmission();
}

// -------------------- Receive Score from Slave 1 --------------------
void receivePoint() {
  Wire.requestFrom(9, 6);  // Ask for up to 6 bytes from Slave 1
  while (Wire.available()) {
    int received = Wire.read();
    Serial.println(received); // Debug
    if (received >= 0 && received < 100) {
      Sent_Points = received;
    }
  }
}

// -------------------- Send Score to Slave 2 --------------------
void sendPoint(int Points) {
  Wire.beginTransmission(8); // Address of Slave 2
  Wire.write(Points);
  Wire.endTransmission();
}

// -------------------- Main Loop --------------------
void loop() {
  int potValue = analogRead(potentiometerPin);
  int octaveShift = map(potValue, 0, 1023, 0, 6);

  char keyPressed = '\0';

  // Read buttons and play corresponding tone
  if (digitalRead(C) == LOW) {
    playTone(T_C, octaveShift); keyPressed = 'C';
  } else if (digitalRead(D) == LOW) {
    playTone(T_D, octaveShift); keyPressed = 'D';
  } else if (digitalRead(E) == LOW) {
    playTone(T_E, octaveShift); keyPressed = 'E';
  } else if (digitalRead(F) == LOW) {
    playTone(T_F, octaveShift); keyPressed = 'F';
  } else if (digitalRead(G) == LOW) {
    playTone(T_G, octaveShift); keyPressed = 'G';
  } else if (digitalRead(A) == LOW) {
    playTone(T_A, octaveShift); keyPressed = 'A';
  } else if (digitalRead(B) == LOW) {
    playTone(T_B, octaveShift); keyPressed = 'B';
  } else if (digitalRead(C1) == LOW) {
    playTone(T_C1, octaveShift); keyPressed = 'P';
  } else {
    noTone(Buzz); // Silence if no key pressed
  }

  // Send key to Slave 1
  if (keyPressed != '\0') {
    sendKey(keyPressed);
  } else {
    sendKey('0'); // Indicates no key pressed
  }

  delay(150); // Debounce delay

  receivePoint();         // Get updated score from Slave 1
  sendPoint(Sent_Points); // Forward score to Slave 2
}
