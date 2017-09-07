const bool ENABLE_LCD = true;
const bool PERSISTENCE = true;

const int BAUD_RATE = 9600;

const int COUNT_PIN = 2;    // Pulse pin from the coin acceptor
const int RESET_PIN = 8;    // the number of the pushbutton pin
const int LED_PIN = 13;     // the number of the LED pin (13 is onboard for most Arduinos)

const int RESET_VALUE = 0; // The value needed to trigger a reset on our reset pin
const unsigned long DEBOUNCE_DELAY = 50; // Debounce value used for our reset pushbutton

const float DEFAULT_SUM = 0.00; // Default starting value for our sum
const float EUR_PER_PULSE = 0.05;   // Set a float value for each pulse recieved from the coin acceptor

const unsigned long UPDATE_DELAY = 100;   // Delay between updating the sum
const unsigned long STORE_DELAY = 5500;   // Delay between storing the sum

const unsigned long SERIAL_DELAY = 30000; // Delay between sending values over serial (to avoid spamming unnecessarily)
