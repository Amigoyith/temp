// DS1722.c
// TODO: <YOUR NAME>
// TODO: <YOUR EMAIL>
// TODO: <DATE>
// TODO: <SHORT DESCRIPTION OF WHAT THIS FILE DOES>
#include "DS1722.h"
#include "STM32L432KC_SPI.h"
#include "STM32L432KC_GPIO.h"
#include "STM32L432KC_TIM.h"
#include <stdint.h> 
#include <stdio.h>
#define SPI_CS_PIN PA11

void initDS1722(void) {
    pinMode(SPI_CS_PIN, GPIO_OUTPUT);
    digitalWrite(SPI_CS_PIN, PIO_HIGH);

    spiCSLow();
   // delay_millis(TIM15,10);
     spiSendReceive(0x02);  // Write to configuration register
    spiSendReceive(0x00);  // Set to 12-bit resolution
    spiCSHigh();
}

void spiCSLow(void) {
    digitalWrite(PA11, PIO_LOW);
    //printf("CS Low\n");
}

void spiCSHigh(void) {
    digitalWrite(PA11, PIO_HIGH);
    //printf("CS High\n");
}

float readTemperature(void) {
    spiCSLow();
    spiSendReceive(0x01);  // Read Temperature command
    uint8_t msb = spiSendReceive(0x00);
    uint8_t lsb = spiSendReceive(0x00);
    spiCSHigh();

    int16_t temp = (msb << 8) | lsb;
    return temp;  
    }
