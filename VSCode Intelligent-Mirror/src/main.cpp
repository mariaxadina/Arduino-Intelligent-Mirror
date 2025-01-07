#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Adafruit_NeoPixel.h>
#include <PCM.h>

// LCD pins
#define RS 8
#define ENABLE 6
#define D4 5
#define D5 4
#define D6 13
#define D7 10

LiquidCrystal lcd(RS, ENABLE, D4, D5, D6, D7);

// Sensor pins
#define SENSOR 7

// Led Strip pins
#define LED_PIN 12
#define NUM_LEDS 17
Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

// Speaker pin
#define SPEAKER 11

// Button pins
#define MUSIC_BTN 3     // Using pin 3 for interrupt
#define SET_ALARM_BTN 9
#define START_STOP_ALARM_BTN 2    // Using pin 2 for interrupt

const unsigned char AlarmSound [] = {113, 133, 142, 159, 191, 220, 227, 222, 210, 186, 149, 116};
const unsigned char Music [] PROGMEM = {133, 133, 133, 133, 133, 133, 133, 133, 133, 133, 133, 134, 134, 135, 136, 137, 138, 139, 141, 141, 142, 142, 141, 141, 140, 138, 137, 136, 135, 134, 133, 132, 132, 131, 131, 131, 131, 131, 131, 130, 130, 130, 130, 130, 130, 130, 130, 130, 131, 131, 132, 133, 134, 135, 135, 135, 135, 134, 133, 132, 131, 130, 129, 129, 128, 127, 127, 126, 126, 126, 126, 126, 125, 125, 125, 125, 125, 125, 124, 124, 124, 124, 123, 123, 123, 122, 122, 122, 121, 121, 121, 120, 120, 120, 120, 120, 119, 119, 119, 119, 118, 118, 118, 117, 117, 117, 117, 116, 116, 115, 115, 115, 114, 114, 113, 113, 113, 113, 113, 114, 114, 114, 115, 115, 116, 116, 117, 119, 120, 122, 124, 125, 127, 128, 129, 129, 129, 129, 128, 127, 126, 126, 125, 125, 124, 124, 124, 124, 124, 125, 125, 126, 126, 126, 126, 126, 127, 127, 127, 127, 128, 129, 130, 131, 132, 133, 133, 133, 133, 133, 133, 132, 131, 130, 129, 129, 128, 128, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 129, 129, 129, 129, 130, 130, 131, 131, 131, 132, 132, 133, 133, 133, 134, 134, 134, 134, 134, 134, 134, 133, 133, 133, 133, 133, 133, 133, 133, 133, 133, 133, 134, 134, 135, 136, 137, 138, 140, 141, 141, 142, 142, 141, 141, 140, 139, 137, 136, 135, 134, 133, 132, 132, 131, 131, 131, 131, 131, 131, 131, 131, 131, 131, 130, 130, 130, 130, 130, 130, 131, 132, 133, 133, 134, 135, 135, 135, 134, 134, 133, 132, 131, 130, 129, 128, 127, 127, 127, 126, 126, 126, 126, 126, 126, 125, 125, 125, 125, 125, 124, 124, 124, 124, 123, 123, 123, 122, 122, 121, 121, 121, 121, 120, 120, 120, 120, 120, 119, 119, 119, 118, 118, 118, 117, 117, 117, 117, 116, 116, 116, 115, 115, 114, 114, 114, 113, 113, 113, 113, 114, 114, 114, 115, 115, 116, 116, 118, 119, 120, 122, 124, 125, 127, 128, 129, 129, 129, 128, 128, 127, 126, 125, 125, 124, 124, 124, 124, 124, 124, 125, 125, 125, 126, 126, 126, 126, 126, 126, 126, 127, 127, 128, 129, 130, 131, 132, 132, 133, 133, 133, 132, 132, 131, 130, 129, 128, 128, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 129, 129, 129, 129, 130, 130, 131, 131, 132, 132, 133, 133, 133, 134, 134, 134, 134, 134, 134, 134, 134, 134, 133, 133, 133, 133, 133, 133, 133, 134, 134, 134, 134, 135, 136, 137, 138, 139, 140, 141, 142, 142, 142, 142, 141, 140, 139, 137, 136, 135, 134, 133, 133, 132, 132, 132, 132, 131, 131, 131, 131, 131, 131, 131, 130, 130, 130, 130, 130, 130, 130, 131, 132, 133, 133, 134, 135, 135, 134, 134, 133, 132, 131, 130, 129, 128, 127, 127, 126, 126, 126, 126, 126, 125, 125, 125, 125, 125, 125, 125, 124, 124, 124, 124, 123, 123, 122, 122, 122, 121, 121, 121, 121, 120, 120, 120, 120, 120, 119, 119, 119, 118, 118, 118, 118, 117, 117, 117, 117, 116, 116, 115, 115, 114, 114, 114, 113, 113, 113, 114, 114, 114, 115, 115, 115, 116, 117, 118, 119, 121, 122, 124, 125, 127, 127, 128, 128, 128, 128, 127, 126, 126, 125, 124, 124, 124, 124, 124, 124, 124, 125, 125, 125, 126, 126, 126, 126, 126, 126, 126, 126, 126, 127, 128, 129, 130, 131, 132, 132, 133, 133, 133, 132, 131, 131, 130, 129, 128, 127, 127, 127, 126, 126, 126, 126, 126, 127, 127, 127, 127, 127, 127, 127, 127, 127, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 129, 129, 129, 130, 130, 131, 131, 132, 132, 132, 133, 133, 134, 134, 134, 134, 135, 134, 134, 134, 134, 134, 133, 133, 133, 133, 133, 134, 134, 134, 134, 134, 135, 135, 136, 137, 138, 139, 140, 141, 142, 142, 142, 142, 141, 140, 139, 137, 136, 135, 134, 133, 133, 132, 132, 132, 131, 131, 131, 131, 131, 131, 131, 131, 131, 130, 130, 129, 129, 129, 130, 130, 131, 132, 132, 133, 134, 134, 134, 134, 133, 132, 131, 130, 129, 128, 127, 127, 126, 126, 126, 125, 125, 125, 125, 125, 125, 125, 125, 124, 124, 124, 124, 124, 123, 123, 122, 122, 122, 121, 121, 121, 121, 121, 120, 120, 120, 120, 120, 119, 119, 119, 118, 118, 118, 118, 117, 117, 117, 116, 116, 115, 115, 114, 114, 114, 114, 114, 114, 114, 114, 115, 115, 115, 116, 117, 117, 118, 120, 121, 123, 124, 125, 127, 127, 128, 128, 128, 128, 127, 126, 126, 125, 125, 124, 124, 124, 124, 124, 124, 125, 125, 125, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 127, 128, 129, 130, 131, 132, 132, 133, 133, 132, 132, 131, 130, 129, 128, 128, 127, 127, 126, 126, 126, 126, 126, 126, 126, 127, 127, 127, 127, 127, 127, 127, 127, 127, 128, 128, 128, 128, 128, 128, 128, 128, 128, 129, 129, 130, 130, 131, 131, 131, 132, 132, 133, 133, 133, 134, 134, 134, 134, 134, 134, 134, 133, 133, 133, 133, 133, 133, 133, 133, 134, 134, 134, 135, 135, 135, 136, 137, 138, 139, 140, 141, 142, 142, 142, 142, 141, 140, 139, 138, 136, 135, 134, 133, 133, 132, 132, 132, 131, 131, 131, 131, 131, 131, 131, 131, 130, 130, 130, 129, 129, 129, 129, 129, 130, 131, 132, 132, 133, 134, 134, 134, 133, 133, 132, 131, 130, 129, 128, 127, 127, 126, 126, 125, 125, 125, 125, 125, 125, 125, 125, 124, 124, 124, 124, 123, 123, 123, 122, 122, 121, 121, 121, 121, 121, 120, 120, 120, 120, 120, 120, 120, 119, 119, 119, 118, 118, 118, 117, 117, 117, 116, 116, 115, 115, 115, 114, 114, 114, 114, 115, 115, 115, 115, 116, 116, 116, 117, 118, 119, 120, 121, 123, 124, 126, 127, 128, 128, 129, 128, 128, 128, 127, 126, 126, 125, 125, 124, 124, 124, 124, 125, 125, 125, 126, 126, 126, 127, 127, 127, 126, 126, 126, 126, 126, 126, 127, 128, 129, 130, 131, 132, 133, 133, 133, 132, 132, 131, 130, 129, 128, 128, 127, 127, 127, 126, 126, 126, 126, 126, 126, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 128, 128, 128, 129, 129, 130, 130, 131, 131, 132, 132, 132, 133, 133, 133, 134, 134, 134, 134, 134, 133, 133, 133, 133, 133, 133, 133, 133, 134, 134, 134, 135, 135, 135, 136, 136, 137, 138, 139, 140, 141, 142, 142, 142, 142, 141, 140, 139, 138, 137, 135, 134, 134, 133, 132, 132, 132, 132, 131, 131, 131, 131, 131, 131, 130, 130, 130, 129, 129, 129, 129, 128, 129, 129, 129, 130, 131, 131, 132, 132, 132, 132, 131, 131, 130, 129, 128, 127, 126, 125, 125, 124, 124, 124, 123, 123, 123, 124, 124, 125, 126, 127, 128, 129, 129, 129, 129, 129, 128, 127, 126, 125, 124, 123, 122, 121, 120, 120, 119, 119, 119, 118, 118, 118, 117, 117, 116, 116, 116, 115, 115, 114, 114, 113, 113, 113, 112, 113, 113, 114, 114, 116, 117, 119, 120, 121, 122, 123, 124, 124, 123, 123, 122, 122, 121, 121, 120, 120, 120, 120, 120, 120, 121, 121, 121, 121, 122, 122, 122, 122, 122, 122, 123, 123, 123, 123, 124, 124, 124, 124, 124, 125, 125, 126, 128, 130, 132, 134, 136, 138, 139, 139, 138, 137, 136, 134, 132, 130, 129, 127, 127, 126, 126, 126, 126, 126, 126, 126, 127, 127, 127, 127, 127, 126, 126, 126, 126, 126, 126, 126, 126, 127, 127, 128, 129, 131, 133, 135, 137, 138, 139, 140, 140, 140, 139, 138, 137, 136, 135, 134, 133, 133, 133, 134, 134, 134, 135, 136, 136, 137, 138, 139, 139, 140, 141, 141, 141, 141, 140, 139, 138, 137, 136, 135, 135, 134, 134, 134, 135, 136, 137, 138, 139, 139, 139, 138, 137, 136, 134, 132, 130, 129, 128, 127, 127, 126, 126, 126, 127, 127, 127, 128, 128, 129, 130, 130, 131, 131, 131, 130, 130, 129, 128, 127, 126, 125, 124, 124, 124, 124, 125, 126, 127, 128, 129, 129, 129, 128, 127, 126, 124, 122, 121, 119, 118, 117, 116, 116, 115, 115, 115, 115, 116, 116, 117, 117, 118, 119, 119, 120, 120, 119, 119, 118, 117, 116, 115, 114, 114, 113, 113, 114, 115, 116, 118, 119, 120, 121, 121, 121, 121, 120, 118, 117, 116, 115, 114, 113, 113, 113, 114, 114, 115, 116, 117, 119, 120, 122, 123, 125, 126, 127, 128, 128, 127, 127, 126, 125, 125, 124, 124, 124, 124, 125, 127, 128, 130, 131, 133, 133, 134, 133, 132, 131, 130, 128, 127, 126, 125, 125, 125, 125, 125, 126, 127, 128, 129, 130, 132, 133, 135, 136, 137, 138, 139, 139, 139, 139, 138, 137, 136, 136, 135, 135, 135, 135, 137, 138, 139, 141, 142, 143, 143, 143, 142, 141, 140, 138, 137, 136, 135, 135, 134, 135, 135, 135, 135, 136, 136, 137, 137, 138, 139, 139, 140, 141, 141, 141, 141, 140, 140, 139, 138, 137, 136, 135, 134, 134, 134, 135, 135, 136, 137, 137, 137, 137, 136, 134, 133, 131, 129, 128, 127, 126, 125, 124, 124, 124, 124, 123, 123, 123, 123, 123, 124, 124, 124, 125, 125, 124, 124, 123, 122, 121, 119, 118, 117, 116, 116, 115, 116, 116, 117, 118, 119, 120, 120, 120, 119, 118, 117, 115, 114, 113, 112, 111, 111, 111, 111, 111, 112, 112, 112, 113, 114, 114, 115, 116, 117, 118, 118, 119, 119, 118, 118, 117, 116, 116, 115, 115, 115, 116, 117, 119, 120, 122, 124, 125, 126, 126, 125, 125, 123, 122, 121, 120, 120, 119, 120, 120, 121, 122, 123, 124, 126, 127, 128, 130, 132, 133, 135, 136, 137, 138, 138, 138, 138, 137, 137, 136, 136, 136, 136, 137, 138, 140, 141, 143, 144, 145, 145, 145, 145, 143, 142, 141, 139, 138, 137, 137, 136, 136, 137, 137, 137, 137, 138, 138, 138, 138, 139, 139, 139, 140, 140, 140, 140, 140, 139, 139, 138, 137, 136, 135, 135, 134, 135, 135, 136, 137, 137, 138, 138, 137, 136, 134, 132, 130, 128, 126, 125, 123, 122, 121, 121, 120, 120, 120, 119, 119, 119, 119, 119, 120, 120, 121, 121, 121, 121, 121, 120, 119, 119, 118, 117, 116, 115, 115, 116, 117, 118, 119, 120, 121, 122, 122, 122, 121, 119, 118, 117, 115, 114, 114, 113, 113, 113, 113, 113, 113, 113, 113, 114, 115, 115, 117, 118, 119, 120, 120, 121, 121, 120, 120, 119, 118, 118, 117, 117, 118, 119, 120, 123, 125, 127, 129, 131, 132, 132, 132, 131, 131, 130, 129, 129, 129, 129, 129, 129, 130, 130, 131, 132, 132, 133, 134, 135, 137, 138, 139, 140, 141, 142, 142, 142, 141, 141, 140, 139, 138, 138, 138, 138, 139, 140, 142, 143, 144, 144, 144, 144, 143, 142, 140, 139, 137, 136, 136, 135, 135, 135, 135, 135, 135, 135, 135, 135, 135, 135, 135, 135, 136, 136, 137, 137, 136, 136, 135, 134, 133, 131, 130, 129, 128, 127, 127, 127, 128, 128, 128, 128, 128, 127, 125, 124, 122, 120, 119, 117, 116, 115, 115, 115, 115, 114, 114, 114, 114, 114, 114, 114, 115, 116, 117, 117, 118, 119, 119, 119, 118, 117, 117, 115, 115, 114, 113, 114, 114, 115, 116, 117, 118, 119, 119, 118, 117, 116, 115, 114, 114, 113, 113, 113, 114, 115, 116, 117, 117, 118, 119, 119, 120, 121, 122, 124, 125, 127, 128, 130, 131, 131, 132, 132, 132, 132, 132, 132, 132, 133, 135, 136, 138, 140, 141, 142, 143, 143, 143, 142, 141, 139, 138, 138, 137, 137, 137, 137, 138, 138, 139, 139, 140, 140, 140, 140, 141, 142, 142, 143, 143, 144, 143, 143, 142, 141, 140, 138, 137, 136, 135, 135, 135, 136, 136, 137, 138, 138, 138, 137, 136, 134, 132, 130, 129, 127, 126, 125, 124, 123, 123, 123, 122, 122, 121, 120, 120, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 118, 117, 116, 115, 114, 114, 114, 115, 116, 117, 119, 119, 120, 120, 120, 119, 117, 116, 115, 114, 113, 113, 113, 113, 114, 115, 116, 117, 118, 118, 119, 120, 120, 121, 122, 124, 125, 126, 127, 127, 128, 128, 127, 127, 126, 126, 125, 126, 126, 128, 129, 131, 134, 136, 137, 139, 139, 139, 139, 138, 137, 137, 136, 135, 135, 135, 135, 135, 135, 136, 136, 136, 136, 136, 137, 137, 138, 139, 140, 141, 141, 142, 141, 141, 140, 139, 137, 136, 135, 134, 133, 133, 133, 134, 135, 136, 136, 136, 136, 135, 133, 131, 130, 128, 126, 125, 124, 123, 122, 121, 121, 120, 120, 119, 119, 118, 118, 118, 118, 118, 119, 119, 119, 120, 120, 119, 119};

