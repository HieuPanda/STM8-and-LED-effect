#include "iostm8s005k6.h"
#include <intrinsics.h>
#include "delay.h"
#include "ledEffect.h"
#include "sspi.h"

#define STD_ON 1
#define STD_OFF 0
#define HIGH            1
#define LOW             0

#define LED0 PB_ODR_ODR0
#define LED1 PB_ODR_ODR1
#define LED2 PB_ODR_ODR2
#define LED3 PB_ODR_ODR3
#define LED4 PC_ODR_ODR1
#define LED5 PC_ODR_ODR2
#define LED6 PC_ODR_ODR3
#define LED7 PC_ODR_ODR4

//#define NUMBER_LED     16
#define COUNT_TIME_MAX 100

#define HC595_LATCH       PE_ODR_ODR5

//typedef unsigned char  uint8_t;
typedef   signed char   int8_t;

typedef unsigned int   uint16_t;
typedef   signed int    int16_t;

//khai bao union de dieu khien tung LED qua hc595
typedef union
{
    struct
    {
      uint8_t PIN0 : 1;
      uint8_t PIN1 : 1;
      uint8_t PIN2 : 1;
      uint8_t PIN3 : 1;
      uint8_t PIN4 : 1;
      uint8_t PIN5 : 1;
      uint8_t PIN6 : 1;
      uint8_t PIN7 : 1;
    }PIN;
    uint8_t ODR;
}HC595_RegType;


const uint8_t  dosangtb[16] = {0, 1, 2, 3 , 5, 7, 10, 15, 20, 26, 32, 39, 47, 60, 75, 90}; 
uint8_t  dosang[NUMBER_LED];
HC595_RegType  HC595_REG;

// khai bao con tro ham de tro den cac hieu ung
void (*ptr)(uint8_t * , uint8_t const *);

static void Init_CpuClock(void)
{
    CLK_ICKR_LSIEN     = 1;  //Enable che di low speed internal RC ~ 128khz de nuoi còi và ic thoi gian thuc
    CLK_ECKR_HSEEN     = 0;	// disenable high speed external, clean/set by software
    CLK_CKDIVR_HSIDIV  = 0x00;  //  HSI prescaler, khong chia
    CLK_SWCR_SWEN      = 1;	//	SWEN: swith start/stop, enable clock swith execution chuyen sang thach anh noi
    CLK_SWR            = 0XE1;  //thanh ghi clock marter, chon HSI lam clock source
}
static void Init_Port(void)
{
    // cau hinh led 0
    PB_DDR_DDR0        = 1;  //Chon Chan A1 o che do output mode
    PB_CR1_C10         = 1;  //Chon che do Push pull cho chan A1
    PB_ODR_ODR0        = 0;  // set chan PA1 = 0, out 0V
    
    //cau hinh led 1
    PB_DDR_DDR1        = 1;  //Chon Chan A1 o che do output mode
    PB_CR1_C11         = 1;  //Chon che do Push pull cho chan A1
    PB_ODR_ODR1        = 0;  // set chan PA1 = 0, out 0V
    
    //cau hinh led 2
    PB_DDR_DDR2        = 1;  //Chon Chan A1 o che do output mode
    PB_CR1_C12         = 1;  //Chon che do Push pull cho chan A1
    PB_ODR_ODR2        = 0;  // set chan PA1 = 0, out 0V

    //cau hinh led 3
    PB_DDR_DDR3        = 1;  //Chon Chan A1 o che do output mode
    PB_CR1_C13         = 1;  //Chon che do Push pull cho chan A1
    PB_ODR_ODR3        = 0;  // set chan PA1 = 0, out 0V    

    //cau hinh led 4
    PC_DDR_DDR1        = 1;  //Chon Chan A1 o che do output mode
    PC_CR1_C11         = 1;  //Chon che do Push pull cho chan A1
    PC_ODR_ODR1        = 0;  // set chan PA1 = 0, out 0V   

    //cau hinh led 5
    PC_DDR_DDR2        = 1;  //Chon Chan A1 o che do output mode
    PC_CR1_C12         = 1;  //Chon che do Push pull cho chan A1
    PC_ODR_ODR2        = 0;  // set chan PA1 = 0, out 0V 
    
    //cau hinh led 6
    PC_DDR_DDR3        = 1;  //Chon Chan A1 o che do output mode
    PC_CR1_C13         = 1;  //Chon che do Push pull cho chan A1
    PC_ODR_ODR3        = 0;  // set chan PA1 = 0, out 0V
    
    //cau hinh led 7
    PC_DDR_DDR4        = 1;  //Chon Chan A1 o che do output mode
    PC_CR1_C14         = 1;  //Chon che do Push pull cho chan A1
    PC_ODR_ODR4        = 0;  // set chan PA1 = 0, out 0V   
}

