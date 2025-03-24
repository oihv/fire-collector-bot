#include "sys.h"

void RCC_Configuration(void){ // RCC clock configuration
	ErrorStatus HSEStartUpStatus;
	RCC_DeInit(); // RCC system reset (for debug purpose), RCC registers are reset to initial values
	RCC_HSEConfig(RCC_HSE_ON); // Enable HSE (High-Speed External oscillator)
	HSEStartUpStatus = RCC_WaitForHSEStartUp(); // Wait until HSE is ready
	if(HSEStartUpStatus == SUCCESS){
		// Set PLL clock source and multiplication factor
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9); // RCC_PLLMul_x, where x is the multiplication factor from 2 to 16. When HSE=8MHz, and RCC_PLLMul_9, the PLLCLK=72MHz
		// Set AHB clock (HCLK)
		RCC_HCLKConfig(RCC_SYSCLK_Div1); // RCC_SYSCLK_Div1, so AHB clock = system clock (SYSCLK) = 72MHz, external crystal is 8MHz
		// Note here, if you use SYSTICK as the system clock, then the SYSTICK (Cortex System timer) = HCLK/8 = 9MHz
		RCC_PCLK1Config(RCC_HCLK_Div2); // Set low-speed AHB clock (PCLK1), RCC_HCLK_Div2, so APB1 clock = HCLK/2 = 36MHz, external crystal is 8MHz
		RCC_PCLK2Config(RCC_HCLK_Div1); // Set high-speed AHB clock (PCLK2), RCC_HCLK_Div1, so APB2 clock = HCLK = 72MHz, external crystal is 8MHz
		// Note that AHB needs to be faster than the external storage clock. APB2 includes AD, I/O, high-speed TIM, etc. APB1 includes DA, USB, SPI, I2C, CAN, low-speed TIM, etc.
		FLASH_SetLatency(FLASH_Latency_2); // Set FLASH storage access latency
		/* FLASH clock delay is added here, waiting for the clock to synchronize
		Recommended chip system operating frequency:
		0~24MHz, choose Latency_0,
		24~48MHz, choose Latency_1,
		48~72MHz, choose Latency_2 */
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable); // Choose FLASH prefetch instruction mode, enable prefetch instruction
		RCC_PLLCmd(ENABLE); // Enable PLL
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET); // Wait for PLL to stabilize
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK); // Choose SYSCLK clock source as PLL
		while(RCC_GetSYSCLKSource() != 0x08); // Wait for PLL to be the SYSCLK clock source
	}
	// Start enabling the clock of the peripherals you want to use
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |
	RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE, ENABLE); // Enable APB2 peripheral clock
}
