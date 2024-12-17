#include <Arduino.h>
#include <LiquidCrystal.h>

// LCD pins
#define RS 8
#define ENABLE 6
#define D4 5
#define D5 4
#define D6 3
#define D7 2

LiquidCrystal lcd(RS, ENABLE, D4, D5, D6, D7);

// Sensor pins
#define SENSOR 7

// Led Strip pins
#define LED 12

// Button pins
#define MUSIC_BTN 11
#define SET_ALARM_BTN 9
#define START_STOP_ALARM_BTN 10



void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);

  pinMode(MUSIC_BTN, INPUT_PULLUP);
  pinMode(SET_ALARM_BTN, INPUT_PULLUP);
  pinMode(START_STOP_ALARM_BTN, INPUT_PULLUP);
  
}

void loop() {
  
}

