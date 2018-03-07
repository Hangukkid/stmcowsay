#ifndef COWSAY_H
#define COWSAY_H
#include <stdint.h>

void drawTextBox(uint8_t*, int);
void drawCow();
void receiveInput (uint8_t*, int);

//helper functions
void clearString(uint8_t*, int);

#endif