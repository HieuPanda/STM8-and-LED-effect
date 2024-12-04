#include "LedEffect.h"
void hieuUngSaoBang(uint8_t *dosang, uint8_t *dosangtb, uint8_t speed)
{
    dosang[3] = dosangtb[15];
    dosang[2] = dosangtb[12];
    dosang[1] = dosangtb[9];
    dosang[0] = dosangtb[1]; 
    

      //tu duy xoay mat dong ho
    while(1)
    {
        uint8_t ds = dosang[15];
        for(uint8_t CountLed =15 ; CountLed > 0; CountLed--)
        {
            dosang[CountLed] = dosang[CountLed - 1];
        }
        dosang[0] = ds;
        delay_ms(speed);
    }
    

}

void hieuUngSangDan(uint8_t *dosang, uint8_t *dosangtb)
{
    for( uint8_t CountDs = 0; CountDs < 16; CountDs ++)
    { 
        for(uint8_t CountLed = 0; CountLed < NUMBER_LED ; CountLed ++)
        {
            dosang[CountLed] = dosangtb[CountDs];         
        }
        delay_ms(40);
    }
}

void hieuUngToiDan(uint8_t *dosang, uint8_t *dosangtb)
{
    
     for( uint8_t CountDs = 16; CountDs > 0 ; CountDs --)
    {
        for(uint8_t CountLed = 0; CountLed < NUMBER_LED; CountLed ++)
        {
            dosang[CountLed] = dosangtb[CountDs-1];         
        }
        delay_ms(40);
    }
}

void sangTuTraiQuaPhai(uint8_t *dosang, uint8_t *dosangtb)
{
    for( uint8_t CountLed = 8; CountLed >0; CountLed --)
    {
        for(uint8_t CountDs = 1; CountDs <17; CountDs ++)
        {
            dosang[CountLed-1] = dosangtb[CountDs];         
        }
        delay_ms(100);
    }
}

void tatTuTraiQuaPhai(uint8_t *dosang, uint8_t *dosangtb)
{
    for( uint8_t CountLed = 8; CountLed >0; CountLed --)
    {
        for(uint8_t CountDs = 16; CountDs >0; CountDs --)
        {
            dosang[CountLed-1] = dosangtb[CountDs-1];         
        }
        delay_ms(100);
    }
}
void sangTuPhaiQuaTrai(uint8_t *dosang, uint8_t *dosangtb)
{
    for( uint8_t CountLed = 0; CountLed < NUMBER_LED; CountLed ++)
    {
        for(uint8_t CountDs = 0; CountDs <16; CountDs ++)
        {
            dosang[CountLed] = dosangtb[CountDs];         
        }
     delay_ms(100);
    }
}


void tatTuPhaiQuaTrai(uint8_t *dosang, uint8_t *dosangtb)
{
    for( uint8_t CountLed = 0; CountLed <NUMBER_LED; CountLed ++)
    {
        for(uint8_t CountDs = 16; CountDs >0; CountDs --)
        {
            dosang[CountLed] = dosangtb[CountDs-1];         
        }
        delay_ms(100);
    }
}

void sangNhayTraiQuaPhai(uint8_t *dosang, uint8_t *dosangtb)
{
    for( uint8_t CountLed = 7; CountLed >0; CountLed =CountLed - 2)
    {
        for(uint8_t CountDs = 1; CountDs <17; CountDs ++)
        {
            dosang[CountLed] = dosangtb[CountDs];         
        }
        delay_ms(100);
    }
}

void tatNhayTraiQuaPhai(uint8_t *dosang, uint8_t *dosangtb)
{
    for( uint8_t CountLed = 7; CountLed >0; CountLed -= 2)
    {
        for(uint8_t CountDs = 16; CountDs >0; CountDs --)
        {
            dosang[CountLed] = dosangtb[CountDs];         
        }
        delay_ms(100);
    }
}

void ledSangDon(uint8_t *dosang, uint8_t const *dosangtb)
{
    uint8_t Count =0, sodensang = 0;
    for(uint8_t CountDem = 0; CountDem < 16; CountDem ++ )
    {
        sodensang = NUMBER_LED - CountDem;
        for (Count = 0 ; Count < sodensang ; Count++ )
        {       
            dosang[Count]= dosangtb[15];
            if(Count > 0)
            {
                dosang[Count-1] = dosangtb[0];
            }
            delay_ms(200);
        }
    }
}