#ifndef STORAGE_H
#define STORAGE_H

const unsigned int START_ADDRESS = 1; // Address location to start storing on EEPROM
const int FLOAT_SIZE = 4;

float readSum(unsigned int addr);
void storeSum(unsigned int addr, float x);
#endif
