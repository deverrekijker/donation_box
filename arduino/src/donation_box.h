const bool ENABLE_LCD = true;
const bool PERSISTENCE = true;

const int BAUD_RATE = 9600;

const int COUNT_PIN = 2;    // Pulse pin from the coin acceptor
const int RESET_PIN = 7;    // the number of the pushbutton pin
const int LED_PIN = 13;     // the number of the LED pin (13 is onboard for most Arduinos)

const float EUR_PER_PULSE = 0.05;   // Set a float value for each pulse recieved from the coin acceptor

const unsigned long UPDATE_DELAY = 100;   // Delay between updating the sum
const unsigned long STORE_DELAY = 5500;   // Delay between storing the sum
