#include "iostm8s005k6.h"
#include "sspi.h"

#define SPI_MOSI        PC_ODR_ODR6
#define SPI_MISO        PC_IDR_IDR7
#define SPI_CLK         PC_ODR_ODR5
#define SPI_CS 
#define HIGH            1
#define LOW             0

void Sspi_Init(void)
{
    //cau hình các chân, MISO,MOSI, SCL, CS 
    PC_DDR_DDR6         = 1;  // MOSI
    PC_CR1_C16          = 1;  
    PC_ODR_ODR6         = 0;  
   
    PC_DDR_DDR7         = 0;  //MISO
    PC_CR1_C17          = 1;  
    PC_ODR_ODR7         = 0;  
   
    PC_DDR_DDR5         = 1;  //CLK 
    PC_CR1_C15          = 1;  
    PC_ODR_ODR5         = 0;  
   
    PE_DDR_DDR5         = 1;  //CS
    PE_CR1_C15          = 1;  
    PE_ODR_ODR5         = 0; 
}

uint8_t Sspi_Transmit(uint8_t data)
{
    uint8_t data_read = 0x00;
    //truoc khi truyen keo chan cs xuong thap de chon chip giao tiep
    //SPI_CS = LOW;
    for(uint8_t countBit = 0; countBit < 8 ; countBit++)
    {
        //gui bit cao truoc
        SPI_MOSI = (data >> (7- countBit)) & 0x01 ;
        SPI_CLK = HIGH;
        SPI_CLK = LOW;
        // doc du lieu tu chan miso
        data_read = SPI_MISO;
        if(countBit < 7)
        {
            data_read = data_read << 1;
        }
    }
    //khi truyen xong thi enable len
    //SPI_CS = HIGH;
    return data_read;
}

