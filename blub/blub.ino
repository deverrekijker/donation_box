const int interruptPin = 2;

const int MAX_PULSETRAIN_DURATION = 200;
int last_pulse = millis();
int current_pulse = 0;

int pulse_count = 0;

const char IDLE = 0;
const char PULSE_TRAIN_IN_PROGRESS = 1;
const char PULSE_TRAIN_END= 2;

char state = IDLE;

const int CENT50 = 10;

float coin_value(int coin) {
  float val = 0;
  switch(coin) {
    case CENT50:
      return 0.5;
  }
  return val;
}

float sum = 0;
float old_sum = 0;
int now = millis();
      
int last_coin = 0;

void setup() {
  Serial.begin(9600);
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), onPulse, RISING);
  
}

void loop() {  
  switch(state){
    case IDLE:
    if (sum != old_sum) {
      Serial.print("Last: ");
      Serial.println(last_coin);
      Serial.print("Last Coin Value: ");
      Serial.println(coin_value(last_coin));
      Serial.print("Sum: ");
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
      };
      };
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
  };
}
