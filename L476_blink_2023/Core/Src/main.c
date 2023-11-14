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
volatile int LED_ON = 0;
volatile int Old_State_Blue_Button = 0;
volatile int Actual_State_Blue_Button = 0;
volatile int Sleep_State = 0;
volatile int expe = 1;
volatile int a=0;

void save_and_increment_expe(void) {
    // Check if blue button is pressed
    if (BLUE_BUTTON()) {
        // Read the backup register value
        uint32_t expe_backup = LL_RTC_BAK_GetRegister(RTC, LL_RTC_BKP_DR0);
        // Increment expe and ensure it loops from 1 to 8
        expe_backup = (expe_backup % 8) + 1;
        // Write the new value to the backup register
        LL_RTC_BAK_SetRegister(RTC, LL_RTC_BKP_DR0, expe_backup);
    }
}


int main(void) {
	/*clock domains activation*/
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);
	GPIO_init();
	LL_PWR_EnableBkUpAccess();

	NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
	if (LL_RCC_LSE_IsReady()==1){
		RTC_Init_HotStart();
	}else{
		RTC_Init_ColdStart();
	}

	//SystemClock_Config_exp1();
	save_and_increment_expe();
	// Initialize expe with the value from the backup register
	expe = LL_RTC_BAK_GetRegister(RTC, LL_RTC_BKP_DR0);
	/* Configure the system clock */
	if (expe == 1) {
		SystemClock_Config_exp1();
		LL_LPM_EnableSleep();
	}
	if (expe == 2) {
		SystemClock_Config_exp2();
		//SystemClock_Config_exp2_blue();
	}
	if (expe == 3) {
		SystemClock_Config_exp3();
		LL_LPM_EnableSleep();
	}
	if (expe == 5) {
		SystemClock_Config_exp5();

		RCC->CR |= RCC_CR_MSIPLLEN;
		LL_LPM_EnableSleep();
		Sleep_State = 1;
		//RTC_wakeup_init_from_stop(7);
	}
	/* Initialize all configured peripherals */
	//GPIO configuration


	//initialization of systick timer (tick period set at 1 ms)
	//LL_Init1msTick( SystemCoreClock );
	//set priority
	NVIC_SetPriority(SysTick_IRQn, -1);
	//Set the Systick reload value for a 10ms overflow
	SysTick_Config(SystemCoreClock / 100); // 10ms overflow
	//Enable the simple sleep mode

	while (1) {
		if (Sleep_State == 1)
			__WFI();

	}
}

// systick interrupt handler
void SysTick_Handler(void) {
	millis += 10;
	if (expe == 2) {
		GPIOC->ODR ^= (1 << 10);

		if (LED_ON == 1 && millis >= 100) {
			LED_GREEN(0);
			LED_ON = 0;
			millis = 0;
		} else if (LED_ON == 0 && millis >= 1900) {
			LED_GREEN(1);
			LED_ON = 1;
			millis = 0;
		}
	}
	if (expe == 3) {
		GPIOC->ODR ^= (1 << 10);
		if (BLUE_BUTTON())
			Sleep_State = 1;
		if (LED_ON == 1 && millis >= 150) {
			LED_GREEN(0);
			LED_ON = 0;
			millis = 0;
		} else if (LED_ON == 0 && millis >= 1850) {
			LED_GREEN(1);
			LED_ON = 1;
			millis = 0;
		}
	}
	if (expe == 5) {
		GPIOC->ODR ^= (1 << 10);
		if (BLUE_BUTTON())
		{
		}
		if (LED_ON == 1 && millis >= 250) {
			LED_GREEN(0);
			LED_ON = 0;
			millis = 0;
		} else if (LED_ON == 0 && millis >= 1750) {
			LED_GREEN(1);
			LED_ON = 1;
			millis = 0;
		}
	}
	if (expe == 1) {
		if (BLUE_BUTTON())
			Sleep_State = 1;
		//MSI_State=0;
		//to be defined if systick interrupt is enabled.
		if (LED_ON == 1 && millis >= T_LED_ON) {
			LED_GREEN(0);
			LED_ON = 0;
			millis = 0;
		} else if (LED_ON == 0 && millis >= T_LED_OFF) {
			LED_GREEN(1);
			LED_ON = 1;
			millis = 0;
		}
	}
}