static void Init_Timer2(void)
{
    TIM2_PSCR = 4; // chon clock timer 2 = 1Mhz (ftimer = fmater\2 mu PSCR)
    TIM2_ARRH = (uint8_t)((200>>8) & 0XFF);
    TIM2_ARRL = (uint8_t)(200 & 0XFF);
    TIM2_CR1_ARPE      = 1;
    TIM2_IER_UIE       = 1;
    TIM2_CR1_CEN       = 1;
}

void HC595_Init(void)
{
    Sspi_Init();
}

void HC595_sendData(uint8_t data)
{
  Sspi_Transmit(data);
  HC595_LATCH = HIGH;
  HC595_LATCH = LOW;
}


int main( void )
{
  
    __disable_interrupt();
    Init_CpuClock();
    Init_Port();
    Init_Timer2();
    HC595_Init();
    __enable_interrupt();
  
    while(1)
    {
        hieuUngSaoBang(dosang, (uint8_t*)dosangtb, 100);
    }
}

#pragma vector = TIM2_OVR_UIF_vector
__interrupt void TIM2_OVR_UIF_handler(void)
{
    static uint16_t CountTime = 0;
   
    if(CountTime < dosang[0])
    {
        LED0 = STD_ON;
    }
    else
    {
        LED0 = STD_OFF;
    }
   
    if(CountTime < dosang[1])
    {
        LED1 = STD_ON;
    }
    else
    {
        LED1 = STD_OFF;
    }
 
    if(CountTime < dosang[2])
    {
        LED2 = STD_ON;
    }
    else
    {
        LED2 = STD_OFF;
    }
   
    if(CountTime < dosang[3])
    {
        LED3 = STD_ON;
    }
    else
    {
        LED3 = STD_OFF;
    }
   
    if(CountTime < dosang[4])
    {
        LED4 = STD_ON;
    }
    else
    {
        LED4 = STD_OFF;
    }
   
    if(CountTime < dosang[5])
    {
        LED5 = STD_ON;
    }
    else
    {
        LED5 = STD_OFF;
    }
    if(CountTime < dosang[6])
    {
        LED6 = STD_ON;
    }
    else
    {
        LED6 = STD_OFF;
    }   
    if(CountTime < dosang[7])
    {
        LED7 = STD_ON;
    }
    else
    {
        LED7 = STD_OFF;
    }
    if(CountTime < dosang[8])
    {
        HC595_REG.PIN.PIN0 = STD_ON;
    }
    else
    {
        HC595_REG.PIN.PIN0 = STD_OFF;
    }
    if(CountTime < dosang[9])
    {
        HC595_REG.PIN.PIN1 = STD_ON;
    }
    else
    {
        HC595_REG.PIN.PIN1 = STD_OFF;
    }
    if(CountTime < dosang[10])
    {
        HC595_REG.PIN.PIN2 = STD_ON;
    }
    else
    {
        HC595_REG.PIN.PIN2 = STD_OFF;
    }
    if(CountTime < dosang[11])
    {
        HC595_REG.PIN.PIN3 = STD_ON;
    }
    else
    {
        HC595_REG.PIN.PIN3 = STD_OFF;
    }
    if(CountTime < dosang[12])
    {
        HC595_REG.PIN.PIN4 = STD_ON;
    }
    else
    {
        HC595_REG.PIN.PIN4 = STD_OFF;
    }
    if(CountTime < dosang[13])
    {
        HC595_REG.PIN.PIN5 = STD_ON;
    }
    else
    {
        HC595_REG.PIN.PIN5 = STD_OFF;
    }
    if(CountTime < dosang[14])
    {
        HC595_REG.PIN.PIN6 = STD_ON;
    }
    else
    {
        HC595_REG.PIN.PIN6 = STD_OFF;
    }
    if(CountTime < dosang[15])
    {
        HC595_REG.PIN.PIN7 = STD_ON;
    }
    else
    {
        HC595_REG.PIN.PIN7 = STD_OFF;
    }
    if(++ CountTime == 100)
    {
        CountTime = 0;
    }
    HC595_sendData(HC595_REG.ODR);
    TIM2_SR1_UIF   = 0;
}

