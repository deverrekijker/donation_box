#include <Arduino.h>
#include <EEPROM.h>
#include "storage.h"

// readFloat() - Returns a float from a given EEPROM address index, addr
float readFloat(unsigned int addr) {
  union {
    byte b[FLOAT_SIZE];
    float f;
  } data;

  for(int i = 0; i < FLOAT_SIZE; i++) {
    data.b[i] = EEPROM.read(addr+i);
  }

  return data.f;
}

// storeFloat() - Stores a float x at a specified EERPOM address index, addr
void storeFloat(unsigned int addr, float x) {
  union {
    byte b[FLOAT_SIZE];
    float f;
  } data;

  data.f = x;

  for(int i = 0; i < FLOAT_SIZE; i++) {
    EEPROM.write(addr+i, data.b[i]);
  }
}
