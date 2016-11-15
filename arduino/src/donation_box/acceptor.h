#define INTERRUPT_PIN 2

// Miliseconds to wait for a pulse
const int MAX_PULSETRAIN_DURATION = 200;

// State machine values
const char IDLE = 0;
const char PULSE_TRAIN_IN_PROGRESS = 1;
const char PULSE_TRAIN_END = 2;

// Coin Pulses
const int CENT50 = 10;
