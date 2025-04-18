/*
  Title    : Slave2 Display Controller for Score
  Author   : Zahid Muhammad Abdullah
  Date     : July 2024
  Purpose  : This Arduino sketch is designed to run on a secondary (slave) Arduino 
             that receives score values over I2C from a master Arduino. The score 
             (0–99) is displayed on a dual 7-segment LED display using PORTD, 
             PORTB, and PORTC to control the segments. Timer1 is also initialized 
             to update the display at fixed intervals.
*/

#include <Wire.h>
#include <TimerOne.h>

int Score = 0;

void setup() {
  // Set all PORTD, PORTB, and PORTC pins to OUTPUT
  DDRD = 0xFF;
  DDRB = 0xFF;
  DDRC = 0xFF;

  // Initialize I2C as a slave with address 8
  Wire.begin(8);
  Wire.onReceive(receiveScore); // Register the I2C receive callback

  // Initialize Timer1 to trigger every 100ms
  Timer1.initialize(100000); 
  Timer1.attachInterrupt(receiveScore); // Also trigger score update periodically

  Serial.begin(9600); // Initialize Serial for debugging (optional)
}

// Function to receive score via I2C from the master Arduino
void receiveScore(int bytes) {
  while (Wire.available()) {
    Score = Wire.read(); // Read and store the score
    // Serial.println(Score); // Uncomment for debugging
  }
}

// Clears all LEDs by resetting all ports
void clearLEDs() {
  PORTD = 0;
  PORTB = 0;
  PORTC = 0;
}

// Displays a digit on the right side 7-segment display
void setLEDsRight(char number) {
  clearLEDs();
  switch (number) {
    case '0': PORTD |= 0b01100000; PORTB |= 0b00010011; PORTC |= 0b00000001; break;
    case '1': PORTB |= 0b00000011; break;
    case '2': PORTD |= 0b11100000; PORTB |= 0b00010010; break;
    case '3': PORTD |= 0b11000000; PORTB |= 0b00010011; break;
    case '4': PORTD |= 0b10000000; PORTB |= 0b00000011; PORTC |= 0b00000001; break;
    case '5': PORTD |= 0b11000000; PORTB |= 0b00010001; PORTC |= 0b00000001; break;
    case '6': PORTD |= 0b11100000; PORTB |= 0b00010001; PORTC |= 0b00000001; break;
    case '7': PORTB |= 0b00010011; break;
    case '8': PORTD |= 0b11100000; PORTB |= 0b00010011; PORTC |= 0b00000001; break;
    case '9': PORTD |= 0b11000000; PORTB |= 0b00010011; PORTC |= 0b00000001; break;
  }
}

// Displays a digit on the left side 7-segment display
void setLEDsLeft(char number) {
  clearLEDs();
  switch (number) {
    case '0': break; // All segments off (optional zero)
    case '1': PORTD |= 0b00010000; PORTB |= 0b00100000; break;
    case '2': PORTD |= 0b00001000; PORTB |= 0b00101000; PORTC |= 0b00011010; break;
    case '3': PORTD |= 0b00011000; PORTB |= 0b00100000; PORTC |= 0b00011010; break;
    case '4': PORTD |= 0b00010000; PORTB |= 0b00100000; PORTC |= 0b00001100; break;
    case '5': PORTD |= 0b00011000; PORTB |= 0b00000000; PORTC |= 0b00011110; break;
    case '6': PORTD |= 0b00011000; PORTB |= 0b00001000; PORTC |= 0b00011110; break;
    case '7': PORTD |= 0b00010000; PORTB |= 0b00100000; PORTC |= 0b00000010; break;
    case '8': PORTD |= 0b00011000; PORTB |= 0b00101000; PORTC |= 0b00001110; break;
    case '9': PORTD |= 0b00011000; PORTB |= 0b00100000; PORTC |= 0b00011110; break;
  }
}

// Displays a 2-digit number (00–99) using both 7-segment displays
void setTwoDigitDisplay(int number) {
  if (number < 0 || number > 99) return; // Guard against invalid input
  char leftDigit = '0' + (number / 10);
  char rightDigit = '0' + (number % 10);

  setLEDsLeft(leftDigit);  // Show tens place
  delay(10);
  setLEDsRight(rightDigit); // Show units place
  delay(10);
}

void loop() {
  setTwoDigitDisplay(Score); // Continuously update the display with current score
  // Serial.println(Score); // Uncomment for live debugging
}

