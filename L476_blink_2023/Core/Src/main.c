/*Author: Alexandre Boyer
 * Date: 26 Sept 2023
 */
/* Project L476_blink_2023 for STM32L476 mounted on Nucleo board:
 * the user LED (mounted on pin PA-5) is flashed every second for 50 ms.
 * The time base is provided by Systick (1000 ticks per second).
 * The clock configuration is the default one (Sysclk = 80 MHz, derived from MSI and PLL).
 */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "gpio.h"
#include "clock.h"
#define T_LED_OFF 950 //ms
#define T_LED_ON 50 //ms
/* Private function prototypes -----------------------------------------------*/
volatile uint32_t millis = 0;
volatile int LED_ON=0;
volatile int Old_State_Blue_Button=0;
volatile int Actual_State_Blue_Button=0;
volatile int Sleep_State=0;
volatile int expe=2;
int main(void) {
	/*clock domains activation*/
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

	NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

	/* Configure the system clock */
	if (expe==1)
	{
	 SystemClock_Config_exp1();
	 LL_LPM_EnableSleep();
	}
	if (expe==2)
	{
	SystemClock_Config_exp2();
	//SystemClock_Config_exp2_blue();
	}
	/* Initialize all configured peripherals */
	//GPIO configuration
	GPIO_init();

	//initialization of systick timer (tick period set at 1 ms)
	//LL_Init1msTick( SystemCoreClock );
	//set priority
	NVIC_SetPriority(SysTick_IRQn, -1);
	//Set the Systick reload value for a 10ms overflow
	SysTick_Config(SystemCoreClock / 100); // 10ms overflow
	//Enable the simple sleep mode

	while (1) {
		if(Sleep_State==1)
			__WFI();

	}
}

// systick interrupt handler
void SysTick_Handler(void) {
	millis+=10;
	if (expe==2)
	{
		GPIOC->ODR^=(1<<10);
	}
	if(BLUE_BUTTON())
		Sleep_State=1;
		//MSI_State=0;
	//to be defined if systick interrupt is enabled.
	if (LED_ON==1 && millis>=T_LED_ON)
	{
	LED_GREEN(0);
	LED_ON=0;
	millis=0;
	}
	else if(LED_ON ==0 && millis>=T_LED_OFF)
	{
	LED_GREEN(1);
	LED_ON=1;
	millis=0;
	}
}

