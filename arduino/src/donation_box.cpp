#include <Arduino.h>

#include "donation_box.h"
#include "storage.h"
#include "lcd.h"

float sum = 0.00;
float oldSum = 0.00;

// Reset button
int ledState = LOW;
int resetState;
int lastResetState = LOW;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

// For Timing EEPROM writes
unsigned long lastStoreTime = 0;

void checkResetButton() {
  int reading = digitalRead(RESET_PIN);

  // If the switch changed, due to noise or pressing:
  if (reading != lastResetState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // if the button state has changed:
    if (reading != resetState) {
      resetState = reading;

      if (resetState == HIGH) {
        ledState = HIGH;
        sum = 0.00;
      }
      else {
        ledState = LOW;
      }
    }
  }

  digitalWrite(LED_PIN, ledState);
  lastResetState = reading;
}

void setupLCD() {
  lcd.begin(LCD_X, LCD_Y);

  // Initialise each line of the lcd
  for (int i=0; i < LCD_Y; i++) {
    lcd.init();
  }

  // Initialise Euro character
  lcd.createChar(0, euro);

  lcd.backlight();

  lcd.clear();
  lcd.print(INIT_MESSAGE);

  delay(1000);

  lcd.clear();
  lcd.print(GENERAL_MESSAGE);
}

void updateLCD() {
  lcd.clear();
  lcd.print(GENERAL_MESSAGE);
  lcd.setCursor(0,1); // Move to line 1
  lcd.print(TOTAL_MESSAGE);
  lcd.setCursor(8,1); // TODO make dynamic according to length of message
  lcd.write(0);
  lcd.setCursor(9,1);
  lcd.print(sum);
}

void on_pulse() {
  sum += EUR_PER_PULSE;
}

void setup() {
  Serial.begin(BAUD_RATE);

  pinMode(RESET_PIN, INPUT);
  pinMode(COUNT_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(COUNT_PIN), on_pulse, RISING);

  if (PERSISTENCE == true) {
    float stored_sum = readSum(START_ADDRESS); // Attempt to read stored sum from EEPROM
    if (stored_sum != stored_sum) { // check for NaN
      //Serial.println("No stored value found");
    } else {
      sum = stored_sum;
      oldSum = sum;
    }
  }

  if (ENABLE_LCD == true) {
    setupLCD();
    updateLCD();
  }

  lastStoreTime = millis();
}

void loop() {
  if (oldSum != sum) {
    delay(UPDATE_DELAY);
    Serial.println(sum);

    if (ENABLE_LCD == true) {
      updateLCD();
    }

    oldSum = sum;
    lastStoreTime = millis();
  }

  if (PERSISTENCE == true) {
    checkResetButton();

    if ((millis() - lastStoreTime) > STORE_DELAY && readSum(START_ADDRESS) != sum) { // If STORE_DELAY is exceeded and the stored value is different to the current
      storeSum(START_ADDRESS, sum); // write the new sum to EEPROM, overwriting the last stored value
    }
  }
}
