#include "STM32L432KC_SPI.h"
#include "STM32L432KC_GPIO.h"

void initSPI(int br, int cpol, int cpha) {
    // Enable SPI1 clock
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
  
    // Enable GPIOA and GPIOB clocks
  //  RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
  //  RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;

 
    

  //  digitalWrite(PA11, PIO_HIGH);
  //  pinMode(PA11, GPIO_OUTPUT); 
    // Configure alternate functions for SPI pins
   // GPIOA->AFR[0] |= (5 << (5 * 4));  // AF5 for PA5 (SCK)
   // GPIOB->AFR[0] |= (5 << (4 * 4)) | (5 << (5 * 4));  // AF5 for PB4 (MISO) and PB5 (MOSI)
        // Configure CS pin as output
    
    // CS is active low, so start high

    // Configure SPI
    SPI1->CR1 &= ~_VAL2FLD(SPI_CR1_BR, 0b111);

    SPI1->CR1 |=_VAL2FLD(SPI_CR1_BR, br);


    SPI1->CR1 &= ~_VAL2FLD(SPI_CR1_CPOL, cpol); //clear polarity
    SPI1->CR1 |=_VAL2FLD(SPI_CR1_CPOL, cpol);

    SPI1->CR1 &= ~_VAL2FLD(SPI_CR1_CPHA, cpha);//clear phase
    SPI1->CR1 |=_VAL2FLD(SPI_CR1_CPHA, cpha);//phase set
    
    SPI1->CR2 |= _VAL2FLD(SPI_CR2_SSOE, 0b1);
    SPI1->CR2 |= _VAL2FLD(SPI_CR2_FRXTH, 0b1);//set fifo to 8bit
    SPI1->CR1 |= _VAL2FLD(SPI_CR1_MSTR, 0b1);
   // SPI1->CR2 |= SPI_CR2_SSOE;  
   // SPI1->CR1 |= SPI_CR1_SSM;
   // SPI1->CR1 |= SPI_CR1_SSI;
    
     SPI1->CR1 |=_VAL2FLD(SPI_CR2_DS, 7);
    SPI1->CR2 |= _VAL2FLD(SPI_CR2_FRF, 0b0);
 // SPI1->CR2 |= _VAL2FLD(SPI_CR2_DS, 0b1111); 
    // Enable SPI

    SPI1->CR1 |= _VAL2FLD(SPI_CR1_LSBFIRST, 0b0);
    SPI1->CR1 |= _VAL2FLD(SPI_CR1_CRCEN, 0b0);

    SPI1->CR1 |= _VAL2FLD(SPI_CR1_SSM, 0b1);
    SPI1->CR1 |= _VAL2FLD(SPI_CR1_SSI, 0b1);

    SPI1->CR1 |= SPI_CR1_SPE;
}

char spiSendReceive(char send) {
    while (!(SPI1->SR & SPI_SR_TXE));
    *((volatile uint8_t *)&SPI1->DR) = send;
    while (!(SPI1->SR & SPI_SR_RXNE));
    return SPI1->DR;
}
