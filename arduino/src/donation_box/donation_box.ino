
const int interruptPin = 2;
const float EUR_PER_PULSE = 0.05;

float sum = 0;
float old_sum = 0;

void setup() {
  Serial.begin(9600);
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), onPulse, RISING);  
}

void loop() {  
  if (old_sum != sum){
    Serial.println(sum);
    old_sum = sum;
    
  }
}

void onPulse() {
  sum += EUR_PER_PULSE;
}
