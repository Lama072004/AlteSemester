#include <stdio.h>
#include <pigpio.h>
#include <unistd.h>
#include <string.h>

//--------------------------------------AT COMMANDS--------------------------------------//
#define         AT_CGMI         0
#define         AT_CGMM         1
#define         AT_GSN          2

typedef uint8_t ATcommand_t;

const char atCommands[][10] = { "AT+CGMI", "AT+CGMM", "AT+GSN", ""};

//------------------------------------GPIO DEFINITIONS------------------------------------//
#define LED_ORANGE  5     
#define LED_GREEN   7
#define RESET_N     12
#define POWER_ON    26


//------------------------------------UART DEFINITIONS------------------------------------//
#define UART_BAUD   115200
#define BUFFERSIZE  256         //defines maximum length of AT COMMAND response and data sent (AT COMMAND + Payload + response)

//-------------------------------------SPI DEFINITIONS------------------------------------//
#define SPI_CHANNEL 0
#define MODE        0
#define BAUD        64000 

void initSaraModule()
{
    gpioWrite(POWER_ON, 1);
    usleep(500000);
    gpioWrite(POWER_ON, 0);
    usleep(500000);
}

int sendATCommand(int uartHandle, ATcommand_t command, char* rcv)
{
    char sndBuf[BUFFERSIZE] = { 0 };
    strcat(sndBuf, atCommands[command]);
    strcat(sndBuf, "\r");
    serWrite(uartHandle, sndBuf, strlen(sndBuf));
    int rcvCnt = 0;

    //The following code would be more regulated and without sleeping, but it is not working! usleep is necessary. 
    // while(!rcvCnt)
    // {
    //     rcvCnt = serDataAvailable(uartHandle);
    // }    

    usleep(10000);
    rcvCnt = serDataAvailable(uartHandle);
    int actuallyRead = serRead(uartHandle, rcv, rcvCnt);
    return actuallyRead;
}

void turnLedOn(uint8_t gpioNr)
{
    gpioWrite(gpioNr, 1);
}

void turnLedOff(uint8_t gpioNr)
{
    gpioWrite(gpioNr,0);
}

void startUpSequence()
{
    //checking LEDs
    gpioInitialise();
    turnLedOn(LED_GREEN);
    turnLedOn(LED_ORANGE);
    sleep(1);
    turnLedOff(LED_ORANGE); 
    turnLedOff(LED_GREEN);
}

void convertTemperature(char* buffer, int16_t* temperatureWhole, int16_t* temperatureMilli)
{
    int16_t temperatureRaw = 0;
    temperatureRaw |= buffer[0] << 8;
    temperatureRaw |= buffer[1];

    uint16_t negative = 0x8000 & temperatureRaw;      //check if value is negative
    temperatureRaw = temperatureRaw >> 3;             //get rid of lowest 3 bits. These aren't used by the TC77

    if(negative)                                     // Set the highest bit to 1 for negative value
    {                                   
        temperatureRaw |= 0x8000;
    }

    *temperatureWhole = (temperatureRaw * 625) / 10000;         //(raw * 625) = temp in 1/10 of a milli degree celcius, 625 is a constant defined in the datasheet
    *temperatureMilli = ((temperatureRaw * 625) / 10) - (*temperatureWhole) * 1000;
    if(*temperatureMilli < 0)
    {
         *temperatureMilli = (*temperatureMilli) * (-1);
    } 
}


int main()
{
    startUpSequence();

//---------------------------------TC77-----------------------------------------------

    int spiHandle = spiOpen(SPI_CHANNEL, BAUD, MODE);
    if(spiHandle < 0)
    {
        printf("Couldn't open SPI driver\n");
        return -1;
    }
    //led turns automatically on because it is also CE1 which is not used.
    turnLedOff(LED_GREEN); 

    char buffer[2] = { 0 }; 
    int dataLen = spiRead(spiHandle, buffer, 2);

    if(dataLen == 2){
        int16_t temperatureWhole, temperatureMilli;
        convertTemperature(buffer, &temperatureWhole, &temperatureMilli);        
        printf("Temperature is %d,%d°C\n", temperatureWhole, temperatureMilli); 
    }
    else
    {
        printf("Temperature could not be read, check hardware\n");
    }
 
//-------------------------------------------Sara----------------------------------------------
    initSaraModule();

    int uartHandle = serOpen("/dev/ttyS0",UART_BAUD, 0);
    
    if(uartHandle < 0)
    {
        printf("Couldn't open serial device\n");
        return -1;
    }

    //when the raspberry gets started, the first time the UART communcation is started, the SARA Module does not answer,
    //no clue why. The commented block was to try to restart the UART communcation. Didn't work either. On the second start of the programm,
    //everything works fine. 
    {
        char rxAT_CGMI[BUFFERSIZE] = { 0 };
        char rxAT_CGMM[BUFFERSIZE] = { 0 };
        char rxAT_GSN[BUFFERSIZE] = { 0 };

        // sendATCommand(uartHandle, AT_CGMI, rxAT_CGMI);
        // usleep(10000);
        // serClose(uartHandle);
        // usleep(10000);
        // uartHandle = serOpen("/dev/ttyS0",UART_BAUD, 0);
        // usleep(10000);

        sendATCommand(uartHandle, AT_CGMI, rxAT_CGMI);
        sendATCommand(uartHandle, AT_CGMM, rxAT_CGMM);
        sendATCommand(uartHandle, AT_GSN, rxAT_GSN);

        printf("%s***MSG_END***\n", rxAT_CGMI);
        printf("%s***MSG_END***\n", rxAT_CGMM);
        printf("%s***MSG_END***\n", rxAT_GSN);
    }

    serClose(uartHandle);

    return (0);
}

