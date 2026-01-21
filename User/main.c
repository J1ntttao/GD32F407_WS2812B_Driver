#include "gd32f4xx.h"
#include "systick.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "USART0.h"
#include "SPI.h"
#include "driver_ws2812b.h"

void USART0_on_recv(uint8_t* data, uint32_t len) {
    // 此代码是在中断里执行的, 不要做耗时操作 (delay_ms)
    printf("recv[%d]->%s\n", len, data);
}

int main(void) {

    // 配置全局中断优先级分组
    nvic_priority_group_set(NVIC_PRIGROUP_PRE2_SUB2);
    // 滴答定时器初始化
    systick_config();
    // 初始化串口
    USART0_init();
    // 初始化SPI
    SPI_init();
    // 初始化WS2812
    WS2812_init();
    // 初始化颜色
    for(uint16_t i = 0; i < WS2812_NUM1; i++){
        WS2812_set_color_brightness(1, i, 0x00FFFF, 1);
    }
    for(uint16_t i = 0; i < WS2812_NUM2; i++){
        WS2812_set_color_brightness(2, i, 0xFFFF00, 1);
    }
    // 显示颜色
    WS2812_display(1);
    delay_1ms(10); 
    WS2812_display(2);
  
    while(1);
}
