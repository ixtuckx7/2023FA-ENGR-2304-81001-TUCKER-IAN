#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int pressureSensorPin = A0;  // Analog pin for pressure sensor
const int motorPin = 9;           // Digital pin for motor
const int ledPin = 7;             // Digital pin for LED (D7)

int desiredPressure = 0;
int pressure = 0;

int leds[] = {13, 12, 8, 4}; // array of LED pin numbers

// I2C LCD Configuration
LiquidCrystal_I2C lcd(0x20, 20, 4);  // Set the I2C address of your LCD module, adjust if needed

void setup() {
  Serial.begin(9600);
  pinMode(motorPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  // initialize LED pins as outputs
  for (int i = 0; i < 4; i++) {
    pinMode(leds[i], OUTPUT);
  }

  // Initialize LCD with the correct I2C address and pins
  lcd.begin(16, 2);
  lcd.init();  // initialize the lcd
  lcd.backlight();  // turn on the backlight
  lcd.clear();
  lcd.print("Rocket Launcher");
  lcd.setCursor(0, 1);
  lcd.print("Countdown");
  delay(2000);
}

void loop() {
  // Prompt the user to enter the desired pressure
  Serial.println("Enter the desired pressure:");

  // Read the desired pressure from the Serial Monitor
  while (Serial.available() == 0) {
    delay(10);
  }

  desiredPressure = Serial.parseInt();

  // Regulate compressor output
  regulateCompressor();

  // Initiate rocket launcher countdown
  countdown(); // Using the provided countdown function
}

// Function to regulate compressor output
void regulateCompressor() {
  pressure = 0;

  while (pressure < desiredPressure) {
    // Simulate compressor action (replace this with actual hardware control)
    digitalWrite(motorPin, HIGH);  // Start the compressor
    delay(500);  // Simulate time passing
    pressure += 5;  // Simulate pressure increase
    Serial.print("Current Pressure: ");
    Serial.println(pressure);
  }

  digitalWrite(motorPin, LOW);  // Stop the compressor

  Serial.println("Desired pressure reached!");
}

// Function for the countdown
void countdown() {
  lcd.clear();
  lcd.print("Countdown Initiated");

  Serial.println("Rocket launcher countdown initiated:");

  for (int i = 15; i > 0; i--) { // Adjust the countdown range as needed
    // Convert the current count to binary and turn on/off the LEDs accordingly
    displayCountdown(i);

    lcd.setCursor(0, 1);
    lcd.print("Time: ");
    lcd.print(i);
    lcd.print("s");
    delay(1000);  // Simulate time passing
  }

  // Trigger rocket launcher (turn on LED)
  digitalWrite(ledPin, HIGH);
  lcd.clear();
  lcd.print("Rocket Launched!");
  delay(2000);  // Simulate rocket launch duration
  digitalWrite(ledPin, LOW);

  // Allow time for the LED to turn off before the next iteration
  delay(1000);
}

// Function to display the countdown on LEDs
void displayCountdown(int count) {
  for (int i = 0; i < 4; i++) {
    digitalWrite(leds[i], bitRead(count, i));
  }
}
