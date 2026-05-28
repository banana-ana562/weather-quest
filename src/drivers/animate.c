#include <stdint.h>
#include "ST7735.h"
#include "SysTick_Delay.h"
#include "animate.h"
#include "bmps.h"


void raining(void){
    while(1){
        ST7735_FillRect(80, 10, 40, 40, ST7735_BLACK);
        ST7735_DrawBitmap(80, 50, rain1, 40, 40);
        SysTick_Wait(FIVE_MS * 2);

        ST7735_FillRect(80, 10, 40, 40, ST7735_BLACK);
        ST7735_DrawBitmap(80, 50, rain2, 40, 40);
        SysTick_Wait(FIVE_MS * 2);
    }
}