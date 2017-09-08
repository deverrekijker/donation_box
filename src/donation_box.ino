#include "donation_box.h"
#include "storage/storage.h"
#include "lcd/lcd.h"

float sum = DEFAULT_SUM;
float oldSum = DEFAULT_SUM;

// Reset button
int resetState;
unsigned long lastDebounceTime = 0;
int ledState = LOW;
int lastLedState = ledState;

// For timing EEPROM writes
unsigned long lastStoreTime = 0;

// For timing our sum values sent over serial
unsigned long lastSendTime = 0;

// checkResetButton() - On function call, reads our RESET_PIN's state and resets our sum value to DEFAULT_SUM if RESET_VALUE is read.
void checkResetButton() {
  resetState = digitalRead(RESET_PIN);

  // Filter out any noise, by setting a small buffer using our debounce delay value
  if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {

    // If the reset button has been pressed and sum is not already default, activate the LED and set the sum to default value and activate the LED
    if (resetState == RESET_VALUE && sum != DEFAULT_SUM) {
        ledState = HIGH;
        sum = DEFAULT_SUM;
        Serial.println("RESET");
      }
    else {
      ledState = LOW;
    }
  }

  // If the LED state has changed
  if (ledState != lastLedState) {
    // Write our current LED state to our LED pin
    digitalWrite(LED_PIN, ledState);
    lastLedState = ledState;
  }
}

// setupLCD() - Initiates the LCD display with all components needed and displays INIT_MESSAGE when ready.
void setupLCD() {
  lcd.begin(LCD_X, LCD_Y);

  // Initialise each line of the lcd
  for (int i=0; i < LCD_Y; i++) {
    lcd.init();
  }

  // Initialise Euro character
  lcd.createChar(0, EURO_SYMBOL);

  lcd.backlight();

  lcd.clear();
  lcd.print(INIT_MESSAGE);

  delay(1000);

  lcd.clear();
  lcd.print(GENERAL_MESSAGE);
}

// updateLCD() - When called, updates the lcd display to show the latest sum.
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

// onPulse() - Called by our attachInterrupt each time a rising voltage is read on our COUNT_PIN (From the coin acceptor).
void onPulse() {
  sum += EUR_PER_PULSE;
}

// sendSum() - Simply sends our sum over serial and updates lastSendTime to indicate that a sum was just sent.
void sendSum() {
  Serial.println(sum);
  lastSendTime = millis();
}

void setup() {
  Serial.begin(BAUD_RATE);

  // Let's use the internal pull-up resistors for our pins
  pinMode(RESET_PIN, INPUT_PULLUP);
  pinMode(COUNT_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(COUNT_PIN), onPulse, RISING);

  if (PERSISTENCE == true) {
    float stored_sum = readFloat(START_ADDRESS); // Attempt to read stored sum from EEPROM
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

  // Init our lastXTime values
  lastStoreTime = millis();
  lastSendTime = millis();
}

void loop() {
  checkResetButton(); // First check if we have a reset button press

  // If our sum has been updated
  if (oldSum != sum) {
    delay(UPDATE_DELAY);

    if (ENABLE_LCD == true) {
      updateLCD();
    }

    oldSum = sum;
    lastStoreTime = millis();
  }

  // Check if our SERIAL_DELAY value has been exceeded and it's time to send a new value
  if ((millis() - lastSendTime) > SERIAL_DELAY) {
    sendSum();
  }

  if (PERSISTENCE == true) {
    // If STORE_DELAY is exceeded and the stored value is different to the current
    if ((millis() - lastStoreTime) > STORE_DELAY && readFloat(START_ADDRESS) != sum) {
      storeFloat(START_ADDRESS, sum); // write the new sum to EEPROM, overwriting the last stored value
    }
  }
}
