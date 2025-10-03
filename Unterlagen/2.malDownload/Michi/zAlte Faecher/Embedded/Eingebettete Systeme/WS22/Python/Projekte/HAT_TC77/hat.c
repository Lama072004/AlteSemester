#include <stdio.h>
//#include <stdlib.h>
#include <pigpio.h>
//#include "/../../usr/include/pigpiod_if2.h"

        
#define RGB_RED     19
#define RGB_GREEN   12
#define RGB_BLUE    13
#define NWK_LED     22

// #define MISO     9
// #define CLK          11
// #define CS           8
// #define MOSI     10

#define BUFFERSIZE  2
#define SPI_CHANNEL 1

#define BAUD        64000

#define MODE        0


//returns the temperature in 1/10 Celsius
//parameters: spi buffer 
uint32_t getTemperature(char* data)
{
    //every bit is a step of 0.0625°C, data consists of 12 (13) bits 
    //first bit is +- sign, 
    const int msb = 0, lsb = 1;
    const uint8_t mask = 0x07;

    //get rid of dont care bits
    data[lsb] = data[lsb] >> 3;

    //get sign and delete sign bit
    bool isNegative = data[msb] & 0x80;
    data[msb] = data[msb] & 0x7F;

    //get highest three bits
    char highestThreeBitsLSB = data[msb] & mask;
    highestThreeBitsLSB = highestThreeBitsLSB << 5;
}

//returns the temperature in 1/100 Celsius
//parameters: spi buffer 
int32_t getTemperatureAlt(char* data)
{
    //every bit is a step of 0.0625°C, data consists of 12 (13) bits 
    const int msb = 0, lsb = 1;
    uint32_t value = (data[msb] << 8) & data[lsb];
    bool isNegative = value & 0x7000;
    value = value << 1;
    value = value >> 4;
    int32_t ret = 0xFFFF & value;
    if(isNegative) ret = ret * -1;
    ret = ret * 625;
    ret /= 100;
    return (uint32_t) ret;
}


int main()
//zuerst Programm in "Terminal - Buildaufgabe ausführen builden"
//anschließend im Terminal mit "sudo ./output/main" ausführen
{

    unsigned int modus = MODE;
    gpioInitialise();

 
    unsigned int spiHandle = spiOpen(SPI_CHANNEL, BAUD, modus);
    printf("Handle = %d\n", spiHandle);

    char buffer[2] = {2};
    
    int retVal = spiRead(spiHandle, buffer, 2);
    printf("retVal READ: %d\n", retVal);
    uint8_t lo = buffer[0];
    uint8_t hi = buffer[1];

    printf("%u %d\n", lo, hi);

    // printf("Hello World!\n");

    // gpioSetMode(RGB_RED, PI_OUTPUT);
    // gpioSetMode(RGB_GREEN, PI_OUTPUT);
    // gpioSetMode(RGB_BLUE, PI_OUTPUT);
    // gpioWrite(RGB_BLUE,1);
    // gpioWrite(RGB_GREEN,1);
    // gpioWrite(RGB_RED,1);
    // gpioWrite(NWK_LED,0  );
    
    return (0);
}

