#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#include <acceptor.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  // set the LCD address to 0x20 for a 16 chars and 2 line display
//LiquidCrystal_I2C lcd(0x38,16,2);  //if the LCD does not work, please use the other address:0x38

int now = millis();
int last_coin = 0;
int pulse_count = 0;
int last_pulse = millis();

int current_pulse = 0;

float sum = 0;
float old_sum = 0;

char state = IDLE;

float coin_value(int coin) {
  float val = 0;
  switch(coin) {
    case CENT50:
      return 0.5;
  }
  return val;
}

void setup_lcd() {
  lcd.begin(16,2);               // initialize the lcd
  //lcd.init();                      // initialize the lcd

  lcd.init();                      // initialize the lcd
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.print("MONEYBOX IS GO");
  delay(2000);
  lcd.clear();
  lcd.print("GIMME COINS");
};

void setup() {
  Serial.begin(9600);
  pinMode(INTERRUPT_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), onPulse, RISING);

  setup_lcd();
}

void loop() {
  switch(state){
    case IDLE:
    if (sum != old_sum) {
      Serial.print("Pulses: ");

      Serial.println(pulse_count);
      Serial.print("Last Coin Value: ");
      Serial.println(coin_value(last_coin));
      Serial.print("Sum: ");

      lcd.clear();
      lcd.print("GIMME COINS");
      lcd.setCursor(0,1);
      lcd.print("Total: €");
      lcd.setCursor(9,1);
      lcd.print(sum);

      Serial.println(sum);
      old_sum = sum;
    }

      break;
    case PULSE_TRAIN_IN_PROGRESS:
      state = PULSE_TRAIN_END;
      delay(20);
     if (state == PULSE_TRAIN_END){

      if (now - last_pulse > MAX_PULSETRAIN_DURATION) {
        state = IDLE;
        last_coin = pulse_count;
        sum = sum + coin_value(last_coin);
      }
    }

    case PULSE_TRAIN_END:
      now = millis();

      if (now - last_pulse > MAX_PULSETRAIN_DURATION) {
        last_coin = pulse_count;
        sum = sum + coin_value(last_coin);
        state = IDLE;
      }
    }
  }

void onPulse() {
  last_pulse = millis();
  switch(state) {
    case IDLE:
      pulse_count = 1;
      state = PULSE_TRAIN_IN_PROGRESS;
      break;
    case PULSE_TRAIN_IN_PROGRESS:
      pulse_count++;
      break;
    case PULSE_TRAIN_END:
      pulse_count++;
      state = PULSE_TRAIN_IN_PROGRESS;
  }
}
