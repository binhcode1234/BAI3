#include "stm32f10x.h"              // Thu vi?n chính cho STM32F10x
#include "stm32f10x_gpio.h"         // Thu vi?n GPIO
#include "stm32f10x_rcc.h"          // Thu vi?n Clock
#include "stm32f10x_exti.h"         // Thu vi?n EXTI (ng?t ngoài)
#include "misc.h"                   // Các hàm ti?n ích: NVIC, SysTick...

void GPIO_Config(void);
void EXTI_Config(void);
void NVIC_Config(void);
void Delay_ms(uint32_t ms);

int main(void)
{
    SystemInit();       
    GPIO_Config();      
    EXTI_Config();
    NVIC_Config();

    while (1)
    {
        // LED PB12 ON
        GPIO_SetBits(GPIOB, GPIO_Pin_12);
        Delay_ms(500);

        // LED PB12 OFF
        GPIO_ResetBits(GPIOB, GPIO_Pin_12);
        Delay_ms(500);
    }
}

void GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_Cauhinh;

    // Enable clock GPIOB & AFIO
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);

    // PB12, PB13 -> Output push-pull (LEDs)
    GPIO_Cauhinh.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13;
    GPIO_Cauhinh.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Cauhinh.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOB, &GPIO_Cauhinh);

    // PB0 -> Input pull-up (Button)
    GPIO_Cauhinh.GPIO_Pin = GPIO_Pin_0;
    GPIO_Cauhinh.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOB, &GPIO_Cauhinh);
}

void EXTI_Config(void)
{
    EXTI_InitTypeDef EXTI_Cauhinh;

    // Connect EXTI Line0 to PB0
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource0);

    // Configure EXTI Line0
     EXTI_Cauhinh.EXTI_Line = EXTI_Line0;
     EXTI_Cauhinh.EXTI_Mode = EXTI_Mode_Interrupt;
     EXTI_Cauhinh.EXTI_Trigger = EXTI_Trigger_Falling; // nh?n nút t?o m?c th?p
     EXTI_Cauhinh.EXTI_LineCmd = ENABLE;
     EXTI_Init(& EXTI_Cauhinh);
}

void NVIC_Config(void)
{
    NVIC_InitTypeDef NVIC_cauhinh;

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    NVIC_cauhinh.NVIC_IRQChannel = EXTI0_IRQn;
    NVIC_cauhinh.NVIC_IRQChannelPreemptionPriority = 0x0;
    NVIC_cauhinh.NVIC_IRQChannelSubPriority = 0x0;
    NVIC_cauhinh.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_cauhinh);
}

void EXTI0_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line0) != RESET)
    {
        // Ð?o tr?ng thái LED PB13
        if (GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_13))
            GPIO_ResetBits(GPIOB, GPIO_Pin_13);
        else
            GPIO_SetBits(GPIOB, GPIO_Pin_13);

        // Xóa co ngat
        EXTI_ClearITPendingBit(EXTI_Line0);
    }
}

// Hàm delay dùng 2 vòng for l?ng nhau
void Delay_ms(uint32_t ms)
{
    volatile uint32_t i, j;
    for (i = 0; i < ms; i++)
    {
        for (j = 0; j < 8000; j++)   
        {
            
        }
    }
}