volatile bool toggleMusicState = false;
unsigned long lastInterruptTimeMusicBTN = 0;
const unsigned long debounceDelay = 50;
volatile bool musicPlaying = false;

// Function to handle toggling the music state when the music button is pressed
void toggleMusic() {
  unsigned long currentTime = millis();

  if (currentTime - lastInterruptTimeMusicBTN > debounceDelay) {
      toggleMusicState = true;
      lastInterruptTimeMusicBTN = currentTime;
    }
        
}
// Function to play sound using the speaker, given an array of sound frequencies
void playSound(const unsigned char *soundData, unsigned int dataSize, unsigned int duration = 200) {
  for (unsigned int i = 0; i < dataSize; i++) {
    unsigned int frequency = soundData[i] * 10; // Scale frequency for better sound
    tone(SPEAKER, frequency, duration);        // Play the tone on the speaker
    delay(duration);                           // Wait for the tone to finish
    noTone(SPEAKER);                           // Stop the tone before moving to the next
  }
}
// Function to start playing the music
void playMusic() {
  musicPlaying = true;
  playSound(Music, sizeof(Music));
}
// Function to stop playing the music
void stopMusic() {
  musicPlaying = false;
  noTone(SPEAKER);
  stopPlayback();
}
// Function to turn on Led Strip
void turnOnLedStrip() {
  for (int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, strip.Color(255, 255, 255));     // White
  }
  strip.show();
}
// Function to turn off Led Strip
void turnOffLedStrip() {
  for (int i = 0; i < NUM_LEDS; i++) {
      strip.setPixelColor(i, strip.Color(0, 0, 0)); 
      strip.show();
      delay(50); 
    }
}
// Led animation for alarm
void alarmLedAnimation() {
  for (int i = 0; i < NUM_LEDS; i++) {
      strip.setPixelColor(i, strip.Color(255, 0, 128)); // Pink
      strip.show();
      delay(50); 
    }
  turnOffLedStrip();
  for (int i = 0; i < NUM_LEDS; i++) {
      strip.setPixelColor(i, strip.Color(0, 128, 255)); // Light Blue
      strip.show();
      delay(50); 
    }
  turnOffLedStrip();
  for (int i = 0; i < NUM_LEDS; i++) {
      strip.setPixelColor(i, strip.Color(128, 0, 255)); // Purple
      strip.show();
      delay(50); 
    }
  turnOffLedStrip();
}


