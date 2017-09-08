#ifndef STORAGE_H
#define STORAGE_H

const unsigned int START_ADDRESS = 1; // Address location to start storing on EEPROM
const int FLOAT_SIZE = 4; // The size of our float data structure in Bytes

float readFloat(unsigned int addr);
void storeFloat(unsigned int addr, float x);
#endif
