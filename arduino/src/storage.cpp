#include <Arduino.h>
#include <EEPROM.h>
#include "storage.h"

float readSum(unsigned int addr) {
  union {
    byte b[FLOAT_SIZE];
    float f;
  } data;

  for(int i = 0; i < FLOAT_SIZE; i++) {
    data.b[i] = EEPROM.read(addr+i);
  }

  return data.f;
}

void storeSum(unsigned int addr, float x) {
  union {
    byte b[FLOAT_SIZE];
    float f;
  } data;

  data.f = x;

  for(int i = 0; i < FLOAT_SIZE; i++) {
    EEPROM.write(addr+i, data.b[i]);
  }
}
