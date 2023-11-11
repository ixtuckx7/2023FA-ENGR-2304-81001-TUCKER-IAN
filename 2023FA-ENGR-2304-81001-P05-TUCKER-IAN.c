#include <LiquidCrystal.h> // Include the LCD library

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // Initialize the LCD object

void setup() {
  lcd.begin(16, 2); // Initialize the LCD with 16 columns and 2 rows
  lcd.print("Hello World!"); // Display the text
}

void loop() {
  // Your code for additional functionality
}