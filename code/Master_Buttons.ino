#include <Wire.h>
#include <TimerOne.h>

// Defining Frequency Values For Notes
#define T_C 262
#define T_D 294
#define T_E 330
#define T_F 349
#define T_G 392
#define T_A 440
#define T_B 493
#define T_C1 262*2

// Pin Numbers for Notes
const int C = 3;
const int D = 4;
const int E = 5;
const int F = 6;
const int G = 7;
const int A = 8;
const int B = 9;
const int C1 = 10;

volatile int Points; // Variable to store points received from slave
int Sent_Points; // Variable to store points to be sent to another slave

// Pin For Speaker
const int Buzz = 11;

// const int LED = 13; For Debugging

// Reading Pin from Potentiometer
const int potentiometerPin = A0;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  // pinMode(LED, OUTPUT); For Debugging

  // Set up input pins for keys with internal pull-up resistors
  pinMode(C, INPUT_PULLUP);
  pinMode(D, INPUT_PULLUP);
  pinMode(E, INPUT_PULLUP);
  pinMode(F, INPUT_PULLUP);
  pinMode(G, INPUT_PULLUP);
  pinMode(A, INPUT_PULLUP);
  pinMode(B, INPUT_PULLUP);
  pinMode(C1, INPUT_PULLUP);

  Wire.setClock(40000); // Set I2C clock speed
  Wire.onReceive(receivePoint);  // Register receive event handler for I2C
  // Timer1.initialize(100000);
  // Timer1.attachInterrupt(receivePoint);
  
}

// To Play frequencies and different Octaves on Speaker 
void playTone(int baseFrequency, int octaveShift) {
  int frequency = baseFrequency * (1 << octaveShift); // Multiply base frequency by 2^octaveShift
  tone(Buzz, frequency); // Play the calculated frequency on the speaker
  // digitalWrite(LED, HIGH); For DEBUGGING
}

// To Send Key Values to Slave Arduino 1 
void sendKey(char key) {
  Wire.beginTransmission(9); // Begin transmission to slave with address 9
  Wire.write(key); // Write the key value
  Wire.endTransmission(); // End transmission
}

// To Receive Points Values from Slave Arduino 1
void receivePoint() {
  Wire.requestFrom(9, 6);  // Request data from slave with address 9
  while (Wire.available()) { // While data is available
    int Points = Wire.read(); // Read points value
    Serial.println(Points); // Print points value for debugging
    if(Points >=0 && Points < 100){
    Sent_Points = Points; // Store valid points value
    }
}
}

// To Send Points Value to Slave Arduino 2
void sendPoint(int Points) {
  Wire.beginTransmission(8); // Begin transmission to slave with address 8
  Wire.write(Points); // Write the points value
  Wire.endTransmission(); // End transmission
}

void loop() {
  int potValue = analogRead(potentiometerPin); // Read potentiometer value
  int octaveShift = map(potValue, 0, 1023, 0, 6); // Map potentiometer value to an octave shift between 0 and 6

  char keyPressed = '\0'; // Variable to store the key pressed

// Check each key pin and play the corresponding tone if pressed
  if (digitalRead(C) == LOW) {
    playTone(T_C, octaveShift);
    keyPressed = 'C';
  } else if (digitalRead(D) == LOW) {
    playTone(T_D, octaveShift);
    keyPressed = 'D';
  } else if (digitalRead(E) == LOW) {
    playTone(T_E, octaveShift);
    keyPressed = 'E';
  } else if (digitalRead(F) == LOW) {
    playTone(T_F, octaveShift);
    keyPressed = 'F';
  } else if (digitalRead(G) == LOW) {
    playTone(T_G, octaveShift);
    keyPressed = 'G';
  } else if (digitalRead(A) == LOW) {
    playTone(T_A, octaveShift);
    keyPressed = 'A';
  } else if (digitalRead(B) == LOW) {
    playTone(T_B, octaveShift);
    keyPressed = 'B';
  } else if (digitalRead(C1) == LOW) {
    playTone(T_C1, octaveShift);
    keyPressed = 'P';
  } else {
    noTone(Buzz); // Turn off the speaker if no key is pressed
    // digitalWrite(LED, LOW);
  }

  // Send key value to the first slave if a key was pressed, otherwise indicate no key pressed
  if (keyPressed != '\0') {
    sendKey(keyPressed);
  } else {
    sendKey('0'); // Indicate no key is pressed
  }
  delay(150);// Delay to debounce key press
  // Serial.println(keyPressed); FOR DEBUGGING
  
  // Send Key Values to Slave Arduino 1
  sendKey(keyPressed);

  //  Receiver Point Values from Slave Arduino 1
  receivePoint();

  // Send Point Values to Slave Arduino 2
  sendPoint(Sent_Points);
  // Serial.println(Points); For DEBUGGING
}

