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
volatile int expe;
volatile int a = 0;
volatile int blue_mode = 0;
volatile int init = 1;

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
	if (LL_RCC_LSE_IsReady() == 1) {
		RTC_Init_HotStart();
	} else {
		RTC_Init_ColdStart();
	}

	//SystemClock_Config_exp1();
	save_and_increment_expe();
	// Initialize expe with the value from the backup register
	expe = LL_RTC_BAK_GetRegister(RTC, LL_RTC_BKP_DR0);
	//8 experiences au total => on reset expe une fois arrive a 8
	if (expe > 8){
		expe=1;
	}
	//expe = 6;
	/* Configure the system clock */
	if (expe == 1) {
		SystemClock_Config_exp1();
		LL_LPM_EnableSleep();
	}
	if (expe == 2) {
		SystemClock_Config_exp2();

	}
	if (expe == 3) {
		SystemClock_Config_exp3();
		LL_LPM_EnableSleep();
	}
	if (expe ==4){ //expe3 bis car non realise
		SystemClock_Config_exp3();
		LL_LPM_EnableSleep();
	}
	if (expe == 5) {
		SystemClock_Config_exp5();
		LL_LPM_EnableSleep();
		LL_RCC_MSI_EnablePLLMode();
	}
	if (expe == 6) {
		SystemClock_Config_exp5();
		LL_LPM_EnableSleep();
		LL_RCC_MSI_EnablePLLMode();
	}
	if (expe == 7) {
		SystemClock_Config_exp5();
		LL_LPM_EnableSleep();
		LL_RCC_MSI_EnablePLLMode();
	}
	if (expe == 8) {
		SystemClock_Config_exp5();
		LL_LPM_EnableSleep();
		LL_RCC_MSI_EnablePLLMode();
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
	if (BLUE_BUTTON() && !init) {
		blue_mode = 1;
	}
	if (!BLUE_BUTTON() && init) {
		init = 0;
	}
	if (expe == 2) {
		GPIOC->ODR ^= (1 << 10);
		if (BLUE_BUTTON()) {
			//SystemClock_Config_exp2_blue();
		}
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
	if (expe == 4) { //expe3 bis car non traité
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
		if (blue_mode == 1) {
			LL_LPM_EnableDeepSleep();
			LL_PWR_SetPowerMode(LL_PWR_MODE_STOP0); //stop0
			RTC_wakeup_init_from_stop(7);
			__WFI();
			blue_mode = 0;
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
	if (expe == 6) {
		GPIOC->ODR ^= (1 << 10);
		if (blue_mode == 1) {
			LL_LPM_EnableDeepSleep();
			LL_PWR_SetPowerMode(LL_PWR_MODE_STOP1);
			RTC_wakeup_init_from_stop(7);
			__WFI();
			blue_mode = 0;
		}
		if (LED_ON == 1 && millis >= 300) {
			LED_GREEN(0);
			LED_ON = 0;
			millis = 0;
		} else if (LED_ON == 0 && millis >= 1700) {
			LED_GREEN(1);
			LED_ON = 1;
			millis = 0;
		}
	}
	if (expe == 7) {
		GPIOC->ODR ^= (1 << 10);
		if (blue_mode == 1) {
			LL_LPM_EnableDeepSleep();
			LL_PWR_SetPowerMode(LL_PWR_MODE_STOP2);
			RTC_wakeup_init_from_stop(7);
			__WFI();
			blue_mode = 0;
		}
		if (LED_ON == 1 && millis >= 350) {
			LED_GREEN(0);
			LED_ON = 0;
			millis = 0;
		} else if (LED_ON == 0 && millis >= 1650) {
			LED_GREEN(1);
			LED_ON = 1;
			millis = 0;
		}
	}
	if (expe == 8) {
		GPIOC->ODR ^= (1 << 10);
		if (BLUE_BUTTON()) {
			LL_PWR_SetPowerMode(LL_PWR_MODE_SHUTDOWN);
			LL_LPM_EnableDeepSleep();
			RTC_wakeup_init_from_standby_or_shutdown(7);
			__WFI();
			//blue_mode = 0;
		}
		if (LED_ON == 1 && millis >= 400) {
			LED_GREEN(0);
			LED_ON = 0;
			millis = 0;
		} else if (LED_ON == 0 && millis >= 1600) {
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
// partie commune a toutes les utilisations du wakeup timer
void RTC_wakeup_init(int delay) {
	LL_RTC_DisableWriteProtection( RTC);
	LL_RTC_WAKEUP_Disable( RTC);
	while (!LL_RTC_IsActiveFlag_WUTW( RTC)) {
	}
	// connecter le timer a l'horloge 1Hz de la RTC
	LL_RTC_WAKEUP_SetClock( RTC, LL_RTC_WAKEUPCLOCK_CKSPRE);
	// fixer la duree de temporisation
	LL_RTC_WAKEUP_SetAutoReload( RTC, delay);	// 16 bits
	LL_RTC_ClearFlag_WUT(RTC);
	LL_RTC_EnableIT_WUT(RTC);
	LL_RTC_WAKEUP_Enable(RTC);
	LL_RTC_EnableWriteProtection(RTC);
}

// Dans le cas des modes STANDBY et SHUTDOWN, le MPU sera reveille par reset
// causé par 1 wakeup line (interne ou externe) (le NVIC n'est plus alimenté)
void RTC_wakeup_init_from_standby_or_shutdown(int delay) {
	RTC_wakeup_init(delay);
	// enable the Internal Wake-up line
	LL_PWR_EnableInternWU();// ceci ne concerne que Standby et Shutdown, pas STOPx
}

// Dans le cas des modes STOPx, le MPU sera reveille par interruption
// le module EXTI et une partie du NVIC sont encore alimentes
// le contenu de la RAM et des registres étant préservé, le MPU
// reprend l'execution après l'instruction WFI
void RTC_wakeup_init_from_stop(int delay) {
	RTC_wakeup_init(delay);
	// valider l'interrupt par la ligne 20 du module EXTI, qui est réservée au wakeup timer
	LL_EXTI_EnableIT_0_31( LL_EXTI_LINE_20);
	LL_EXTI_EnableRisingTrig_0_31( LL_EXTI_LINE_20);
	// valider l'interrupt chez NVIC
	NVIC_SetPriority(RTC_WKUP_IRQn, 1);
	NVIC_EnableIRQ(RTC_WKUP_IRQn);
}

// wakeup timer interrupt Handler (inutile mais doit etre defini)
void RTC_WKUP_IRQHandler() {
	LL_EXTI_ClearFlag_0_31( LL_EXTI_LINE_20);
}