// Variables needed for debouncing
int buttonState_1;
int lastButtonState_1 = HIGH;
unsigned long lastDebounceTime_1 = 0;

// Debouncing function for buttons
int debounceButton(int buttonPin, int &lastButtonState, unsigned long &lastDebounceTime, int &buttonState) { 
    int reading = digitalRead(buttonPin); // Read current button state (LOW or HIGH)

    if (reading != lastButtonState) { // If current state is different from the last recorded state (change from HIGH to LOW or vice versa)
        lastDebounceTime = millis(); // Start timing
    }

    if ((millis() - lastDebounceTime) > debounceDelay) { // If the signal persists beyond 50 ms, it means the button was pressed and not due to noise
        if (reading != buttonState) { // If the button state differs from its last stable state
            buttonState = reading; // Save the stable state of the button
        }
    }

    lastButtonState = reading; // Record the current state as the last one
    return buttonState;        // Return the current button state (LOW or HIGH)
}

// Variables to store the selected alarm time and the current key
int setTime = -1;
int key = -1;
const char *msg1 = "7 seconds timer";
const char *msg2 = "5 minute timer";
const char *msg3 = "10 minute timer";

// Function that cycles through the available alarm time options and displays them on the LCD
int selectTimeForAlarm() {
  key = (key + 1) % 3;
    switch (key) {
    case 0:
        lcd.clear();
        lcd.println(msg1);
        delay(500);
        break;
    case 1:
        lcd.clear();
        lcd.println(msg2);
        delay(500);
        break;
    case 2:
        lcd.clear();
        lcd.println(msg3);
        delay(500);
        break;
    default:
        break;
    }
    return key;
}

