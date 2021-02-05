
#include "misc.h"


/* 8016890 - todo */
void nvic_irq_init(void)
{
	NVIC_InitTypeDef NVIC_InitStruct;

	NVIC_SetVectorTable(NVIC_VectTab_FLASH/*0x8000000*/, 0x4000);
	NVIC_PriorityGroupConfig(/*0x500*/NVIC_PriorityGroup_2);

	NVIC_InitStruct.NVIC_IRQChannel = USART2_IRQn; //0x26;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);

	NVIC_SetPriority(SysTick_IRQn, 0);

	NVIC_InitStruct.NVIC_IRQChannel = RTC_IRQn; //0x03;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
}


/* 80168e0 - complete */
void usart1_init(void)
{
	USART_InitTypeDef USART_InitStruct;

	USART_InitStruct.USART_BaudRate = 115200;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;

	USART_Init(USART1, &USART_InitStruct);
	USART_Cmd(USART1, ENABLE);
}


/* 8016918 - complete */
void usart2_init(void)
{
	USART_InitTypeDef USART_InitStruct;

	USART_InitStruct.USART_BaudRate = 28800;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;

	USART_Init(USART2, &USART_InitStruct);
	USART_ITConfig(USART2, /*0x525*/USART_IT_RXNE, ENABLE);
	USART_Cmd(USART2, ENABLE);
}


/* 801695c - complete */
void periph_clock_enable(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA/*4*/, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB/*8*/, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2/*1 << 17*/, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR/*1 << 28*/, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP/*1 << 27*/, ENABLE);

	PWR_BackupAccessCmd(ENABLE);
}


/* 8016998 - todo */
void sram_periph_init(void)
{
	FSMC_NORSRAMInitTypeDef FSMC_NORSRAMInitStruct; //sp
	FSMC_NORSRAMTimingInitTypeDef FSMC_ReadWriteTimingStruct; //sp60
	GPIO_InitTypeDef GPIO_InitStruct; //sp88

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC/*1 << 8*/, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOG|RCC_APB2Periph_GPIOF|RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOD /*0x1e1*/, ENABLE);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_4|GPIO_Pin_5|
															GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|
															GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15; //0xffb3 = 1111111110110011
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOD, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|
															GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|
															GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15; //0xffff
	GPIO_Init(GPIOE, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|
															GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15; //0xf03f = 1111000000111111
	GPIO_Init(GPIOF, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|
															GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_12; //0x163f = 1011000111111
	GPIO_Init(GPIOG, &GPIO_InitStruct);

	FSMC_ReadWriteTimingStruct.FSMC_AddressSetupTime = 1; //sp60
	FSMC_ReadWriteTimingStruct.FSMC_AddressHoldTime = 1; //sp64
	FSMC_ReadWriteTimingStruct.FSMC_DataSetupTime = 20; //sp68
	FSMC_ReadWriteTimingStruct.FSMC_DataLatency = 0; //sp80
	FSMC_ReadWriteTimingStruct.FSMC_AccessMode = FSMC_AccessMode_A; //0; //sp84
	FSMC_ReadWriteTimingStruct.FSMC_BusTurnAroundDuration = 0; //sp72
	FSMC_ReadWriteTimingStruct.FSMC_CLKDivision = 0; //sp76

	FSMC_NORSRAMInitStruct.FSMC_Bank = FSMC_Bank1_NORSRAM3; //4; //sp0
	FSMC_NORSRAMInitStruct.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable; //0; //sp4
	FSMC_NORSRAMInitStruct.FSMC_MemoryType = FSMC_MemoryType_SRAM; //0; //sp8
	FSMC_NORSRAMInitStruct.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_8b; //0; //sp12
	FSMC_NORSRAMInitStruct.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable; //0; //sp16
	FSMC_NORSRAMInitStruct.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low; //0; //sp24
	FSMC_NORSRAMInitStruct.FSMC_WrapMode = FSMC_WrapMode_Disable; //0; //sp28
	FSMC_NORSRAMInitStruct.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState; //0; //sp32
	FSMC_NORSRAMInitStruct.FSMC_WriteOperation = FSMC_WriteOperation_Enable; //0x1000; //sp36
	FSMC_NORSRAMInitStruct.FSMC_WaitSignal = FSMC_WaitSignal_Disable; //0; //sp40
	FSMC_NORSRAMInitStruct.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable; //0; //sp44
	FSMC_NORSRAMInitStruct.FSMC_AsynchronousWait = FSMC_AsynchronousWait_Disable; //0; //sp20
	FSMC_NORSRAMInitStruct.FSMC_WriteBurst = FSMC_WriteBurst_Disable; //0; //sp48
	FSMC_NORSRAMInitStruct.FSMC_ReadWriteTimingStruct = &FSMC_ReadWriteTimingStruct; //sp52
	FSMC_NORSRAMInitStruct.FSMC_WriteTimingStruct = &FSMC_ReadWriteTimingStruct; //sp56

	FSMC_NORSRAMInit(&FSMC_NORSRAMInitStruct);
	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM3, ENABLE);
}


/* 8017464 - todo */
int main(void)
{

	periph_clock_enable();

	sram_periph_init();
	nvic_irq_init();
	usart2_init();


}