volatile bool toggleAlarmState = false;
unsigned long lastInterruptTime = 0;

// Interrupt function to toggle the alarm state when the alarm button is pressed
void toggleAlarm() {
  unsigned long currentTime = millis();

  if (currentTime - lastInterruptTime > debounceDelay) {
      toggleAlarmState = true;
      lastInterruptTime = currentTime;
    }
        
}

volatile bool alarmRunning = false;
unsigned long alarmTime = 0;

// Function to start the alarm with a specified set time
void startAlarm(int setTime) {
  if (setTime == 0)
        alarmTime = 7000;   // in ms 5 sec
    else if (setTime == 1)
        alarmTime = 300000;   // in ms 5 min
    else if (setTime == 2)
        alarmTime = 600000;   // in ms 10 min

  alarmRunning = true;
  Serial.println("Start alarm.");

}

// Function to stop the alarm
void stopAlarm() {
    alarmRunning = false;
    Serial.println("Stop alarm.");
    lcd.clear();
    lcd.print("Alarm stopped.");
}

unsigned long alarmStartTime = 0;

// Function to run the alarm, checking elapsed time and updating the display

void runAlarm() {
  static unsigned long lastUpdate = 0;
  unsigned long elapsed = millis() - alarmStartTime;
  unsigned long remaining = alarmTime - elapsed;

  // If alarm time is up, stop the alarm
  if (remaining <= 0) {
    alarmRunning = false;
    lcd.clear();
    lcd.print("Alarm Finished!");
    playSound(AlarmSound, sizeof(AlarmSound));
    alarmLedAnimation();
    stopPlayback();
    return;
  }

  // Update the display only at intervals (e.g., every 200ms)
  if (millis() - lastUpdate >= 200) {
    lastUpdate = millis();

    int minutes = remaining / 60000;              // Convert ms to minutes
    int seconds = (remaining % 60000) / 1000;     // Convert ms to seconds

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Time Left: ");
    lcd.setCursor(0, 1);
    if (minutes < 10) lcd.print("0");             // Leading zero for minutes
    lcd.print(minutes);
    lcd.print(":");
    if (seconds < 10) lcd.print("0");             // Leading zero for seconds
    lcd.print(seconds);
  }
}


void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);

  pinMode(MUSIC_BTN, INPUT_PULLUP);
  pinMode(SET_ALARM_BTN, INPUT_PULLUP);
  pinMode(START_STOP_ALARM_BTN, INPUT_PULLUP);

  strip.begin();
  strip.show();
  delay(50);
  strip.setBrightness(128);
  strip.show();

  pinMode(SENSOR, INPUT);
  delay(6000);   // 60 seconds for calibration

  lcd.setCursor(0, 0);
  lcd.print("Hello,world!");

  attachInterrupt(digitalPinToInterrupt(START_STOP_ALARM_BTN), toggleAlarm, FALLING);
  attachInterrupt(digitalPinToInterrupt(MUSIC_BTN), toggleMusic, FALLING);
}

bool alarmStarted = false;


void loop() {

  /* PIR Sensor checks if motion is detected. */

  if(digitalRead(SENSOR) == HIGH) {
    turnOnLedStrip();
  } else {
    turnOffLedStrip();
  }
  
  /* Button 1 (SET_ALARM_BTN) is used to cycle through predefined alarm time levels (e.g., 7 seconds, 5 minutes, or 10 minutes).
     Each time the button is pressed, it changes the alarm time selection. This allows the user to set the alarm duration by pressing the button multiple times. */

  if (digitalRead(SET_ALARM_BTN) == LOW && debounceButton(SET_ALARM_BTN, lastButtonState_1, lastDebounceTime_1, buttonState_1) == LOW) {
    setTime = selectTimeForAlarm();
    alarmStarted = false;
  }

  /* Button 2 (START_STOP_ALARM_BTN) is used to toggle the alarm on and off.
     When the button is pressed, an interrupt is triggered and the `toggleAlarmState` flag is set to true.
     This causes the alarm to either start or stop, depending on the current state of the `alarmRunning` flag. */
  
  if(toggleAlarmState) {
    toggleAlarmState = false;   // Clear the toggle flag
    Serial.println("interrupt");

    if (!alarmRunning) {
            lcd.clear();
            lcd.print("Alarm started!");  
            alarmStartTime = millis();
            startAlarm(setTime);
        } else {
            lcd.clear();
            lcd.print("Alarm stopped!");
            stopAlarm();
        }
  }

  if(alarmRunning) {
    runAlarm();
  }

  /* Button 3 (MUSIC_BTN) is used to toggle the music on and off.
     When the button is pressed, an interrupt is triggered and the `toggleMusicState` flag is set to true.
     This causes the music to either start or stop, depending on the current state of the `musicPlaying` flag. */

  if(toggleMusicState) {
    toggleMusicState = false;
    Serial.println("Music interrupt.");

    if(!musicPlaying) {
      //incep muzica
      playMusic();
      Serial.println("Music started.");
      
    } else {
      //opresc muzica
      stopMusic();
      Serial.println("Music Stopped.");
      
    }
  }
}

